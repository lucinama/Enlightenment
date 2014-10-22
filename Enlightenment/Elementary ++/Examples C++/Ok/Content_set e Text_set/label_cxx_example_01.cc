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

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
 
  ::elm_win win(elm_win_util_standard_add("label", "Label"));
  win.autodel_set(true);
 
  ::elm_label label(efl::eo::parent = win);
  elm_object_text_set(label._eo_ptr(), "Some long text for our label, that is long but ""not too long.");  // XXX
  label.slide_duration_set(3);
  label.slide_mode_set(ELM_LABEL_SLIDE_MODE_ALWAYS);
  label.style_set("slide_bounce");
  label.position_set(0, 20);
  label.evas::object::size_set(200, 15);
  label.visibility_set(true);
 

  ::elm_label label2(efl::eo::parent = win);
  elm_object_text_set(label2._eo_ptr(),"This is the text for our second label, which is"
		      " much longer than the previous one, maybe even "
		      "too long, but maybe not.");    // XXX
  label2.ellipsis_set(true);
  label2.evas::object::size_set(200, 15);
  label2.position_set(0, 30);
  label2.visibility_set(true);
  
  ::elm_label label3(efl::eo::parent = win);
  elm_object_text_set(label3._eo_ptr(), "Some more long text much as before, long but ""not too long."); // XXX
  label3.line_wrap_set(ELM_WRAP_CHAR);
  label3.ellipsis_set(true);
  label3.evas::object::size_set(200, 15);
  label3.position_set (0, 50);
  label3.visibility_set(true);

  ::elm_label label4(efl::eo::parent = win);
  elm_object_text_set(label4._eo_ptr(), "And for this label we choose a different text, "
		      "for no reason other than that we can.");  // XXX
  label4.line_wrap_set(ELM_WRAP_CHAR);
  label4.evas::object::size_set(200, 30);
  label4.position_set (0, 80);
  label4.visibility_set(true);
 

  ::elm_label label5(efl::eo::parent = win);
  elm_object_text_set(label5._eo_ptr(),"And for this label we choose a different text, "
		      "for no reason other than that we can.");  // XXX
  label5.line_wrap_set(ELM_WRAP_WORD);
  label5.evas::object::size_set(200, 40);
  label5.position_set (0, 110);
  label5.visibility_set(true);

  ::elm_label label6(efl::eo::parent = win);
  elm_object_text_set(label6._eo_ptr(),"Short text");   // XXX
  label6.style_set("marker");
  label6.color_set(255, 0, 0, 255);
  label6.evas::object::size_set(200, 15);
  label6.position_set (0, 140);
  label6.visibility_set(true);

  win.evas::object::size_set(200, 170);
  win.visibility_set(true);  
  
  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
