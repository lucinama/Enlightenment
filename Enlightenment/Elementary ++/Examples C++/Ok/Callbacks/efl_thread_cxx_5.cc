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
#include <pthread.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"

#include <elm_win.eo.hh>
#include <elm_box.eo.hh>
#include <elm_button.eo.hh>
#include <elm_actionslider.eo.hh>

#include <Eina.hh>

#include <Evas.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

namespace efl { namespace evas {
    using ::evas::canvas;
    using ::evas::rectangle;
  } }
  
static Ecore_Thread *thr = NULL;

struct info
{
   double x, y;
};

static void
th_do(void *data, Ecore_Thread *th)
{
   double t = 0.0;

   // inside our "do" function for the ecore thread, lets do the real work
   for (;;)
     {
        struct info *inf = malloc(sizeof(struct info));

        if (inf)
          {
             inf->x = 200 + (200 * sin(t));
             inf->y = 200 + (200 * cos(t));
             // now we have recorded the timepoint we pass it as feedback
             // back to the mainloop. it will free it when done
             ecore_thread_feedback(th, inf);
          }
        // and sleep and loop
        usleep(1000);
        t += 0.02;
        // in case someone has asked us to cancel - then cancel this loop
        // co-operatively (cancelling is co-operative)
        if (ecore_thread_check(th)) break;
     }
}
//
// END - code running in my custom thread instance

static void
th_feedback(void *data, Ecore_Thread *th, void *msg)
{
   struct info *inf = msg;
   evas_object_move(rect, inf->x - 50, inf->y - 50);
   free(inf);
}

// BONUS (optional): called after th_do returns and has NOT been cancelled
static void th_end(void *data, Ecore_Thread *th) { printf("thread ended\n"); }
// BONUS (optional): called in mainloop AFTER thread has finished cancelling
static void th_cancel(void *data, Ecore_Thread *th) { printf("thread cancelled\n"); }

// just test cancelling the thread worker
static void
down(::elm_actionslider obj, Eo_Event_Description const& desc, void* info)
{
   if (thr) ecore_thread_cancel(thr);
   thr = NULL;
}

// on window delete - cancel thread then delete window and exit mainloop
static void
del(::elm_actionslider obj, Eo_Event_Description const& desc, void* info)
{
   if (thr) ecore_thread_cancel(thr);
   thr = NULL;
obj.del();
   elm_exit();
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	::elm_win win(elm_win_util_standard_add("efl-thread-5", "EFL Thread 5"));
  	win.callback_delete_request_add(del);

   	efl::evas::rectangle o(efl::eo::parent = win);
  	o.color_set( 50, 80, 180, 255);
  	o.size_hint_min_set( 100, 100);
  	o.visibility_set(true);
   	o.event_callback_add(EVAS_CALLBACK_MOUSE_DOWN, down, NULL);
	efl::evas::rectangle rect(efl::eo::parent = win);
   	rect = o;
  
   	thr = ecore_thread_feedback_run(th_do, th_feedback, th_end, th_cancel,
                                   NULL, true);

   	win.evas::object::size(400, 400);
   	win.visibility_set(true);

   	elm_run();
   	if (thr) ecore_thread_cancel(thr);
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()

