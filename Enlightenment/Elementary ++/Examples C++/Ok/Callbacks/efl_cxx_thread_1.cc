#include <pthread.h>
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

#include <Eo.h>
#include <Evas.h>
#include <Elementary.h>
#include <elm_widget.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_accessible.eo.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_widget_action.eo.h"

#include <elm_win.eo.hh>
#include "elm_check.eo.hh"

#include <Eina.hh>
#include <Evas.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

namespace efl { namespace evas {
    using ::evas::canvas;
    using ::evas::rectangle;
   } }

::elm_win win(elm_win_util_standard_add("Win Plain" , "Win Plain"));
efl::evas::rectangle rect(efl::eo::parent = win);

static pthread_t thread_id;

static void *
my_thread_run(void *arg)
{
   double t = 0.0;

   for (;;)
     {
        ecore_thread_main_loop_begin();
          {
             Evas_Coord x, y;

             x = 200 + (200 * sin(t));
             y = 200 + (200 * cos(t));
             rect.position_set(x - 50, y - 50);
          }
        ecore_thread_main_loop_end();
        usleep(1000);
        t += 0.02;
     }
   return NULL;
}

static void
my_thread_new(void)
{
   pthread_attr_t attr;

   if (pthread_attr_init(&attr) != 0)
     perror("pthread_attr_init");
   if (pthread_create(&thread_id, &attr, my_thread_run, NULL) != 0)
     perror("pthread_create");
}

static void
del(::elm_win obj, Eo_Event_Description const& desc, void* info)
{
   exit(0);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  bool value;
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
 
  ::elm_win win(elm_win_util_standard_add("efl-thread-1", "EFL Thread 1"));
  win.callback_delete_request_add(&del);
   
  efl::evas::rectangle o(efl::eo::parent = win);
  o.color_set(50, 80, 180, 255);
  o.size_set(100, 100);
  o.visibility_set(true);
  rect = o;

  my_thread_new();
 
  win.size_set(400, 400);
  win.visibility_set(true);

  elm_run();
 
  return 0;
}
ELM_MAIN()
