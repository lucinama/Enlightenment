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
#include <elm_actionslider.eo.hh>

#include <Eina.hh>

#include <iostream>

static void _pos_selected_cb(::elm_actionslider obj, Eo_Event_Description const& desc, void* info)
{
   std::cout << "Selection: " << (char *)info << std::endl;
   std::cout << "Label selected: " << obj.selected_label_get() << std::endl;
}

static void
_position_change_magnetic_cb(::elm_actionslider obj, Eo_Event_Description const& desc, void* info)
{
   if (!strcmp((char *)info, "left"))
     obj.magnet_pos_set(ELM_ACTIONSLIDER_LEFT);
   else if (!strcmp((char *)info, "right"))
     obj.magnet_pos_set(ELM_ACTIONSLIDER_RIGHT);
}

static void
_magnet_enable_disable_cb(::elm_actionslider obj, Eo_Event_Description const& desc, void* info)
{
   	if (!strcmp((char *)info, "left"))
     	obj.magnet_pos_set(ELM_ACTIONSLIDER_CENTER);
	else if (!strcmp((char *)info, "right"))
     	obj.magnet_pos_set(ELM_ACTIONSLIDER_NONE);
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	::elm_win win(elm_win_util_standard_add("actionslider", "Actionslider"));
  	win.autodel_set(true);

 	::elm_box bx(efl::eo::parent = win);
	bx.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
   	win.resize_object_add(bx);
   	bx.visibility_set(true);

	::elm_actionslider as(efl::eo::parent = win);
   	as.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
   	as.size_hint_align_set(EVAS_HINT_FILL, 0);
   	as.indicator_pos_set(ELM_ACTIONSLIDER_RIGHT);
   	as.magnet_pos_set( ELM_ACTIONSLIDER_RIGHT);
   	as.text_set("left", "Snooze");			// XXX
   	as.text_set("right", "Stop"); 			// XXX

	int position = ELM_ACTIONSLIDER_LEFT | ELM_ACTIONSLIDER_RIGHT;

   	as.enabled_pos_set(static_cast<Elm_Actionslider_Pos>(position));
   	//as.callback_pos_changed_add(&_position_change_magnetic_cb);
   	//as.callback_selected_add(&_pos_selected_cb);
   	as.visibility_set(true);
	bx.pack_end(as);

	::elm_actionslider as2(efl::eo::parent = win);
   	as2.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
   	as2.size_hint_align_set(EVAS_HINT_FILL, 0);
   	as2.indicator_pos_set(ELM_ACTIONSLIDER_CENTER);
   	as2.magnet_pos_set(ELM_ACTIONSLIDER_CENTER);
   	as2.text_set("left", "Snooze");			// XXX
   	as2.text_set("right", "Stop");		// XXX
	as2.enabled_pos_set(static_cast<Elm_Actionslider_Pos>(position));
   	//as2.callback_selected_add(&_pos_selected_cb);
  	as2.visibility_set(true);
	bx.pack_end(as2);

	::elm_actionslider as3(efl::eo::parent = win);
	as3.style_set("bar");
   	as3.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
   	as3.size_hint_align_set(EVAS_HINT_FILL, 0);
   	as3.indicator_pos_set(ELM_ACTIONSLIDER_LEFT);
	int position2 = ELM_ACTIONSLIDER_CENTER | ELM_ACTIONSLIDER_RIGHT;
   	as3.magnet_pos_set(static_cast<Elm_Actionslider_Pos>(position2));
   	as3.enabled_pos_set(static_cast<Elm_Actionslider_Pos>(position2));
   	as3.text_set("center", "Accept");		// XXX
   	as3.text_set("right", "Reject");		// XXX
   	//as3.callback_selected_add(&_pos_selected_cb);
   	as3.visibility_set(true);
	bx.pack_end(as3);
  
  	::elm_actionslider as4(efl::eo::parent = win);
	as4.style_set("bar");
   	as4.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
   	as4.size_hint_align_set(EVAS_HINT_FILL, 0);
   	as4.indicator_pos_set(ELM_ACTIONSLIDER_LEFT);
   	as4.magnet_pos_set(ELM_ACTIONSLIDER_LEFT);
   	as4.text_set("center", "Accept");		// XXX
   	as4.text_set("right", "Reject"); 		// XXX
   	elm_object_text_set(as4._eo_ptr(), "Go");		// XXX
   	//as4.callback_pos_changed_add(&_position_change_magnetic_cb);
   	//as4.callback_selected_add(&_pos_selected_cb);
 

	::elm_actionslider as5(efl::eo::parent = win);
   	as5.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
   	as5.size_hint_align_set(EVAS_HINT_FILL, 0);
   	as5.indicator_pos_set(ELM_ACTIONSLIDER_LEFT);
   	as5.magnet_pos_set(ELM_ACTIONSLIDER_ALL);
   	as5.text_set("left", "Left");			// XXX
   	as5.text_set("center", "Center"); 		// XXX
   	as5.text_set("right", "Right");			// XXX
   	elm_object_text_set(as5._eo_ptr(), "Go");		// XXX
   	//as5.callback_selected_add(&_pos_selected_cb);
	as5.visibility_set(true);
	bx.pack_end(as5);

	::elm_actionslider as6(efl::eo::parent = win);
   	as6.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
   	as6.size_hint_align_set(EVAS_HINT_FILL, 0);
   	as6.indicator_pos_set(ELM_ACTIONSLIDER_LEFT);
   	as6.magnet_pos_set(ELM_ACTIONSLIDER_ALL);
   	as6.text_set("left", "Enable");			// XXX
   	as6.text_set("center", "Magnet"); 		// XXX
   	as6.text_set("right", "Disable");		// XXX
	//as6.callback_pos_changed_add(&_magnet_enable_disable_cb);
   	//as6.callback_selected_add(&_pos_selected_cb);
	as6.visibility_set(true);
	bx.pack_end(as6);

   	win.evas::object::size_set(320, 400);
   	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();
   	return 0;
}
ELM_MAIN()
