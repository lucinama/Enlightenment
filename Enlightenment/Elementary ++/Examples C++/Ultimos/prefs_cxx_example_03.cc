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

#define WIDTH (500)
#define HEIGHT (700)
#define MSG_ID_VEL (1)

static void
_update_animation(Evas_Object *prefs, Evas_Object *layout)
{
   Eina_Value value;
   Eina_Bool animation;

   elm_prefs_item_value_get(prefs, "main:config:options:animation", &value);
   eina_value_get(&value, &animation);
   if (animation)
     elm_layout_signal_emit(layout, "start", "animation");
   else
     elm_layout_signal_emit(layout, "stop", "animation");
}

static void
_update_animation_time(Evas_Object *prefs, Evas_Object *layout)
{
   Eina_Value value;
   float animation_time;
   Edje_Message_Float msg;

   elm_prefs_item_value_get(prefs, "main:config:options:animation_time", &value);
   eina_value_get(&value, &animation_time);
   if (animation_time < 0.01) animation_time = 0.01;
   msg.val = animation_time;
   edje_object_message_send(elm_layout_edje_get(layout), EDJE_MESSAGE_FLOAT,
                            MSG_ID_VEL, &msg);
}

static void
_update(Evas_Object *prefs, Evas_Object *layout)
{
   _update_animation(prefs, layout);
   _update_animation_time(prefs, layout);
}

static void
_page_loaded_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *layout = data;

   _update(obj, layout);
}

static void
_item_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
   const char *item = event_info;
   Evas_Object *layout = data;

   if (!strcmp(item, "main:config:options:animation_time"))
     _update_animation_time(obj, layout);
   else if (!strcmp(item, "main:config:options:animation"))
     _update_animation(obj, layout);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Elm_Prefs_Data *prefs_data;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   ::elm_win win(elm_win_util_standard_add("Prefs", "Prefs Example 03"));
   win.autodel_set(EINA_TRUE);

   ::elm_layout layout(efl::eo::parent = win);
   layout.file_set("prefs_example_03.edj", "prefs_edje");

   ::elm_prefs prefs(efl::eo::parent = win);
   prefs.size_hint_weight_set(prefs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   prefs.evas::object::size_set(WIDTH, HEIGHT);
   prefs.visibility_set(EINA_TRUE);

   prefs.callback_page_loaded_add(&_page_loaded_cb);
   prefs.callback_item_changed_add(&_item_changed_cb);

   prefs.autosave_set(EINA_TRUE);

   prefs_data = ::elm_prefs_data_new("./prefs_example_03.cfg", NULL, EET_FILE_MODE_READ_WRITE);

   prefs.file_set("prefs_example_03.epb", NULL);
   prefs.data_set(prefs_data);

   prefs.item_swallow("main:swal", layout);

   _update_animation_time(prefs, layout);
   _update_animation(prefs, layout);

   win.evas::object::size_set(WIDTH, HEIGHT);
   win.visibility_set(EINA_TRUE);

   elm_run();

   ::elm_prefs_data_unref(prefs_data);

   elm_shutdown();

   return 0;
}
ELM_MAIN()
