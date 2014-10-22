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

include <Elementary.h>

static Eina_Bool visible = EINA_TRUE;
static Eina_Bool editable = EINA_TRUE;
static Eina_Bool disabled = EINA_FALSE;

//testing ui reflection on prefs data changes
static Eina_Bool
_elm_prefs_items_change(void *data)
{
   Evas_Object *prefs, *notify = data;
   Elm_Prefs_Data *prefs_data;
   Elm_Prefs_Item_Type type;
   Eina_Value value;

   prefs = evas_object_data_get(notify, "prefs");
   prefs_data = evas_object_data_get(notify, "prefs_data");

   visible = !visible;
   elm_prefs_item_visible_set(prefs, "main:floatsp", visible);

   disabled = !disabled;
   elm_prefs_item_disabled_set(prefs, "main:checkb", disabled);

   editable = !editable;
   elm_prefs_item_editable_set(prefs, "main:text", editable);
   if (elm_prefs_data_value_get(prefs_data, "main:text", &type, &value))
     {
        eina_value_set(&value, editable ? "This is a editable text entry" :
                       "This is a non-editable text entry");
        elm_prefs_data_value_set(prefs_data, "main:text", type, &value);
     }

   evas_object_show(notify);

   return ECORE_CALLBACK_RENEW;
}

static void
_action_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *notify = data;
   Elm_Prefs_Data *prefs_data;
   Elm_Prefs_Item_Type type;
   Eina_Value value;

   prefs_data = evas_object_data_get(notify, "prefs_data");

   if (elm_prefs_data_value_get(prefs_data, "main:text", &type, &value))
     {
        eina_value_set(&value, "Action!");
        elm_prefs_data_value_set(prefs_data, "main:text", type, &value);
     }
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Elm_Prefs_Data *prefs_data;

   ::elm_win win(elm_win_util_standard_add("Prefs", "Prefs Example 02"));
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
  win.autodel_set(EINA_TRUE);

   ::elm_prefs prefs(efl::eo::parent = win);
   prefs.size_hint_weight_set(prefs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   win.resize_object_add(prefs);
   prefs.visibility_set(EINA_TRUE);

   prefs.autosave_set(EINA_TRUE);

   prefs_data = ::elm_prefs_data_new("./prefs_example_02.cfg", NULL, EET_FILE_MODE_READ_WRITE);

   prefs.file_set("prefs_example_02.epb", NULL);
   prefs.data_set(prefs_data);

   ::elm_label label(efl::eo::parent = win);
   elm_object_text_set(label._eo_ptr(), "Editable, Visible and Disable! Just Saying...");  // XXX
   label.size_hint_weight_set(0.0, 0.0);
   label.size_hint_align_set(0.5, 0.5);

   ::elm_notify notify(efl::eo::parent = win);
   notify.align_set(0.5, 1);
   notify.timeout_set(2);
   elm_object_content_set(notify._eo_ptr(), label._eo_ptr());  // XXX
   notify.size_hint_weight_set(notify, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   notify.visibility_set(EINA_TRUE);

   notify.data_set("prefs", prefs);
   notify.data_set("prefs_data", prefs_data);

   prefs.callback_action_add(&_action_cb);

   win.evas::object::size_set(320, 320);
   win.visibility_set(EINA_TRUE);

   ecore_timer_add(5.0, _elm_prefs_items_change, notify);

   elm_run();

   ::elm_prefs_data_unref(prefs_data);

   elm_shutdown();

   return 0;
}
ELM_MAIN()
