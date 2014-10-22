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
#include <Evas.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

namespace efl { namespace evas {
    using ::evas::canvas;
    using ::evas::rectangle;
  } }

static void
_transit_flip(Elm_Transit *trans)
{
   elm_transit_effect_flip_add(trans, ELM_TRANSIT_EFFECT_FLIP_AXIS_X, EINA_TRUE);
}

static void
_transit_blend(Elm_Transit *trans)
{
   elm_transit_effect_blend_add(trans);
}

static void
_transit_fade(Elm_Transit *trans)
{
   elm_transit_effect_fade_add(trans);
}

static void
_transit_resizable_flip(Elm_Transit *trans)
{
   elm_transit_effect_resizable_flip_add(
      trans, ELM_TRANSIT_EFFECT_FLIP_AXIS_Y, EINA_TRUE);
}

static struct {
     const char *label;
     void (*transition_add_cb)(Elm_Transit *);
     Eina_Bool checked;
} _transitions[] = {
       { "Flip", _transit_flip, EINA_FALSE },
       { "Blend", _transit_blend, EINA_FALSE },
       { "Fade", _transit_fade, EINA_FALSE },
       { "Resizable Flip", _transit_resizable_flip, EINA_FALSE },
       { NULL, NULL, EINA_FALSE }
};

static void
_checkbox_transition_add(::elm_box box, const char *label, Eina_Bool *checked)
{
  ::elm_check check(efl::eo::parent = box);
   check.size_hint_weight_set( EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   check.size_hint_align_set( 0.0, 0.0);
   elm_object_text_set(check._eo_ptr(), label); // XXX
   check.state_pointer_set(checked);
   box.pack_end(check);
   check.visibility_set(EINA_TRUE);
}

static void
_transit_start(void *data, Evas_Object *o, void *event_info)
{
  Elm_Transit *trans = NULL;
  Eina_List *objs = data, *l;
  Evas_Object *obj;
  int i;

  trans = ::elm_transit_add();
  EINA_LIST_FOREACH(objs, l, obj)
    ::elm_transit_object_add(trans, obj);

  for (i = 0; _transitions[i].label; i++)
    {
      if (_transitions[i].checked)
	_transitions[i].transition_add_cb(trans);
    }

  ::elm_transit_duration_set(trans, 2.0);
  ::elm_transit_go(trans);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
  Eina_List *objs = NULL;
  char buf[PATH_MAX];
  int i;

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
  elm_app_info_set(elm_main, "elementary", "images/icon_07.png");

  ::elm_win win(elm_win_util_standard_add("transit", "Transit Example"));
  win.autodel_set(EINA_TRUE);

  ::elm_box box(efl::eo::parent = win);
  box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(box);
  box.visibility_set(EINA_TRUE);

  ::elm_button btn(efl::eo::parent = win);
  btn.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
  btn.size_hint_align_set(EVAS_HINT_FILL, 0.0);
  elm_object_text_set(btn._eo_ptr(), "Transformed object!"); // XXX
  ::elm_icon icon(efl::eo::parent = win);
  snprintf(buf, sizeof(buf), "%s/images/icon_07.png", elm_app_data_dir_get());
  icon.file_set(buf, NULL);
  btn.content_set("icon", icon);
  btn.position_set(50, 50);
  btn.evas::object::size_set( 200, 50);
  btn.visibility_set(EINA_TRUE);

  objs = eina_list_append(objs, btn);  // XXX

  ::elm_button btn2(efl::eo::parent = win);
  btn2.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
  btn2.size_hint_align_set(EVAS_HINT_FILL, 0.0);
  elm_object_text_set(btn2._eo_ptr(), "Another object!"); // XXX
  ::elm_icon icon2(efl::eo::parent = win);
  snprintf(buf, sizeof(buf), "%s/images/icon_08.png", elm_app_data_dir_get());
  icon2.file_set(buf, NULL);
  btn2.content_set("icon", icon2);
  btn2.position_set(50, 50);
  btn2.evas::object::size_set( 200, 50);
  btn2.visibility_set(EINA_TRUE);

  objs = eina_list_append(objs, btn2);

  ::elm_box hbox(efl::eo::parent = win);
  hbox.horizontal_set(EINA_TRUE);
  hbox.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
  hbox.size_hint_align_set(EVAS_HINT_FILL, 0.0);
  box.pack_end(hbox);
  hbox.visibility_set(EINA_TRUE);

  for (i = 0; _transitions[i].label; i++)
    _checkbox_transition_add(hbox, _transitions[i].label, &_transitions[i].checked);

  ::elm_button btn3(efl::eo::parent = win);
  btn3.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_object_text_set(btn3._eo_ptr(), "Transit!");  // XXX
  hbox.pack_end(btn3);
  btn3.visibility_set(EINA_TRUE);

  bt3.callback_clicked_add(&_transit_start);

  efl::evas::rectangle rect(efl::eo::parent = win);
  rect.color_set( 0, 0, 0, 0);
  rect.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  rect.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box.pack_end(rect);
  rect.visibility_set(EINA_TRUE);

  win.evas::object::size_set(300, 100);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
