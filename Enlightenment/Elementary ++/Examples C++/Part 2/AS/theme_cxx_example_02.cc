#ifdef HAVE_CONFIG_H
# include <elementary_config.h>
#endif

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

#include <elm_win.eo.hh>
#include <elm_box.eo.hh>
#include <elm_button.eo.hh>

#include <Eina.hh>

static void
_btn_clicked_cb(::elm_button btn, Eo_Event_Description const& desc, void* info)
{
  static int loaded = 1;
  if (loaded)
    elm_theme_overlay_del("./theme_example.edj");
  else
    elm_theme_overlay_add("./theme_example.edj");
  loaded = 1 - loaded;
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  elm_theme_overlay_add("./theme_example.edj");

  ::elm_win win(elm_win_util_standard_add("theme", "Theme example"));
  win.autodel_set(true);

  ::elm_box box(efl::eo::parent = win);
  box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(box);
  box.visibility_set(true);

  ::elm_button btn(efl::eo::parent = win);
  elm_object_text_set(btn._eo_ptr(), "Button 1"); // XXX
  box.pack_end(btn);
  btn.visibility_set(true);
  btn.callback_clicked_add(&_btn_clicked_cb);

  ::elm_button btn2(efl::eo::parent = win);
  elm_object_text_set(btn2._eo_ptr(), "Button 2"); // XXX
  box.pack_end(btn2);
  btn2.visibility_set(true);
  btn2.callback_clicked_add(&_btn_clicked_cb);

  ::elm_button btn3(efl::eo::parent = win);
  elm_object_text_set(btn3._eo_ptr(), "Button 3"); // XXX
  box.pack_end(btn3);
  btn3.visibility_set(true);
  btn3.callback_clicked_add(&_btn_clicked_cb);

  ::elm_button btn4(efl::eo::parent = win);
  elm_object_text_set(btn4._eo_ptr(), "Button 4"); // XXX
  box.pack_end(btn4);
  btn4.visibility_set(true);
  btn4.callback_clicked_add(&_btn_clicked_cb);

  win.evas::object::size_set(300, 320);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
