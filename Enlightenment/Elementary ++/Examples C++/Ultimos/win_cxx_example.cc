extern "C"
{
#ifdef HAVE_CONFIG_H
#include <elementary_config.h>
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
#include "elm_interface_atspi_text.h"
#include "elm_interface_scrollable.h"
}

#include <Elementary.hh>
#include <Eina.hh>

#include <iostream>

static void
_btn_activate_cb(::elm_win data, void *event)
{
  data.activate();
}

static void
_btn_lower_cb(::elm_win data, Evas_Object *obj, void *event)
{
  data.lower();
}

static void
_btn_raise_cb(::elm_win data, Evas_Object *obj, void *event)
{
  data.raise();
}

static void
_btn_borderless_cb(::elm_win data, Evas_Object *obj, void *event)
{
  Eina_Bool flag = data.borderless_get();
  data.borderless_set(!flag);
}

static void
_btn_shaped_cb(::elm_win data, Evas_Object *obj, void *event)
{
  Eina_Bool flag = data.shaped_get();
  data.shaped_set(!flag);
}

static void
_btn_alpha_cb(::elm_win data, Evas_Object *obj, void *event)
{
  Eina_Bool flag = data.alpha_get();
  data.alpha_set(!flag);
}

static void
_btn_fullscreen_cb(::elm_win data, Evas_Object *obj, void *event)
{
  Eina_Bool flag = data.fullscreen_get();
  data.fullscreen_set(!flag);
}

static void
_btn_maximized_cb(::elm_win data, Evas_Object *obj, void *event)
{
  Eina_Bool flag = data.maximized_get();
  data.maximized_set(!flag);
}

static void
_btn_iconified_cb(::elm_win data, Evas_Object *obj, void *event)
{
  Eina_Bool flag = data.iconified_get();
  data.iconified_set(!flag);
}

static void
_btn_rotation_cb(::elm_win data, Evas_Object *obj, void *event)
{
  int angle = data.rotation_get();
  angle = (angle + 90) % 360;
  data.rotation_set(angle);
}

static void
_btn_rotation_resize_cb(::elm_win data, Evas_Object *obj, void *event)
{
  int angle = data.rotation_get();
  angle = (angle + 90) % 360;
  data.rotation_with_resize_set(angle);
}

static void
_btn_sticky_cb(::elm_win data, Evas_Object *obj, void *event)
{
  Eina_Bool flag = data.sticky_get();
  data.sticky_set(!flag);
}

static void
_yes_quit_cb(::elm_win data, Evas_Object *obj, void *event)
{
  elm_exit();
}

static void
_no_quit_cb(::elm_win data, Evas_Object *obj, void *event)
{
  data.del();
}

static void
_main_win_del_cb(::elm_win obj, void *event)
{
  ::elm_notify msg(efl::eo::parent = obj);
  msg.align_set(0.5, 0.5);
  msg.allow_events_set(EINA_FALSE);
  msg.visibility_set(EINA_TRUE);

  ::elm_box box(efl::eo::parent = obj);
  box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  box.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_object_content_set(msg._eo_ptr(), box._eo_ptr()); // XXX
  box.visibility_set(EINA_TRUE);

  ::elm_label lbl(efl::eo::parent = obj);
  elm_object_text_set(lbl._eo_ptr(), "Really want quit?");  // XXX
  lbl.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  lbl.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box.pack_end(lbl);
  lbl.visibility_set(EINA_TRUE);

  ::elm_separator sep(efl::eo::parent = obj);
  sep.horizontal_set(EINA_TRUE);
  box.pack_end(sep);
  sep.visibility_set(EINA_TRUE);

  ::elm_box box2(efl::eo::parent = obj);
  box2.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
  box2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box.pack_end(box2);
  box2.visibility_set(EINA_TRUE);

  ::elm_button btn(efl::eo::parent = obj);
  elm_object_text_set(btn._eo_ptr(), "Yes");  // XXX
  box2.pack_end(btn);
  btn.visibility_set(EINA_TRUE);

  btn.callback_clicked_add(&_yes_quit_cb);

  ::elm_button btn2(efl::eo::parent = obj);
  elm_object_text_set(btn2._eo_ptr(), "No");  // XXX
  box2.pack_end(btn2);
  btn2.visibility_set(EINA_TRUE);
  
  btn2.callback_clicked_add(&_no_quit_cb);
}

static void
_force_focus_cb(::elm_win data, Evas_Object *obj, void *event)
{
#ifdef HAVE_ELEMENTARY_X
  Ecore_X_Window xwin = data.xwindow_get();
  ecore_x_window_focus(xwin);
#endif
}

static void
_win_focused_cb(void *data, Evas_Object *obj, void *event)
{
  const char *name = data;
  std::cout << "Window focused: " << name << std::endl;
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
  char buf[256];

  elm_app_info_set(elm_main, "elementary", "images/logo.png");

  ::elm_win win(elm_win_util_standard_add("win-example", "Elm_Win Example"));
  win.focus_highlight_enabled_set(EINA_TRUE);

  win.callback_focus_in_add(&_win_focused_cb);

  win.callback_delete_request_add(&_main_win_del_cb);

  ::elm_box bigbox(efl::eo::parent = win);
  bigbox.horizontal_set(EINA_TRUE);
  bigbox.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bigbox);
  bigbox.visibility_set(EINA_TRUE);

  ::elm_box box(efl::eo::parent = win);
  box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  box.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bigbox.pack_end(box);
  box.visibility_set(EINA_TRUE);

  //::elm_win win(elm_win_util_standard_add("win-example", "Elm_Win Example"));
  ::elm_win win2(;
  win2 = elm_win_add(NULL, "sub-win-example", ELM_WIN_DIALOG_BASIC);
  win2.autodel_set(EINA_TRUE);
  win2.title_set("Managed window");
  win2.visibility_set(EINA_TRUE);

  win2.callback_focus_in_add(&_win_focused_cb);

  ::elm_icon o(efl::eo::parent = win2);
  sprintf(buf, "%s/images/logo.png", elm_app_data_dir_get());
  o.file_set(buf, NULL);
  o.resizable_set(o, EINA_FALSE, EINA_FALSE);
  o.no_scale_set(o, EINA_TRUE);
  win2.resize_object_add(o);
  o.visibility_set(EINA_TRUE);

  ::elm_label lb(efl::eo::parent = win);
  elm_object_text_set(lb._eo_ptr(), "<b>Managed Window</b>"); // XXX
  box.pack_end(lb);
  lb.visibility_set(EINA_TRUE);

#define WIN_ACTION(name)				\
  do {							\
    ::elm_button btn(efl::eo::parent = win);		\
    elm_object_text_set(btn._eo_ptr(), #name);		\
    box.pack_end(btn);					\
    btn.visibility_set(EINA_TRUE);			\
    btn.callback_clicked_add(&_btn_##name##_cb);	\
  } while (0)

  WIN_ACTION(activate);
  WIN_ACTION(lower);
  WIN_ACTION(raise);
  WIN_ACTION(borderless);
  WIN_ACTION(shaped);
  WIN_ACTION(alpha);
  WIN_ACTION(fullscreen);
  WIN_ACTION(maximized);
  WIN_ACTION(iconified);
  WIN_ACTION(rotation);
  WIN_ACTION(rotation_resize);
  WIN_ACTION(sticky);

  ::elm_box box2(efl::eo::parent = win);
  box2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  box2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bigbox.pack_end(box2);
  box2.visibility_set(EINA_TRUE);

  ::elm_win win3(elm_win_util_standard_add("sub-win-example2", "Non-managed window"));
  win3.autodel_set(EINA_TRUE);
  win3.override_set(EINA_TRUE);
  win3.visibility_set(EINA_TRUE);

  win3.callback_focus_in_add(&_win_focused_cb);

  ::elm_box bigbox2(efl::eo::parent = win);
  bigbox2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bigbox2);
  bigbox2.visibility_set(EINA_TRUE);
   
  ::elm_label lb2(efl::eo::parent = win3);
  elm_object_text_set(lb._eo_ptr(), "This window should have no borders or titlebar.<ps>"
		      "It was set in override mode, so the Window Manager<ps>"
		      "should ignore everything about it.<ps>"
		      "It's up to the program to handle it properly, and some"
		      "of the actions performed on it may not have any effect."
                      ); // XXX
  bigbox2.pack_end(lb2);
  lb2.visibility_set(EINA_TRUE);

  ::elm_entry en(efl::eo::parent = win3);
  elm_object_text_set(en._eo_ptr(), "See if you can focus me"); // XXX
  en.single_line_set(EINA_TRUE);
  en.scrollable_set(EINA_TRUE);
  en.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
  en.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bigbox2.pack_end(en);
  en.visibility_set(EINA_TRUE);

  ::elm_separator sep(efl::eo::parent = win3);
  sep.horizontal_set(EINA_TRUE);
  bigbox2.pack_end(sep);
  sep.visibility_set(EINA_TRUE);

  ::elm_button bt(efl::eo::parent = win3);
  elm_object_text_set(bt.eo_ptr(), "Focus me"); // XXX
  bigbox2.pack_end(bt);
  bt.visibility_set(EINA_TRUE);

  bt.callback_clicked_add(&_force_focus_cb);

  ::elm_label lb2(efl::eo::parent = win3);
  elm_object_text_set(lb2._eo_ptr(), "<b>Override Window</b>");
  box2.pack_end(lb2);
  lb2.visibility_set(EINA_TRUE);

  WIN_ACTION(activate);
  WIN_ACTION(lower);
  WIN_ACTION(raise);
  WIN_ACTION(borderless);
  WIN_ACTION(shaped);
  WIN_ACTION(alpha);
  WIN_ACTION(fullscreen);
  WIN_ACTION(maximized);
  WIN_ACTION(iconified);
  WIN_ACTION(rotation);
  WIN_ACTION(rotation_resize);
  WIN_ACTION(sticky);

  win.evas::object::size_set(400, 400);
  win.visibility_set(EINA_TRUE);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
