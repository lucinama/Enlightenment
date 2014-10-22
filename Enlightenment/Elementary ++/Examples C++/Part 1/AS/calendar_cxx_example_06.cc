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
#include <elm_button.eo.hh>
#include <elm_calendar.eo.hh>

#include <Eina.hh>

#define SECS_DAY 86400

static void
_btn_clear_cb(::elm_calendar obj, Eo_Event_Description const& desc, void* info)
{
  obj.marks_clear();
  obj.marks_draw();
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  struct tm selected_time;
  time_t current_time;
  struct tm sunday = { 0, 0, 12, 7, 0, 0, 0, 0, -1, 0, };
  struct tm christmas;
  christmas.tm_mday = 25;
  christmas.tm_mon = 11;
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   
  ::elm_win win(elm_win_util_standard_add("calendar", "Calendar Marks Example"));
  win.autodel_set(true);
  
  ::elm_box bx(efl::eo::parent = win);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);
    
  ::elm_calendar cal(efl::eo::parent = win);
  cal.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  cal.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  cal.visibility_set(true);
  bx.pack_end(cal);

  current_time = time(NULL);
  localtime_r(&current_time, &selected_time);

  Elm_Calendar_Mark* mark;
  mark = cal.mark_add("checked", &selected_time, ELM_CALENDAR_UNIQUE);

  current_time = time(NULL) + 1 * SECS_DAY;
  localtime_r(&current_time, &selected_time);
  cal.mark_add("checked", &selected_time, ELM_CALENDAR_UNIQUE);
 
  cal.mark_add("holiday", &christmas, ELM_CALENDAR_ANNUALLY);
 
  cal.mark_add("holiday", &sunday, ELM_CALENDAR_WEEKLY);
 
  mark.mark_clear();

  cal.marks_draw();

  ::elm_button bt(efl::eo::parent = win);
  bt.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt.text_set("elm.text", "Clear marks");
  bt.callback_clicked_add(&_btn_clear_cb);
  bx.pack_end(bt);
  bt.visibility_set(true);

  win.visibility_set(true);

  elm_run();
  elm_shutdown();
  
  return 0;
}
ELM_MAIN()
