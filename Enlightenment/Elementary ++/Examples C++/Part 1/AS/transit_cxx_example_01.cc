#ifdef HAVE_CONFIG_H
# include <elementary_config.h>
#endif

extern "C"
{
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
#include "elm_interface_atspi_text.h"
#include "elm_interface_scrollable.h"
}

#include <Elementary.hh>
#include <Eina.hh>

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  Elm_Transit *trans;
   
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("transit-basic", "Transit - Basic"));
  win.autodel_set(EINA_TRUE);

  ::elm_button bt(efl::eo::parent = win);
  elm_object_text_set(bt._eo_ptr(), "Resizing Effect"); // XXX
  bt.visibility_set(EINA_TRUE);
  bt.position_set(50, 100);
  bt.evas::object::size_set(100, 50);

  trans = ::elm_transit_add();
  ::elm_transit_object_add(trans, bt._eo_ptr());

  ::elm_transit_effect_resizing_add(trans, 100, 50, 300, 150);

  ::elm_transit_duration_set(trans, 5.0);
  ::elm_transit_go(trans);

  win.evas::object::size_set(400, 400);
  win.visibility_set(EINA_TRUE);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
