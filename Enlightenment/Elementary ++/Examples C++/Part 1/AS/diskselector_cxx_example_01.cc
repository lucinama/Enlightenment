#include <iostream>

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
#include <elm_box.eo.hh>
#include <elm_diskselector.eo.hh>
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

  ::elm_win win(elm_win_util_standard_add("diskselector", "Diskselector Example"));
  win.autodel_set(true);

  ::elm_box bx(efl::eo::parent = win);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);

  ::elm_diskselector ds(efl::eo::parent = win);
  ds.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  ds.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx.pack_end(ds);
  for (std::string s : labels)
    ds.item_append(s, evas::object(), NULL, NULL); // XXX
  ds.visibility_set(true);

  ::elm_diskselector ds2(efl::eo::parent = win);
  ds2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  ds2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx.pack_end(ds2);
  for (std::string s : labels)
    ds2.item_append(s, evas::object(), NULL, NULL);  // XXX
  ds2.round_enabled_set(true);
  ds2.side_text_max_length_set(2);
  ds2.visibility_set(true);

  ::elm_diskselector ds3(efl::eo::parent = win);
  ds3.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  ds3.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx.pack_end(ds3);
  for (std::string s : labels)
    ds3.item_append(s, evas::object(), NULL, NULL); // XXX
  ds3.display_item_num_set(5);
  std::cout << "Number of Items in DiskSelector : " << ds3.display_item_num_get() << std::endl;
  ds3.visibility_set(true);

  ::elm_diskselector ds4(efl::eo::parent = win);
  ds4.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  ds4.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx.pack_end(ds4);
  for (std::string s : labels)
    ds4.item_append(s, evas::object(), NULL, NULL); // XXX
  ds4.bounce_allow_set(true, true);
  ds4.policy_set(ELM_SCROLLER_POLICY_AUTO, ELM_SCROLLER_POLICY_ON);
  ds4.visibility_set(true);

  win.size_set(320,480);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();
  
  return 0;
  
}
ELM_MAIN();
