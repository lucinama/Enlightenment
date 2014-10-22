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

static void _hide(::elm_notify obj, Eo_Event_Description const& desc, void* info);

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("notify", "Notify"));
  win.autodel_set(true);
  
  ::elm_box bx(efl::eo::parent = win);
  bx.horizontal_set(false);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);

  ::elm_label content(efl::eo::parent = win);
  elm_object_text_set(content._eo_ptr(), "default"); // XXX
  content.visibility_set(true);

  ::elm_notify notify(efl::eo::parent = win);
  notify.allow_events_set(false);
  notify.timeout_set( 5);
  elm_object_content_set(notify._eo_ptr(), content._eo_ptr()); // XXX
  notify.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  notify.visibility_set(true);
  bx.pack_end(notify);
  notify.callback_block_clicked_add(&_hide);

  ::elm_label content2(efl::eo::parent = win);
  elm_object_text_set(content2._eo_ptr(), "bottom"); // XXX
  content2.visibility_set(true);

  ::elm_notify notify2(efl::eo::parent = win);
  notify2.align_set( 0.5, 1.0);
  elm_object_content_set(notify2._eo_ptr(), content2._eo_ptr()); // XXX
  notify2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  notify2.visibility_set(true);
  bx.pack_end(notify2);

  ::elm_label content3(efl::eo::parent = win);
  elm_object_text_set(content3._eo_ptr(), "center"); // XXX
  content3.visibility_set(true);

  ::elm_notify notify3(efl::eo::parent = win);
  notify3.align_set( 0.5, 0.5);
  elm_object_content_set(notify3._eo_ptr(), content3._eo_ptr()); // XXX
  notify3.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  notify3.visibility_set(true);
  bx.pack_end(notify3);

  win.evas::object::size_set(100, 200);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()

static void
_hide(::elm_notify obj, Eo_Event_Description const& desc, void* info)
{
  obj.visibility_set(false);
}
