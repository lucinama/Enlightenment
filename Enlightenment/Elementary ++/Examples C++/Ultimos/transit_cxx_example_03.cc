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

#include <iostream>

struct Context
{
   Eina_Bool events_enabled;
   Eina_Bool auto_reverse;
   Eina_Bool final_state_keep;
   int repeat_times;
   Elm_Transit_Tween_Mode tween_mode;
   Evas_Object *obj;
};

static void
_transit_translation(Elm_Transit *trans)
{
  ::elm_transit_effect_translation_add(trans, -20, -50, 70, 150);
}

static void
_transit_color(Elm_Transit *trans)
{
  ::elm_transit_effect_color_add(trans, 100, 255, 100, 255, 40, 10, 40, 50);
}

static void
_transit_rotation(Elm_Transit *trans)
{
  ::elm_transit_effect_rotation_add(trans, 0.0, 135.0);
}

static void
_transit_wipe(Elm_Transit *trans)
{
  ::elm_transit_effect_wipe_add(trans, ELM_TRANSIT_EFFECT_WIPE_TYPE_HIDE, ELM_TRANSIT_EFFECT_WIPE_DIR_RIGHT);
}

static void
_transit_zoom(Elm_Transit *trans)
{
  ::elm_transit_effect_zoom_add(trans, 1.0, 2.0);
}

static void
_transit_resizing(Elm_Transit *trans)
{
  ::elm_transit_effect_resizing_add(trans, 250, 100, 400, 160);
}

static struct {
     const char *label;
     void (*transition_add_cb)(Elm_Transit *);
     Eina_Bool checked;
} _transitions[] = {
       { "Translation", _transit_translation, EINA_FALSE },
       { "Color", _transit_color, EINA_FALSE },
       { "Rotation", _transit_rotation, EINA_FALSE },
       { "Wipe", _transit_wipe, EINA_FALSE },
       { "Zoom", _transit_zoom, EINA_FALSE },
       { "Resizing", _transit_resizing, EINA_FALSE },
       { NULL, NULL, EINA_FALSE }
};

static void
_checkbox_transition_add(::elm_box box, const char *label, Eina_Bool *checked)
{
::elm_check check(efl::eo::parent = box);
check.size_hint_weight_set( EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
check.size_hint_align_set( 0.0, 0.0);
elm_object_text_set(check._eo_ptr(), label);  // XXX
check.state_pointer_set(checked);
box.pack_end(check);
   check.visibility_set(EINA_TRUE);
}

static void
_transit_start(void *data, Evas_Object *o, void *event_info)
{
   Elm_Transit *trans = NULL;
   int i;
   struct Context *ctxt = data;
   Evas_Object *obj = ctxt->obj;

   ::trans = elm_transit_add();
   ::elm_transit_object_add(trans, obj);

   for (i = 0; _transitions[i].label; i++)
     {
        if (_transitions[i].checked)
          _transitions[i].transition_add_cb(trans);
     }

   ::elm_transit_event_enabled_set(trans, ctxt->events_enabled);
   ::elm_transit_auto_reverse_set(trans, ctxt->auto_reverse);
   ::elm_transit_objects_final_state_keep_set(trans, ctxt->final_state_keep);
   ::elm_transit_tween_mode_set(trans, ctxt->tween_mode);
   ::elm_transit_repeat_times_set(trans, ctxt->repeat_times);

   ::elm_transit_duration_set(trans, 2.0);
   ::elm_transit_go(trans);
}

static void
_object_clicked(void *data, Evas_Object *o, void *event_info)
{
  std::cout << "object clicked!" << std::endl;
}

static void
_cb_repeat_changed(void *data, ::elm_spinner obj, void *event)
{
   int *repeat_cnt = data;

   *repeat_cnt = obj.value_get();
}

static void
_cb_tween_changed(::elm_spinner obj, Evas_Object *obj, void *event)
{
   Elm_Transit_Tween_Mode *mode = data;
   double val = 0.0;

   val = obj.value_get();
   if (val == 1.0)
     *mode = ELM_TRANSIT_TWEEN_MODE_LINEAR;
   else if (val == 2.0)
     *mode = ELM_TRANSIT_TWEEN_MODE_SINUSOIDAL;
   else if (val == 3.0)
     *mode = ELM_TRANSIT_TWEEN_MODE_DECELERATE;
   else if (val == 4.0)
     *mode = ELM_TRANSIT_TWEEN_MODE_ACCELERATE;
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   char buf[PATH_MAX];
   int i;
   struct Context context;

   context.events_enabled = EINA_FALSE;
   context.auto_reverse = EINA_FALSE;
   context.final_state_keep = EINA_FALSE;
   context.repeat_times = 0;
   context.tween_mode = ELM_TRANSIT_TWEEN_MODE_LINEAR;

   elm_app_info_set(elm_main, "elementary", "images/icon_07.png");
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   ::elm_win win(elm_win_util_standard_add("transit", "Transit Example"));
   win.autodel_set(EINA_TRUE);

   ::elm_box box(efl::eo::parent = win);
   box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   win.resize_object_add(box);
   box.visibility_set(EINA_TRUE);

   ::elm_bg dummy(efl::eo::parent = win);
   dummy.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   box.pack_end(dummy);
   dummy.visibility_set(EINA_TRUE);

   ::elm_button obj(efl::eo::parent = win);
   elm_object_text_set(obj._eo_ptr(), "Transformed object!"); // XXX
   ::elm_icon icon(efl::eo::parent = win);
   snprintf(buf, sizeof(buf), "%s/images/icon_07.png", elm_app_data_dir_get());
   icon.file_set(buf, NULL);
   obj.content_set("icon", icon);
   obj.position_set(160, 60);
   obj.evas::object::size_set( 250, 100);
   obj.visibility_set(EINA_TRUE);
   context.obj = obj;

   obj.callback_clicked_add(&_object_clicked);

   ::elm_button btn(efl::eo::parent = win);
   box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_text_set(btn._eo_ptr(), "Transit!");  // XXX
   box.pack_end(btn);
   btn.visibility_set(EINA_TRUE);
   btn.callback_clicked_add(&_transit_start);

   ::elm_box hbox(efl::eo::parent = win);
   hbox.horizontal_set(EINA_TRUE);
   hbox.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_FILL);
   hbox.size_hint_align_set(EVAS_HINT_FILL, 0.0);
   box.pack_end(hbox);
   hbox.visibility_set(EINA_TRUE);

   ::elm_box vbox(efl::eo::parent = win);
   vbox.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_FILL);
   vbox.size_hint_align_set(EVAS_HINT_FILL, 0.0);

   for (i = 0; _transitions[i].label; i++)
     _checkbox_transition_add(vbox, _transitions[i].label,
                              &_transitions[i].checked);

   hbox.pack_end(vbox);
   vbox.visibility_set(EINA_TRUE);

   ::elm_box vbox2(efl::eo::parent = win);
   vbox2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_FILL);
   vbox2.size_hint_align_set(EVAS_HINT_FILL, 0.0);
   hbox.pack_end(vbox2);
   vbox2.visibility_set(EINA_TRUE);

   ::elm_check cbox(efl::eo::parent = win);
   cbox.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   cbox.size_hint_align_set(0.0, 0.0);
   elm_object_text_set(cbox._eo_ptr(), "Events enabled");  // XXX
   cbox.state_pointer_set( &context.events_enabled);
   vbox2.pack_end(cbox);
   cbox.visibility_set(EINA_TRUE);

   ::elm_check cbox2(efl::eo::parent = win);
   cbox2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   cbox2.size_hint_align_set(0.0, 0.0);
   elm_object_text_set(cbox2._eo_ptr(), "Auto reverse"); // XXX
   cbox2.state_pointer_set( &context.events_reverse);
   vbox2.pack_end(cbox2);
   cbox2.visibility_set(EINA_TRUE);

   ::elm_check cbox3(efl::eo::parent = win);
   cbox3.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   cbox3.size_hint_align_set(0.0, 0.0);
   elm_object_text_set(cbox3._eo_ptr(), "Keep final state");// XXX
   cbox3.state_pointer_set( &context.final_state_keep);
   vbox2.pack_end(cbox3);
   cbox3.visibility_set(EINA_TRUE);

   ::elm_spinner spinner(efl::eo::parent = win);
   spinner.style_set("vertical");
   spinner.min_max_set( 0, 4);
   spinner.label_format_set( "%.0f");
   spinner.editable_set( EINA_FALSE);
   spinner.size_hint_weight_set( EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   spinner.size_hint_align_set( 0.0, EVAS_HINT_FILL);
   spinner.callback_changed_add(&_cb_repeat_changed);
   vbox2.pack_end(spinner);
   spinner.visibility_set(EINA_TRUE);

   ::elm_spinner spinner2(efl::eo::parent = win);
   spinner2.style_set("vertical");
   spinner2.min_max_set( 1, 4);
   spinner2.label_format_set( "%.0f");
   spinner2.editable_set( EINA_FALSE);
   spinner2.special_value_add(1, "linear");
   spinner2.special_value_add(2, "sinusoidal");
   spinner2.special_value_add(3, "decelerate");
   spinner2.special_value_add(4, "accelerate");
   spinner2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   spinner2.size_hint_align_set(0.0, EVAS_HINT_FILL);
   spinner2.callback_changed_add(&_cb_tween_changed);
   vbox2.pack_end(spinner2);
   spinner2.visibility_set(EINA_TRUE);

   win.visibility_set(EINA_TRUE);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
