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
#include <elm_thumb.eo.hh>

#include <Eina.hh>

#include <iostream>
#include <sstream>

static void
_generation_started_cb(::elm_thumb obj, Eo_Event_Description const& desc, void* info)
{
   std::cout << "thumbnail generation started." << std::endl;
}

static void
_generation_finished_cb(::elm_thumb obj, Eo_Event_Description const& desc, void* info)
{
   std::cout << "thumbnail generation finished." << std::endl;
}

static void
_generation_error_cb(::elm_thumb obj, Eo_Event_Description const& desc, void* info)
{
   std::cout << "thumbnail generation error." << std::endl;
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
   	elm_need_ethumb();

	elm_app_compile_data_dir_set("/home/luciana/Enlightenment/local/share/elementary/");
	elm_app_info_set(reinterpret_cast<void*>(elm_main), "elementary", "images/plant_01.jpg");
   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

 	::elm_win win(elm_win_util_standard_add("thumb", "Thumbnailer"));
  	win.autodel_set(true);

   	::elm_thumb thumb(efl::eo::parent = win);

   	thumb.callback_generate_start_add(&_generation_started_cb);
   	thumb.callback_generate_stop_add(&_generation_finished_cb);
   	thumb.callback_generate_error_add(&_generation_error_cb);

   	thumb.size_set(160, 160);
   	thumb.editable_set(false);
	std::stringstream ss;
	ss << elm_app_data_dir_get() << "/images/plant_01.jpg";
	thumb.file_set(ss.str(), "image");
   	thumb.reload();

   	thumb.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(thumb);
	thumb.visibility_set(true);

  	win.evas::object::size_set(320, 320);
   	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   return 0;
}
ELM_MAIN()

