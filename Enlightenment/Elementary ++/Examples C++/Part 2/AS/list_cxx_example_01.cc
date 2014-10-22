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

#include <elm_win.eo.hh>
#include <elm_list.eo.hh>
#include <elm_box.eo.hh>
#include <elm_scroller.eo.hh>

#include <Eina.hh>

#include <array>
#include <string>

EAPI_MAIN int
elm_main (int argc, char *argv[])
{

  std::array<std::string, 7> labels =
    {
      "Sunday",
      "Monday",
      "Tuesday",
      "Wednesday",
      "Thursday",
      "Friday",
      "Saturday"
    };
     
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("list", "List Example"));
  win.autodel_set(true);
      
  ::elm_box bx(efl::eo::parent = win);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);
 	    	
  ::elm_list li(efl::eo::parent = win);
  li.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  li.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx.pack_end(li);

  for (std::string s : labels)
    li.item_append(s, evas::object(), evas::object(), NULL, NULL);  // XXX

  li.visibility_set(true);
  li.go();
  
  win.evas::object::size_set(320, 240);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
