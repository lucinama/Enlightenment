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
#include "elm_interface_atspi_accessible.eo.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_widget_action.eo.h"

#include <elm_win.eo.hh>
#include <elm_bg.eo.hh>

#include <Eina.hh>

#include <sstream>

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  elm_app_compile_data_dir_set("/home/luciana/Enlightenment/local/share/elementary/");
  elm_app_info_set(reinterpret_cast<void*>(elm_main), "elementary", "images/plant_01.jpg");

  ::elm_win win(elm_win_add(NULL, "bg-image", ELM_WIN_BASIC));
  win.title_set("Bg Image");
  win.autodel_set(true);

  ::elm_bg bg(efl::eo::parent = win);
  bg.load_size_set(20, 20);
  bg.option_set(ELM_BG_OPTION_CENTER);
  std::stringstream ss;
  ss << elm_app_data_dir_get() << "/images/plant_01.jpg";
  bg.file_set(ss.str(), "image");
  bg.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bg);
  bg.visibility_set(true);

  win.size_set(320, 320);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();
  
  return 0;
}
ELM_MAIN()
