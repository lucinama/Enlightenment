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

#include <sstream>

#include <elm_win.eo.hh>
#include <elm_radio.eo.hh>
#include "elm_check.eo.hh"
#include <elm_box.eo.hh>
#include <elm_bg.eo.hh>
#include <elm_spinner.eo.hh>

#include <Eina.hh>

void
_cb_radio_changed(void* data, ::elm_bg o_bg, Eo_Event_Description const& desc EINA_UNUSED, void* info EINA_UNUSED)
{  
  ::elm_win win(elm_win_util_standard_add("bg-options", "Bg Options"));
  win.autodel_set(true);
  ::elm_radio rd(efl::eo::parent = win);
  o_bg.option_set(rd.value_get());
}

void
_cb_overlay_changed(::elm_bg o_bg, Eo_Event_Description const& desc EINA_UNUSED, void* info EINA_UNUSED)
{
  

  if (obj.state_get())
     {
        Evas_Object *parent, *over;
        char buff[PATH_MAX];

	//snprintf(buff, sizeof(buff), "%s/objects/test.edj", elm_app_data_dir_get());
	std::stringstream ss1;
	ss1 << elm_app_data_dir_get() << "/objects/teste.edj";
        static_cast<evas::object>(parent) = o_bg.parent_widget_get();
        over = edje_object_add(evas_object_evas_get(parent));
        edje_object_file_set(over, buff, "bg_overlay");
        o_bg.content_set("overlay", over);
     }
   else
     //  o_bg.content_set("overlay", NULL);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  char buf[PATH_MAX];
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  elm_app_compile_data_dir_set("/home/luciana/Enlightenment/local/share/elementary/");
  elm_app_info_set(reinterpret_cast<void*>(elm_main), "elementary", "objects/test.edj");
 
  ::elm_win win(elm_win_util_standard_add("bg-options", "Bg Options"));
  win.autodel_set(true);

  ::elm_box box(efl::eo::parent = win);
  box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(box);
  box.visibility_set(true);

 ::elm_bg o_bg(efl::eo::parent = win);
 o_bg.option_set(ELM_BG_OPTION_CENTER);
 std::stringstream ss;
 ss << elm_app_data_dir_get() << "/images/plant_01.jpg";
 //snprintf(buf, sizeof(buf), "%s/images/plant_01.jpg", elm_app_data_dir_get());
 // elm_bg_file_set(o_bg, buf, NULL);
 o_bg.file_set(ss.str(), "image");
 o_bg.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
 o_bg.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
 box.pack_end(o_bg);
 o_bg.visibility_set(true);

 ::elm_box hbox(efl::eo::parent = win);
 hbox.horizontal_set(true);
 hbox.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
 hbox.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);

 ::elm_radio rd(efl::eo::parent = win);
 rd.state_value_set(ELM_BG_OPTION_CENTER);
 rd.text_set("elm.text" , "Center");
 rd.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_FILL);
 // evas_object_smart_callback_add(rd, "changed", _cb_radio_changed, o_bg);
 efl::eo::signal_connection conn =
   rd.callback_changed_add
   ([&win] (::elm_radio& obj, Eo_Event_Description const& desc EINA_UNUSED, void* info EINA_UNUSED)
    {
      ::elm_bg o_bg2(efl::eo::parent = win);
      ::elm_radio rd(efl::eo::parent = win);
      o_bg2.option_set(static_cast<Elm_Bg_Option>(obj.value_get()));
    });
 hbox.pack_end(rd);
 rd.visibility_set(true);

 ::elm_radio rdg(efl::eo::parent = win);
 rdg = rd;

 rd.state_value_set(ELM_BG_OPTION_SCALE);
 rd.group_add(rdg);
 rd.text_set("elm.text" , "Scale");
 rd.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_FILL);
 // evas_object_smart_callback_add(rd, "changed", _cb_radio_changed, o_bg);
 conn;
 hbox.pack_end(rd);
 rd.visibility_set(true);

 rd.state_value_set(ELM_BG_OPTION_STRETCH);
 rd.group_add(rdg);
 rd.text_set("elm.text" , "Stretch");
 rd.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_FILL);
 // evas_object_smart_callback_add(rd, "changed", _cb_radio_changed, o_bg);
 conn;
 hbox.pack_end(rd);
 rd.visibility_set(true);

 rd.state_value_set(ELM_BG_OPTION_TILE);
 rd.group_add(rdg);
 rd.text_set("elm.text" , "Title");
 rd.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_FILL);
 // evas_object_smart_callback_add(rd, "changed", _cb_radio_changed, o_bg);
 conn;
 hbox.pack_end(rd);
 rd.visibility_set(true);

 rdg.state_value_set(ELM_BG_OPTION_SCALE);

 ::elm_check rd1(efl::eo::parent = win);
 rd1.text_set("elm.text" , "Show Overlay");
 rd1.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_FILL);
 // evas_object_smart_callback_add(rd, "changed", _cb_overlay_changed, o_bg);
 //rd.callback_changed_add(&_cb_overlay_changed);
 hbox.pack_end(rd1);
 rd1.visibility_set(true);

 ::elm_spinner rd2(efl::eo::parent = win);
 // elm_object_style_set(rd, "vertical");
 // rd2.style_set("vertical");
 rd2.min_max_set(1, 4);
 rd2.label_format_set("%.0f");
 rd2.editable_set(false);
 rd2.special_value_add(1, "White");
 rd2.special_value_add(2, "Red");
 rd2.special_value_add(3, "Blue");
 rd2.special_value_add(4, "Green");
 rd2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
 rd2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
 // evas_object_smart_callback_add(rd, "changed", _cb_color_changed, o_bg);

 efl::eo::signal_connection conn2 =
   rd2.callback_changed_add
   ([&win] (::elm_spinner& obj_, Eo_Event_Description const& desc EINA_UNUSED, void* info EINA_UNUSED)
    {
      ::elm_spinner obj(efl::eo::parent = win);
      ::elm_bg o_bg3(efl::eo::parent = win);
      double val = 0.0;
      val = obj.value_get();
      if (val == 1.0)
	o_bg3.color_set(255, 255, 255, 255);
      else if (val == 2.0)
	o_bg3.color_set(255, 0, 0, 255);
      else if (val == 3.0)
	o_bg3.color_set(0, 0, 255, 255);
      else if (val == 4.0)
	o_bg3.color_set(0, 255, 0, 255);
    });
 hbox.pack_end(rd2);
 rd2.visibility_set(true);

 box.pack_end(hbox);
 hbox.visibility_set(true);

 win.evas::object::size_set(460, 320);
 win.visibility_set(true);

 elm_run();
 elm_shutdown();
  
 return 0;
  
}
ELM_MAIN();
