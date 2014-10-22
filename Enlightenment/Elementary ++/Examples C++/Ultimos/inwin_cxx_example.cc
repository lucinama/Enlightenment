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

  //  ::elm_inwin inwin;
  static const char *styles[] = {
  "default",
    "minimal",
    "minimal_vertical"
    };
  static int current_style = 0;

  static void
  _inwin_hide(::elm_inwin inwin, Evas_Object *obj, void *event)
  {
  if (inwin)
    {
  inwin.visibility_set(EINA_FALSE);
  return;
}
  elm_object_text_set(obj._eo_ptr(), "No inwin!");  // XXX
  elm_object_disabled_set(obj, EINA_TRUE);
}

  static void
  _inwin_destroy(::elm_inwin inwin, Evas_Object *obj, void *event)
  {
  if (inwin)
    {
  inwin.del();
  inwin = NULL;
  return;
}
  elm_object_text_set(obj._eo_ptr(), "No inwin!"); // XXX
  obj.disabled_set(EINA_TRUE);
}

  static void
  _btn_click_cb(void *data, Evas_Object *obj, void *event)
  {
  Evas_Object *o, *parent;

  if (inwin)
    {
  inwin.activate();
  return;
}

  parent = elm_object_top_widget_get(obj);
  ::elm_inwin inwin(efl::eo::parent = parent);
  inwin.style_set(styles[current_style]);
  inwin.visibility_set(EINA_TRUE);

  current_style = (current_style + 1) % 3;

  ::elm_box o(efl::eo::parent = parent);
  o.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  o.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_win_inwin_content_set(inwin._eo_ptr(), o._eo_ptr()); // XXX
  o.visibility_set(true);

  ::elm_label o2(efl::eo::parent = parent);
  elm_object_text_set(o2._eo_ptr(), "Click on the first button to hide the Inwin.<ps>" 
    "Second to destroy it<ps>"); // XXX
  o2.visibility_set(true);

  auto aux = inwin.content_get();
  aux.elm_box_pack_end(o2);

  ::elm_button o3(efl::eo::parent = parent);
  elm_object_text_set(o3_eo_ptr(), "Hide"); // XXX
  o3.visibility_set(true);

  o3.callback_clicked_add(&_inwin_hide);

  aux = inwin.content_get();

  aux.pack_end(o3);

  ::elm_button o4(efl::eo::parent = parent);
  elm_object_text_set(o4_eo_ptr(), "Destroy"); // XXX
  o4.visibility_set(true);
      
  o4.callback_clicked_add(&_inwin_destroy);

  aux = inwin.content_get();
	
  aux.pack_end(o);
}

  static void
  _win_del_cb(void *data, Evas_Object *obj, void *event)
  {
  if (inwin)
    {
  Evas_Object *hover, *o = elm_win_inwin_content_unset(inwin);
  evas_object_del(inwin);
  inwin = NULL;
  hover = elm_hover_add(obj);
  elm_hover_target_set(hover, obj);
  elm_object_part_content_set(hover, "middle", o);  // XXX
  evas_object_show(hover);
  return;
}
  evas_object_del(obj);
}

  static Eina_Bool
  _screenshot_hack_cb(void *data)
  {
  _btn_click_cb(NULL, data, NULL);
  return EINA_FALSE;
}

  EAPI_MAIN int
  elm_main(int argc, char *argv[])
  {
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("inwin-example", "Inwin Example"));
  win.autodel_set(true);

  win.callback_delete_request_add(&_win_del_cb);

  ::elm_box box(efl::eo::parent = win);
  box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(box);
  box.visibility_set(true);

  ::elm_button o(efl::eo::parent = win);
  elm_object_text_set(o._eo_ptr(), "Inwin!");  // XXX
  o.hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  o.size_hint_align_set(0.0, 0.0);
  box.pack_end(o);
  o.visibility_set(true);

  o.callback_clicked_add(&_btn_click_cb);

  if (!strncmp(elm_config_engine_get(), "shot", 4))
    ecore_timer_add(0.1, _screenshot_hack_cb, o);

  win.evas::object::size_set(400, 400);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
  ELM_MAIN()

