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

void
_bla(::elm_bubble obj, Eo_Event_Description const& desc EINA_UNUSED, void* info EINA_UNUSED)
{
  static unsigned char corner = 0;
  ++corner;
  if (corner > 3)
    obj.pos_set(ELM_BUBBLE_POS_TOP_LEFT);
  else
    obj.pos_set(static_cast<Elm_Bubble_Pos>(corner));
}

namespace efl { namespace evas {
    using ::evas::canvas;
    using ::evas::rectangle;
  } }

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  ::evas_init();

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
 
  ::elm_win win(elm_win_util_standard_add("bubble", "Bubble"));
  win.autodel_set(true);

  ::elm_label label1(efl::eo::parent = win);
  elm_object_text_set(label1._eo_ptr(), "Bubble with no icon, info or label");
  label1.visibility_set(true);
		
  efl::evas::rectangle icon(efl::eo::parent = win);
  icon.color_set( 0, 0, 255, 255);
  icon.visibility_set(true);

  elm_bubble bubble1(efl::eo::parent = win);
  bubble1.content_set("icon", icon);
  bubble1.text_set("info", "INFO");
  elm_object_text_set(bubble1._eo_ptr(), "LABEL");  
  elm_object_content_set(bubble1._eo_ptr(), label1._eo_ptr());
  bubble1.evas::object::size_set(300, 100);
  bubble1.visibility_set(true);

  bubble1.callback_clicked_add(&_bla);

  ::elm_label label2(efl::eo::parent = win);
  elm_object_text_set(label2._eo_ptr(), "Bubble with no icon, info or label");
  label2.visibility_set(true);

  ::elm_bubble bubble2(efl::eo::parent = win);
  elm_object_content_set(bubble2._eo_ptr(), label2._eo_ptr()); // XXX
  bubble2.evas::object::size_set(200, 50);
  bubble2.position_set(0, 110);
  bubble2.visibility_set(true);

  win.evas::object::size_set(300, 200);
  win.visibility_set(true);
  
  elm_run();
  elm_shutdown();
  
  return 0;
}
ELM_MAIN()
