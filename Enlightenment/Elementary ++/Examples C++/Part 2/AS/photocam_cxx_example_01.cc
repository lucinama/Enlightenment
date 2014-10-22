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

#include <sstream>
#include <iostream>

#include <elm_win.eo.hh>
#include <elm_photocam.eo.hh>
#include <elm_button.eo.hh>
#include <elm_slider.eo.hh>

#include <Eina.hh>


// static void _fit(::elm_button obj, Eo_Event_Description const* desc, void *info);
// static void _unfit(::elm_button obj, Eo_Event_Description const* desc, void *info);
// static void _zoom(::elm_slider obj, Eo_Event_Description const* desc, void *info);
// static void _bring_in(::elm_photocam obj, Eo_Event_Description const* desc, void *info);

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   elm_app_compile_data_dir_set("/home/luciana/Enlightenment/local/share/elementary/");
   elm_app_info_set(reinterpret_cast<void*>(elm_main), "elementary", "images/insanely_huge_test_image.jpg");

   ::elm_win win(elm_win_util_standard_add("photocam", "Photocam"));
   win.autodel_set(true);

   ::elm_photocam photocam(efl::eo::parent = win);
   std::stringstream ss;
   ss << elm_app_data_dir_get() << "/images/insanely_huge_test_image.jpg";
   photocam.file_set(ss.str());
//photocam.bounce_set(false, true);
//photocam.callback_loaded_detail_add(&_bring_in);
   photocam.evas::object::size_set(500, 400);
   photocam.visibility_set(true);

   ::elm_button obj(efl::eo::parent = win);
   elm_object_text_set(obj._eo_ptr(), "Fit"); // XXX
   obj.visibility_set(true);
   obj.evas::object::size_set(50, 30);
   obj.position_set(10, 410);
//obj.callback_clicked_add(&_fit);
   
   ::elm_button obj2(efl::eo::parent = win);
   elm_object_text_set(obj2._eo_ptr(), "Unfit"); // XXX
   obj2.visibility_set(true);
   obj2.evas::object::size_set(70, 30);
   obj2.position_set(70, 410);
//obj2.callback_clicked_add(&_unfit);
   
   ::elm_slider slider(efl::eo::parent = win);
   elm_object_text_set(slider._eo_ptr(), "Zoom"); // XXX
   slider.visibility_set(true);
   slider.evas::object::size_set(300, 30);
   slider.position_set(150, 410);
//slider.callback_changed_add(&_zoom);

   win.evas::object::size_set(500, 440);
   win.visibility_set(true);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()

// static void
// _bring_in(::elm_photocam obj, Eo_Event_Description const* desc, void *info)
// {
//    int w, h;
//    obj.image_size_get(&w, &h);
// obj.image_region_bring_in(w/2, h/2, 500, 400);
// }

// static void
// _fit(::elm_button obj, Eo_Event_Description const* desc, void *info)
// {
//    int x, y, w, h;
// //elm_photocam_image_region_get(data, &x, &y, &w, &h);
//    data.image_region_get(&x, &y, &w, &h);
// std::cout << "region: {" << x << ", " << y << ", " << w << ", " << h << "}" << std::endl;
// //elm_photocam_zoom_mode_set(data, ELM_PHOTOCAM_ZOOM_MODE_AUTO_FIT);
//    data.zoom_mode_set(ELM_PHOTOCAM_ZOOM_MODE_AUTO_FIT);
// }

// static void
// _unfit(::elm_button obj, Eo_Event_Description const* desc, void *info)
// {
// //elm_photocam_zoom_mode_set(data, ELM_PHOTOCAM_ZOOM_MODE_MANUAL);
//    data.zoom_mode_set(ELM_PHOTOCAM_ZOOM_MODE_MANUAL);
// }

// static void
// _zoom(::elm_slider obj, Eo_Event_Description const* desc, void *info)
// {
//    double z = obj.value_get() * 8;
//    //elm_photocam_zoom_set(data, z);
//    data.zoom_set(z);
// }
