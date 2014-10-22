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
  Elm_Transit *trans, *trans2, *trans3, *trans4;

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("transit9", "Transit 9"));
  win.autodel_set(EINA_TRUE);

  ::elm_button bt(efl::eo::parent = win);
  elm_object_text_set(bt._eo_ptr(), "Chain 1"); // XXX
  bt.evas::object::size_set(100, 100);
  bt.position_set(0,0);
  bt.visibility_set(EINA_TRUE);

  ::elm_button bt2(efl::eo::parent = win);
  elm_object_text_set(bt2._eo_ptr(), "Chain 2"); // XXX
  bt2.evas::object::size_set(100, 100);
  bt2.position_set(300,0);
  bt2.visibility_set(EINA_TRUE);

  ::elm_button bt3(efl::eo::parent = win);
  elm_object_text_set(bt3._eo_ptr(), "Chain 3"); // XXX
  bt3.evas::object::size_set(100, 100);
  bt3.position_set(300, 300);
  bt3.visibility_set(EINA_TRUE);

  ::elm_button bt4(efl::eo::parent = win);
  elm_object_text_set(bt4._eo_ptr(), "Chain 4"); // XXX
  bt4.evas::object::size_set(100, 100);
  bt4.position_set(0, 300);
  bt4.visibility_set(EINA_TRUE);

  trans = ::elm_transit_add();
  ::elm_transit_tween_mode_set(trans, ELM_TRANSIT_TWEEN_MODE_ACCELERATE);
  elm_transit_effect_translation_add(trans, 0, 0, 300, 0);
  ::elm_transit_object_add(trans, bt._eo_ptr());
  ::elm_transit_duration_set(trans, 1);
  ::elm_transit_objects_final_state_keep_set(trans, EINA_TRUE);
  ::elm_transit_go(trans);

  trans2 = ::elm_transit_add();
  ::elm_transit_tween_mode_set(trans2, ELM_TRANSIT_TWEEN_MODE_ACCELERATE);
  ::elm_transit_effect_translation_add(trans2, 0, 0, 0, 300);
  ::elm_transit_object_add(trans2, bt2._eo_ptr());
  ::elm_transit_duration_set(trans2, 1);
  ::elm_transit_objects_final_state_keep_set(trans2, EINA_TRUE);
  ::elm_transit_chain_transit_add(trans, trans2);

  trans3 = ::elm_transit_add();
  ::elm_transit_tween_mode_set(trans3, ELM_TRANSIT_TWEEN_MODE_ACCELERATE);
  ::elm_transit_effect_translation_add(trans3, 0, 0, -300, 0);
  ::elm_transit_object_add(trans3, bt3._eo_ptr());
  ::elm_transit_duration_set(trans3, 1);
  ::elm_transit_objects_final_state_keep_set(trans3, EINA_TRUE);
  ::elm_transit_chain_transit_add(trans2, trans3);

  trans4 = ::elm_transit_add();
  ::elm_transit_tween_mode_set(trans4, ELM_TRANSIT_TWEEN_MODE_ACCELERATE);
  ::elm_transit_effect_translation_add(trans4, 0, 0, 0, -300);
  ::elm_transit_object_add(trans4, bt4._eo_ptr());
  ::elm_transit_duration_set(trans4, 1);
  ::elm_transit_objects_final_state_keep_set(trans4, EINA_TRUE);
  ::elm_transit_chain_transit_add(trans3, trans4);

  win.evas::object::size_set(400, 400);
  win.visibility_set(EINA_TRUE);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
