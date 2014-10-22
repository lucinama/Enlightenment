#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <Evas.h>
#include <Ecore.h>
#include <Ecore_Evas.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Eina.hh>
#include <Evas.hh>
#include <Eo.hh>
#include <Efl.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

#define WIDTH  (640)
#define HEIGHT (480)

static const char *commands = \
  "commands are:\n"
  "\tn - turn on alpha"
  "\tm - turn off alpha"
  "\th - print help\n";

Ecore_Evas  *ee;
evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));

static void
_on_keydown(void *data EINA_UNUSED, Evas *evas EINA_UNUSED, Evas_Object *o EINA_UNUSED, Evas_Event_Key_Down *ev)
{
  //Evas_Event_Key_Down *ev = einfo;

  if (strcmp(ev->key, "h") == 0)
    {
      fprintf(stdout, "%s",  commands);
      return;
    }

  if (strcmp(ev->key, "n") == 0)
    {
      ::ecore_evas_alpha_set(ee, EINA_TRUE);

      fprintf(stdout, "turn on alpha\n");
      return;
    }

  if (strcmp(ev->key, "m") == 0)
    {
      ::ecore_evas_alpha_set(ee, EINA_FALSE);

      fprintf(stdout, "turn off alpha\n");
      return;
    }
}

static void
_on_delete(Ecore_Evas *ee EINA_UNUSED)
{
  ::ecore_main_loop_quit();
}

int
main(void)
{
  efl::eina::eina_init eina_init;
  efl::eo::eo_init init;
  if (!::ecore_evas_init()) return EXIT_FAILURE;
  if (!::evas_init()) return EXIT_FAILURE;

  ee = ::ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);
  if (!ee)
      fprintf(stderr, "You got to have at least one evas engine built and linked"
	  " up to ecore-evas for this example to run properly.\n");

  ::ecore_evas_callback_delete_request_set(ee, _on_delete);
  ecore_evas_show(ee);

  //evas::canvas evas(::eo_ref(::ecore_evas_get(ee)));
  evas::rectangle bg(efl::eo::parent = canvas);
  bg.color_set(0, 0, 0, 0);
  bg.visibility_set(true);
  canvas.render();
  bg.focus_set(EINA_TRUE);


  ::evas_object_event_callback_add(bg._eo_ptr(), EVAS_CALLBACK_KEY_DOWN, _on_keydown, NULL);
  ::ecore_main_loop_begin();
  ::ecore_evas_shutdown();

  return 0;
}
