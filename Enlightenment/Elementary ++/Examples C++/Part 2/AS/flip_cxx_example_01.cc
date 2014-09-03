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
#include <elm_radio.eo.hh>
#include <elm_flip.eo.hh>

#include <Eina.hh>
#include <Evas.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

static void _change_interaction(::elm_radio obj, Eo_Event_Description const& desc, void* info);

namespace efl { namespace evas {
    using ::evas::canvas;
    using ::evas::rectangle;
  } }

EAPI_MAIN int
elm_main (int argc, char *argv[])
{ 
	::evas_init();
	
	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
 
	::elm_win win(elm_win_util_standard_add("flip", "Flip"));
	win.autodel_set(true);
	
	efl::evas::rectangle rect(efl::eo::parent = win);
	rect.evas::object::size_set(150, 150);
	rect.color_set(0, 0, 255, 255);
  	rect.visibility_set(true);
  	  		
	efl::evas::rectangle rect2(efl::eo::parent = win);
	rect2.color_set(0, 255, 0, 255);
  	rect2.visibility_set(true);
  	
 	::elm_flip flip(efl::eo::parent = win);
 	flip.content_set("front", rect);
   	flip.content_set("back", rect2);
	flip.evas::object::size_set(150, 150);
	flip.position_set(10, 10);
  	flip.visibility_set(true);

   	flip.interaction_set(ELM_FLIP_INTERACTION_PAGE);
   	flip.interaction_direction_enabled_set(ELM_FLIP_DIRECTION_UP, true);
   	flip.interaction_direction_enabled_set(ELM_FLIP_DIRECTION_DOWN, true);
   	flip.interaction_direction_enabled_set(ELM_FLIP_DIRECTION_LEFT, true);
   	flip.interaction_direction_enabled_set(ELM_FLIP_DIRECTION_RIGHT, true);
   	flip.interaction_direction_hitsize_set(ELM_FLIP_DIRECTION_UP, 1);
   	flip.interaction_direction_hitsize_set(ELM_FLIP_DIRECTION_DOWN, 1);
   	flip.interaction_direction_hitsize_set(ELM_FLIP_DIRECTION_LEFT, 1);
   	flip.interaction_direction_hitsize_set(ELM_FLIP_DIRECTION_RIGHT, 1);

 	::elm_radio radio(efl::eo::parent = win);
   	elm_object_text_set(radio._eo_ptr(), "page");		//XXXX
   	radio.value_set(ELM_FLIP_INTERACTION_PAGE);
   	radio.state_value_set(ELM_FLIP_INTERACTION_PAGE);
   	radio.evas::object::size_set(radio, 55, 30);
   	radio.position_set(10, 160);
   	radio.visibility_set(true);
   	radio.callback_changed_add(&_change_interaction);
 
  	::elm_radio radio2(efl::eo::parent = win);
   	elm_object_text_set(radio2._eo_ptr(), "cube");		//XXXX
   	radio2.state_value_set(ELM_FLIP_INTERACTION_CUBE);
   	radio2.group_add(radio);
	radio2.evas::object::size_set(55, 30);
   	radio2.position_set(75, 160);
   	radio2.visibility_set(true);
   	radio2.callback_changed_add(&_change_interaction);
   	
   	::elm_radio radio3(efl::eo::parent = win);
   	elm_object_text_set(radio3._eo_ptr(), "rotate");		//XXXX
   	radio3.state_value_set(ELM_FLIP_INTERACTION_ROTATE);
   	radio3.group_add(radio);
	radio3.evas::object::size_set(55, 30);
   	radio3.position_set(140, 160);
   	radio3.visibility_set(true);
   	radio3.callback_changed_add(&_change_interaction);
  
   	win.evas::object::size_set(200, 200);
  	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()

void
_change_interaction(::elm_radio obj, Eo_Event_Description const& desc, void* info);
{
   flip.interaction_set(data, obj.state_value_get());
   flip.go(data, ELM_FLIP_ROTATE_XZ_CENTER_AXIS);
}

