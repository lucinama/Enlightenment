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

extern "C"
{
#include <Eo.h>
#include <Evas.h>
#include <Elementary.h>
#include <elm_widget.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_scrollable.h"
}

#include <elm_win.eo.hh>
#include <elm_panel.eo.hh>
#include <elm_label.eo.hh>
#include <elm_box.eo.hh>

#include <Eina.hh>

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("panel", "Panel"));
  win.autodel_set(true);

  ::elm_box bx(efl::eo::parent = win);
  bx.horizontal_set(false);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);

  ::elm_panel panel(efl::eo::parent = win);
  panel.orient_set(ELM_PANEL_ORIENT_TOP);
  panel.toggle();
  panel.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  panel.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  panel.visibility_set(true);
  bx.pack_end(panel);

  ::elm_label content(efl::eo::parent = win);
  elm_object_text_set(content._eo_ptr(), "content"); // XXX
  content.visibility_set(true);
  elm_object_content_set(panel._eo_ptr(), content._eo_ptr()); // XXX

  ::elm_panel panel2(efl::eo::parent = win);
  panel2.orient_set(ELM_PANEL_ORIENT_RIGHT);
  panel2.hidden_set(true);
  panel2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  panel2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  panel2.visibility_set(true);
  bx.pack_end(panel2);

  ::elm_label content2(efl::eo::parent = win);
  elm_object_text_set(content2._eo_ptr(), "content2"); // XXX
  content2.visibility_set(true);
  elm_object_content_set(panel2._eo_ptr(), content2._eo_ptr()); // XXX

  ::elm_panel panel3(efl::eo::parent = win);
  panel3.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  panel3.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  panel3.visibility_set(true);
  bx.pack_end(panel3);

  ::elm_label content3(efl::eo::parent = win);
  elm_object_text_set(content3._eo_ptr(), "content3"); // XXX
  content3.visibility_set(true);
  elm_object_content_set(panel3._eo_ptr(), content3._eo_ptr()); // XXX

  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
