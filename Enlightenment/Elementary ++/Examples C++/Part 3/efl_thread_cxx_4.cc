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

#include <Eina.hh>
#include <Evas.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

namespace efl { namespace evas {
    using ::evas::canvas;
    using ::evas::rectangle;
  } }

static Evas_Object *win = NULL;
static Evas_Object *rect = NULL;

struct info
{
   double x, y;
};

static void my_thread_mainloop_code(Eo* obj);

static pthread_t thread_id;
static pthread_mutex_t th_lock;
static int th_exit = 0;

// static void *
// my_thread_run(void *arg)
// {
//    double t = 0.0;

//      for (;;)
//      {
//         struct info *inf = malloc(sizeof(struct info));
//         int do_exit;

//         if (inf)
//           {
//              inf->x = 200 + (200 * sin(t));
//              inf->y = 200 + (200 * cos(t));
//              ecore_main_loop_thread_safe_call_async
//                 (my_thread_mainloop_code, inf);
//           }
//         usleep(1000);
//         t += 0.02;

//         pthread_mutex_lock(&th_lock);
//         do_exit = th_exit;
//         pthread_mutex_unlock(&th_lock);
//         if (do_exit) break;
//      }
//    return NULL;
// }

// static void
// my_thread_new(void)
// {
//    pthread_attr_t attr;

//    pthread_mutex_init(&th_lock, NULL);
//    if (pthread_attr_init(&attr) != 0)
//      perror("pthread_attr_init");
//    if (pthread_create(&thread_id, &attr, my_thread_run, NULL) != 0)
//      perror("pthread_create");
// }

// static void
// my_thread_mainloop_code(efl::evas::rectangle rect)
// {
//    struct info *inf = data;
//    rect.position_set(inf->x - 50, inf->y - 50);
//    inf.free();
// }

static void
down(Eo* obj, Eo_Event_Description const& desc, void* info)
{
   pthread_mutex_lock(&th_lock);
   th_exit = 1;
   pthread_mutex_unlock(&th_lock);
}

// on window delete - cancel thread then delete window and exit mainloop
static void
del(Eo* obj, Eo_Event_Description const& desc, void* info)
{
   pthread_mutex_lock(&th_lock);
   th_exit = 1;
   pthread_mutex_unlock(&th_lock);
   obj.del();
   elm_exit();
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

 	::elm_win win(elm_win_util_standard_add("efl-thread-4", "EFL Thread 4"));
   	win.callback_delete_request_add(del);

 	efl::evas::rectangle o(efl::eo::parent = win);
   	o.color_set(50, 80, 180, 255);
   	o.evas::object::size_set(100, 100);
	o.visibility_set(true);
	o.event_callback_add(EVAS_CALLBACK_MOUSE_DOWN, down);
   	rect = o;

   	my_thread_new();

   	win.evas::object::size_set(400, 400);
   	win.visibility_set(true);

   	elm_run();
   	pthread_mutex_lock(&th_lock);
   	th_exit = 1;
   	pthread_mutex_unlock(&th_lock);
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()
