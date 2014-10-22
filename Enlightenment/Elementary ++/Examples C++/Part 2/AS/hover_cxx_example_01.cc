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
}

#include <elm_win.eo.hh>
#include <elm_hover.eo.hh>
#include <elm_button.eo.hh>

#include <Eina.hh>
#include <Evas.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

// static void
// _show_hover(void* data,::elm_button obj, Eo_Event_Description const& desc, void* info)
// {
//   data.visibility_set(true);
//   //evas_object_show(data);
// }

// static void
// _hide_hover(void* data, ::elm_button obj, Eo_Event_Description const& desc, void* info)
// {
//   data.visibility_set(false);
//   //evas_object_hide(data);
// }

namespace efl { namespace evas {
    using ::evas::canvas;
    using ::evas::rectangle;
  } }

EAPI_MAIN int
elm_main (int argc, char *argv[])
{

  ::evas_init();

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
 
  ::elm_win win(elm_win_util_standard_add("hover", "Hover"));
  win.autodel_set(true);
		
  efl::evas::rectangle rect(efl::eo::parent = win);
  rect.size_hint_min_set( 25, 25);
  rect.color_set( 255, 0, 0, 255);
  rect.visibility_set(true);

  efl::evas::rectangle rect2(efl::eo::parent = win);
  rect2.size_hint_min_set( 25, 25);
  rect2.color_set( 0, 255, 0, 255);
  rect2.visibility_set(true);

  efl::evas::rectangle rect3(efl::eo::parent = win);
  rect3.size_hint_min_set( 25, 25);
  rect3.color_set( 0, 0, 255, 255);
  rect3.visibility_set(true);

  ::elm_button bt(efl::eo::parent = win);
  elm_object_text_set(bt._eo_ptr(), "Show hover"); // XXX
  bt.position_set(60, 90);
  bt.evas::object::size_set(80, 20);
  bt.visibility_set(true);

  ::elm_button bt2(efl::eo::parent = win);
  elm_object_text_set(bt2._eo_ptr(), "Hide hover"); // XXX
  bt2.visibility_set(true);

  ::elm_hover hover(efl::eo::parent = win);
  //elm_hover_parent_set(hover, win);
  hover.target_set(bt);

  hover.style_set("popout");

  hover.content_set("left", rect);
  hover.content_set("top", rect2);
  hover.content_set("right", rect3);
  hover.content_set("middle", bt2);

  // bt.callback_clicked_add(&_show_hover);
  // bt2.callback_clicked_add(&_hide_hover);

  win.evas::object::size_set(200, 200);
  win.visibility_set(true);
  
  elm_run();
  elm_shutdown();
  
  return 0;
}
ELM_MAIN()
