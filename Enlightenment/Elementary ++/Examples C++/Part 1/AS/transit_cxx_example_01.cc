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
#include <elm_button.eo.hh>
// #include <elm_transit.eo.hh>


EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  // Evas_Object *bt;
  Elm_Transit *trans;
   
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("transit-basic", "Transit - Basic"));
  win.autodel_set(true);

  ::elm_button bt(efl::eo::parent = win);
  bt.text_set("text", "Resizing Effect");
  bt.visibility_set(true);
  bt.position_set(50, 100);
  bt.size_set(100, 50);

  trans = elm_transit_add();
  elm_transit_object_add(trans, bt);

  elm_transit_effect_resizing_add(trans, 100, 50, 300, 150);

  elm_transit_duration_set(trans, 5.0);
  elm_transit_go(trans);

  // ::elm_transit trans(efl::eo::parent = win);
  // trans.object_add(bt);

  // trans.effect_resizing_add(100, 50, 300, 150);

  // trans.duration_set(5.0);
  // trans.go();

  win.size_set(400, 400);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
  
}
ELM_MAIN()
