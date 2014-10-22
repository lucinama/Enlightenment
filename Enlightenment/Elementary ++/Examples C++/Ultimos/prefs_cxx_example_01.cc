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
#include <pthread.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_text.h"
#include "elm_interface_scrollable.h"
}

#include <Elementary.hh>
#include <Eina.hh>

static Eina_Bool
_elm_prefs_data_change(void *data)
{
   Evas_Object *notify = data;
   Elm_Prefs_Data *prefs_data;
   Elm_Prefs_Item_Type type;
   Eina_Value value;

   prefs_data = evas_object_data_get(notify, "prefs_data");

   if (elm_prefs_data_value_get(prefs_data, "main:universe", &type, &value))
     {
        eina_value_set(&value, 42);
        elm_prefs_data_value_set(prefs_data, "main:universe", type, &value);
     }

   if (elm_prefs_data_value_get(prefs_data, "main:text", &type, &value))
     {
        eina_value_set(&value, "This is a text field (:");
        elm_prefs_data_value_set(prefs_data, "main:text", type, &value);
     }

   evas_object_show(notify);

   return ECORE_CALLBACK_RENEW;
}

static void
_page_saved_cb(void *data, Evas_Object *obj, void *event_info)
{
   const char *page = event_info;

   printf("page %s was saved!\n", page);
}

static void
_page_loaded_cb(void *data, Evas_Object *obj, void *event_info)
{
   const char *page = event_info;

   printf("page %s was loaded!\n", page);
}

static void
_item_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
   const char *item = event_info;

   printf("item %s was changed!\n", item);
}

EAPI_MAIN int
elm_main(int argc, char **argv)

   Elm_Prefs_Data *prefs_data;

::elm_win win(elm_win_util_standard_add("prefs", "Prefs Example 01"));
elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
win.autodel_set(true);

::elm_prefs prefs(efl::eo::parent = win);
prefs.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
win.resize_object_add(prefs);
prefs.visibility_set(true);

prefs.callback_page_saved_add(&_page_saved_cb);
prefs.callback_page_loaded_add(&_page_loaded_cb);
prefs.callback_item_changed_add(&_item_changed_cb);

elm_prefs_autosave_set(prefs, EINA_TRUE);

prefs_data = elm_prefs_data_new("./prefs_example_01.cfg", NULL,
				EET_FILE_MODE_READ_WRITE);

prefs.file_set("prefs_example_01.epb", NULL);
prefs_data_set(prefs_data);

::elm_label label(efl::eo::parent = win);
elm_object_text_set(label._eo_ptr(), "Setting Values Programmatically");  // XXX
label.size_hint_align_set(0.5, 0.5);

::elm_notify notify(efl::eo::parent = win);
notify.align_set(0.5, 1);
notify.timeout_set( 2);
elm_object_content_set(notify._eo_ptr(), label._eo_ptr());  // XXX
notify.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
notify.visibility_set(true);

notify.data_set("prefs_data", prefs_data);

win.evas::object::size_set(320, 320);
win.visibility_set(true);

ecore_timer_add(5.0, _elm_prefs_data_change, notify);

elm_run();

prefs_data.unref();

elm_shutdown();

return 0;
}
ELM_MAIN()
