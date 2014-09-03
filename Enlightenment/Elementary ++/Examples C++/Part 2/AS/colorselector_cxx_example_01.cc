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
#include <elm_colorselector.eo.hh>
#include <elm_box.eo.hh>
#include <elm_frame.eo.hh>

#include <Eina.hh>
#include <Evas.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

void _change_color(::elm_colorselector obj, Eo_Event_Description const& desc, void* info);
void _colorpalette_clicked_cb(::elm_colorselector obj, Eo_Event_Description const& desc, void* info);
void _colorpalette_longpressed_cb(::elm_colorselector obj, Eo_Event_Description const& desc, void* info);

namespace efl { namespace evas {
    using ::evas::canvas;
    using ::evas::rectangle;
  } }

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
	::evas_init();	
	
   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	::elm_win win(elm_win_util_standard_add("color selector", "Color selector"));
	win.autodel_set(true);

  	::elm_box bx(efl::eo::parent = win);
  	bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  	win.resize_object_add(bx);
  	bx.visibility_set(true);

	::elm_frame fr(efl::eo::parent = win);
	fr.size_hint_weight_set( 1.0, 0.5);
	fr.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(fr._eo_ptr(), "Color View");  //XXXX
	bx.pack_end(fr);
	fr.visibility_set(true);

  	efl::evas::rectangle rect(efl::eo::parent = win);
	elm_object_content_set(fr._eo_ptr(), rect._eo_ptr()); 	//XXXX
  	rect.color_set( 255, 90, 18, 255);
  	rect.visibility_set(true);

	::elm_frame fr2(efl::eo::parent = win);
	fr2.size_hint_weight_set( 1.0, 0.5);
	fr2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(fr2._eo_ptr(), "Color Selector");	//XXXX
	bx.pack_end(fr2);
	fr2.visibility_set(true);
	
	::elm_colorselector cs(efl::eo::parent = win);
  	cs.palette_name_set("painting");
  	cs.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
	cs.size_hint_align_set(EVAS_HINT_FILL, 0.0);
   	cs.color_set(255, 90, 18, 255);
	cs.visibility_set(true);
   	cs.callback_changed_add(&_change_color);
   	cs.callback_color_item_selected_add(&_colorpalette_clicked_cb);
   	cs.callback_color_item_longpressed_add(&_colorpalette_longpressed_cb);
   	elm_object_content_set(fr._eo_ptr(), cs._eo_ptr());

   	win.evas::object::size_set(320, 480);
  	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()

void
_change_color(::elm_colorselector obj, Eo_Event_Description const& desc, void* info)
{
   int r, g, b, a;
   obj.color_get(&r, &g, &b, &a);
   evas_color_argb_premul(a, &r, &g, &b);
   //data.color_set(r, g, b, a);
}

void
_colorpalette_clicked_cb(::elm_colorselector obj, Eo_Event_Description const& desc, void* info)
{
   int r = 0, g = 0, b = 0 ,a = 0;
   Elm_Object_Item *color_it = (Elm_Object_Item *) info;
   elm_colorselector_palette_item_color_get(color_it, &r, &g, &b, &a);
   evas_color_argb_premul(a, &r, &g, &b);
   //data.color_set(data, r, g, b, a);
}

void
_colorpalette_longpressed_cb(::elm_colorselector obj, Eo_Event_Description const& desc, void* info)
{
   int r = 0,g = 0,b = 0 ,a = 0;
   //Elm_Object_Item *color_it = (Elm_Object_Item *) info;
   //elm_colorselector_palette_item_color_get(color_it, &r, &g, &b, &a);
   std::cout << std::endl << "color = " << r << " - " << g << "- " << b << "- " << a << std::endl;
}
