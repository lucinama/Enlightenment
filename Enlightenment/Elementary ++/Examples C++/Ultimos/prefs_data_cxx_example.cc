#ifdef HAVE_CONFIG_H
# include <elementary_config.h>
#endif

extern "C"
{
#define ELM_INTERNAL_API_ARGESFSDFEFC
#define ELM_INTERFACE_ATSPI_ACCESSIBLE_PROTECTED
#define ELM_INTERFACE_ATSPI_COMPONENT_PROTECTED
#define ELM_INTERFACE_ATSPI_ACTION_PROTECTED
#define ELM_INTERFACE_ATSPI_VALUE_PROTECTED
#define ELM_INTERFACE_ATSPI_EDITABLE_TEXT_PROTECTED
#define ELM_INTERFACE_ATSPI_TEXT_PROTECTED
#define ELM_INTERFACE_ATSPI_SELECTION_PROTECTED
#define ELM_INTERFACE_ATSPI_IMAGE_PROTECTED
#define ELM_INTERFACE_ATSPI_WIDGET_ACTION_PROTECTED

#include <Eo.h>
#include <Evas.h>
#include <Elementary.h>
#include <elm_widget.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_text.h"
#include "elm_interface_scrollable.h"
}

#include <Elementary.hh>
#include <Eina.hh>


static void
_item_changed_cb(void *cb_data, Elm_Prefs_Data_Event_Type type, Elm_Prefs_Data *data, void *event_info)
{
   Elm_Prefs_Data_Event_Changed *evt = event_info;
   Eina_Bool ok;
   char *str = eina_value_to_string(evt->value);

   printf("item %s had its value changed to %s\n", evt->key, str);
   free(str);

   ok = elm_prefs_data_event_callback_del(data, type, _item_changed_cb, NULL);
   printf("elm_prefs_data_event_callback_del(): %s\n", ok ? "ok" : "fail");
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   Eina_Value value;
   Eina_Bool ok;
   int version;
   char *str;

   prefs_data = elm_prefs_data_new("./test", NULL, EET_FILE_MODE_READ_WRITE);
   printf("elm_prefs_data_new(): %s\n", prefs_data ? "ok" : "fail");

   elm_prefs_data_autosave_set(prefs_data, EINA_TRUE);

   ok = elm_prefs_data_autosave_get(prefs_data);
   printf("elm_prefs_data_autosave_get() returns: %s\n", ok ? "yes" : "no");

   eina_value_setup(&value, EINA_VALUE_TYPE_INT);
   eina_value_set(&value, 50);

   ok = elm_prefs_data_value_set(prefs_data, "position", &value);
   printf("elm_prefs_data_value_set(): %s\n", ok ? "ok" : "fail");
   str = eina_value_to_string(&value);
   printf("value for \'position\' is now %s\n", str);
   free(str);

   printf("elm_prefs_data_version_get() returns %d\n",
          version = elm_prefs_data_version_get(prefs_data));

   elm_prefs_data_version_set(prefs_data, ++version);

   elm_prefs_data_unref(prefs_data);

   prefs_data = elm_prefs_data_new("./test", NULL, EET_FILE_MODE_READ_WRITE);

   ok = elm_prefs_data_value_get(prefs_data, "position", &value);
   printf("elm_prefs_data_value_get(): %s\n", ok ? "ok" : "fail");
   str = eina_value_to_string(&value);
   printf("value for \'position\' is %s\n", str);
   free(str);

   eina_value_set(&value, 3000);

   ok = elm_prefs_data_event_callback_add
      (prefs_data, ELM_PREFS_DATA_EVENT_ITEM_CHANGED, _item_changed_cb, NULL);
   printf("elm_prefs_data_event_callback_add(): %s\n", ok ? "ok" : "fail");

   ok = elm_prefs_data_value_set(prefs_data, "position", &value);
   printf("elm_prefs_data_value_set(): %s\n", ok ? "ok" : "fail");
   str = eina_value_to_string(&value);
   printf("value for \'position\' is now %s\n", str);
   free(str);

   ok = elm_prefs_data_save(prefs_data, NULL, NULL);
   printf("elm_prefs_data_save(): %s\n", ok ? "ok" : "fail");

   elm_prefs_data_ref(prefs_data);
   elm_prefs_data_ref(prefs_data);

   printf("elm_prefs_data_version_get() returns %d\n",
          version = elm_prefs_data_version_get(prefs_data));

   elm_prefs_data_unref(prefs_data);
   elm_prefs_data_unref(prefs_data);
   elm_prefs_data_unref(prefs_data);

   elm_shutdown();

   return 0;
}
ELM_MAIN()
