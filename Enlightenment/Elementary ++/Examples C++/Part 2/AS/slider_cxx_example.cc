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
#include <elm_slider.eo.hh>
#include <elm_box.eo.hh>
#include <elm_icon.eo.hh>
#include <elm_image.eo.hh>

#include <Eina.hh>

#include <iostream>

static void
_changed_cb(::elm_slider obj, Eo_Event_Description const& desc, void* info)
{
  double val = obj.value_get();
  std::cout << "Changed to " << val << std::endl;
}

static void
_delay_changed_cb(::elm_slider obj, Eo_Event_Description const& desc, void* info)
{
  double val = obj.value_get();
  std::cout << "Delay changed to " << val << std::endl;
}

static char*
_indicator_format(double val)
{
  char *indicator = new char[32];
  snprintf(indicator, 32, "%1.2f u", val);
  return indicator;
}

static void
_indicator_free(char *str)
{
  delete str;
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("slider", "Slider Example"));
  win.autodel_set(true);
  	
  ::elm_box bx(efl::eo::parent = win);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);

  ::elm_slider sl(efl::eo::parent = win);
  sl.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  sl.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx.pack_end(sl);
  sl.visibility_set(true);

  ::elm_slider sl2(efl::eo::parent = win);
  elm_object_text_set(sl._eo_ptr(), "Counter"); // XXX
	
  ::elm_icon ic(efl::eo::parent = win);
  ic.standard_set("home");
  ic.resizable_set(false, false);
  sl2.content_set("icon", ic);

  ::elm_icon ic2(efl::eo::parent = win);
  ic2.standard_set("folder");
  ic2.resizable_set(false, false);
  sl2.content_set("end", ic2);
   
  sl2.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  sl2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx.pack_end(sl2);
  sl2.visibility_set(true);

  ::elm_slider sl3(efl::eo::parent = win);
  sl3.value_set(1);
  sl3.span_size_set(200);
  sl3.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  sl3.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx.pack_end(sl3);
  sl3.visibility_set(true);

  ::elm_slider sl4(efl::eo::parent = win);
  sl4.unit_format_set("%1.0f units");
  sl4.min_max_set(0, 100);
  sl4.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  sl4.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx.pack_end(sl4);
  sl4.visibility_set(true);

  ::elm_slider sl5(efl::eo::parent = win);
  sl5.indicator_format_set("%1.2f");
  sl5.inverted_set(true);
  sl5.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  sl5.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx.pack_end(sl5);
  sl5.visibility_set(true);
   
  ::elm_slider sl6(efl::eo::parent = win);
  sl6.horizontal_set(false);
  sl6.indicator_format_function_set(&_indicator_format,&_indicator_free);
  sl6.size_hint_align_set(0.5, EVAS_HINT_FILL);
  sl6.size_hint_weight_set(0, EVAS_HINT_EXPAND);
  bx.pack_end(sl6);
  sl6.visibility_set(true);

  ::elm_slider sl7(efl::eo::parent = win);
  sl7.unit_format_set("%1.3f units");
  sl7.indicator_format_function_set(&_indicator_format,&_indicator_free);
  sl7.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  sl7.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx.pack_end(sl7);
  sl7.visibility_set(true);
  sl7.callback_changed_add(&_changed_cb);
  sl7.callback_delay_changed_add(&_delay_changed_cb);
   	
  win.visibility_set(true);
  	
  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
