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
#include <elm_box.eo.hh>
#include <elm_dayselector.eo.hh>

#include <Eina.hh>
#include <iostream>

void
_changed_cb(::elm_dayselector obj, Eo_Event_Description const& desc, void* info)
{
   char buf[256];
   Elm_Dayselector_Day day;
   Eina_Bool selected;
   
   day = info;
   selected = obj.day_selected_get(day);
   switch(day)
     {
      case ELM_DAYSELECTOR_SUN: snprintf(buf, sizeof(buf), "%s", "Sun");   break;
      case ELM_DAYSELECTOR_MON: snprintf(buf, sizeof(buf), "%s", "Mon");   break;
      case ELM_DAYSELECTOR_TUE: snprintf(buf, sizeof(buf), "%s", "Tue");   break;
      case ELM_DAYSELECTOR_WED: snprintf(buf, sizeof(buf), "%s", "Wed");   break;
      case ELM_DAYSELECTOR_THU: snprintf(buf, sizeof(buf), "%s", "Thu");   break;
      case ELM_DAYSELECTOR_FRI: snprintf(buf, sizeof(buf), "%s", "Fri");   break;
      case ELM_DAYSELECTOR_SAT: snprintf(buf, sizeof(buf), "%s", "Sat");   break;
      default: snprintf(buf, sizeof(buf), "%s", "???"); break;
     }
   fprintf(stderr, "%s state is %d\n", buf, selected);
   //std::cerr << buf << " state is " << selected  << std::endl;
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("dayselector", "Dayselector Example"));
  win.autodel_set(true);

  ::elm_box bx(efl::eo::parent = win);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);

  ::elm_dayselector dayselector(efl::eo::parent = win);
  dayselector.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  dayselector.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  dayselector.callback_dayselector_changed_add(&_changed_cb);
  bx.pack_end(dayselector);
  dayselector.visibility_set(true);

  ::elm_dayselector dayselector2(efl::eo::parent = win);
  dayselector2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  dayselector2.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  dayselector2.callback_dayselector_changed_add(&_changed_cb);
  dayselector2.style_set("mon_first");
  bx.pack_end(dayselector2);
  dayselector2.visibility_set(true);

  win.size_set(350,120);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();
  
  return 0;
  
}
ELM_MAIN();
