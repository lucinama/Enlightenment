
#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define PACKAGE_EXAMPLES_DIR "/home/luciana/Enlightenment/scr/efl/src/examples/evas"
#endif

#include <Ecore.h>
#include <Ecore_Evas.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Eina.hh>
#include <Evas.hh>
#include <Eo.hh>
#include <Efl.hh>

#define WIDTH  320
#define HEIGHT 320

struct test_data
{
   Ecore_Evas  *ee;
   Evas        *canvas;
   Evas_Object *bg;
   Evas_Object *rects[3];
   int          layers[3];
   int          cur_rect, cur_layer;
};

static struct test_data d = {0};

static const char *commands = \
  "commands are:\n"
  "\tc - change the target rectangle to operate on\n"
  "\ta - stack target rectangle one level above\n"
  "\tb - stack target rectangle one level below\n"
  "\tt - stack target rectangle up to the top of its layer\n"
  "\tm - stack target rectangle down to the bottom of its layer\n"
  "\tp - toggle target rectangle's 'pass events' property\n"
  "\tr - toggle target rectangle's 'repeat events' property\n"
  "\ts - print current stacking information\n"
  "\tl - change background rectangle's layer\n"
  "\th - print help\n";

static const char *
_name_get(Evas_Object *o)
{
   const char *s = evas_object_name_get(o);
   if (!s) s = "(null)";
   return s;
}

static void
_on_mouse_down(void *data EINA_UNUSED, Evas *evas EINA_UNUSED, Evas_Object *o, void *einfo EINA_UNUSED)
{
   fprintf(stdout, "Mouse down on rectangle %s!\n", _name_get(o));
}

static void
_canvas_resize_cb(Ecore_Evas *ee)
{
   int w, h;

   ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
bg.evas::object::size_set( w, h);
}

static void
_on_keydown(void *data EINA_UNUSED, Evas *evas EINA_UNUSED, Evas_Object *o EINA_UNUSED, void *einfo)
{
   Evas_Event_Key_Down *ev = einfo;
   const char *name = _name_get(d.rects[d.cur_rect]);

if (strcmp(ev->key, "h") == 0)
     {
        fprintf(stdout, commands);
        return;
     }

   if (strcmp(ev->key, "s") == 0)
     {
        Evas_Object *rect;

        fprintf(stdout, "Order of stacking, from top to bottom, is: ");

        rect = evas_object_top_get(evas);
        fprintf(stdout, "%s", _name_get(rect));

        rect = evas_object_below_get(rect);
        while (rect)
          {
             fprintf(stdout, ", %s", _name_get(rect));
             rect = evas_object_below_get(rect);
          }

        fprintf(stdout, ".\n");

        fprintf(stdout, "Current target rectangle is %s\n",
                _name_get(d.rects[d.cur_rect]));

        fprintf(stdout, "Background rectangle's layer is %d\n",
                evas_object_layer_get(d.bg));

        return;
     }

   if (strcmp(ev->key, "l") == 0)
     {
        d.cur_layer = (d.cur_layer + 1) % 3;
        evas_object_layer_set(d.bg, d.layers[d.cur_layer]);

        fprintf(stdout, "Changing background rectangle's layer to %d\n",
                d.layers[d.cur_layer]);
        return;
     }

   if (strcmp(ev->key, "c") == 0)
     {
        d.cur_rect = (d.cur_rect + 1) % 3;

        fprintf(stdout, "Changing target rectangle to the %s one\n",
                _name_get(d.rects[d.cur_rect]));
        return;
     }

   if (strcmp(ev->key, "t") == 0)
     {
        Evas_Object *neighbour;

        evas_object_raise(d.rects[d.cur_rect]);

        fprintf(stdout, "%s rectangle was re-stacked to the top if its layer\n",
                name);

        neighbour = evas_object_below_get(d.rects[d.cur_rect]);
        fprintf(stdout, "Below of %s rect is %s\n", name,
                neighbour ? _name_get(neighbour) : "no object");
        return;
     }

   if (strcmp(ev->key, "m") == 0)
     {
        Evas_Object *neighbour;

        evas_object_lower(d.rects[d.cur_rect]);

        fprintf(stdout,
                "%s rectangle was re-stacked to the bottom if its layer\n",
                name);

        neighbour = evas_object_below_get(d.rects[d.cur_rect]);
        fprintf(stdout, "Below of %s rect is %s\n", name,
                neighbour ? _name_get(neighbour) : "no object");
        return;
     }

   if (strcmp(ev->key, "p") == 0)
     {
        Eina_Bool pass = evas_object_pass_events_get(d.rects[d.cur_rect]);

        evas_object_pass_events_set(d.rects[d.cur_rect], !pass);

        fprintf(stdout, "%s rectangle is now set to%s pass (ignore) events\n",
                name, pass ? " NOT" : "");

        return;
     }

   if (strcmp(ev->key, "r") == 0)
     {
        Eina_Bool repeat = evas_object_repeat_events_get(d.rects[d.cur_rect]);

        evas_object_repeat_events_set(d.rects[d.cur_rect], !repeat);

        fprintf(stdout, "%s rectangle is now set to%s repeat events\n",
                name, repeat ? " NOT" : "");

        return;
     }

   if (strcmp(ev->key, "a") == 0)
     {
        Evas_Object *neighbour = evas_object_above_get(d.rects[d.cur_rect]);

        if (!neighbour || (evas_object_layer_get(d.rects[d.cur_rect]) !=
                           evas_object_layer_get(neighbour)))
          return;

        evas_object_stack_above(d.rects[d.cur_rect], neighbour);

        fprintf(stdout, "%s rectangle was re-stacked one level above\n", name);

        neighbour = evas_object_above_get(d.rects[d.cur_rect]);
        fprintf(stdout, "Above of %s rect is %s\n", name,
                neighbour ? _name_get(neighbour) : "no object");

        neighbour = evas_object_below_get(d.rects[d.cur_rect]);
        fprintf(stdout, "Below of %s rect is %s\n", name,
                neighbour ? _name_get(neighbour) : "no object");
        return;
     }

   if (strcmp(ev->key, "b") == 0)
     {
        Evas_Object *neighbour = evas_object_below_get(d.rects[d.cur_rect]);

        if (!neighbour || (evas_object_layer_get(d.rects[d.cur_rect]) !=
                           evas_object_layer_get(neighbour)))
          return;

        evas_object_stack_below(d.rects[d.cur_rect], neighbour);

        fprintf(stdout, "%s rectangle was re-stacked one level below\n", name);

        neighbour = evas_object_above_get(d.rects[d.cur_rect]);
        fprintf(stdout, "Above of %s rect is %s\n", name,
                neighbour ? _name_get(neighbour) : "no object");

        neighbour = evas_object_below_get(d.rects[d.cur_rect]);

        fprintf(stdout, "Below of %s rect is %s\n", name,
                neighbour ? _name_get(neighbour) : "no object");
        return;
     }
}

static void
_on_destroy(Ecore_Evas *ee EINA_UNUSED)
{
   ecore_main_loop_quit();
}

int
main(void)
{
   if (!ecore_evas_init())
     return EXIT_FAILURE;

   d.ee = ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);
   if (!d.ee)
     goto error;

   ecore_evas_callback_destroy_set(d.ee, _on_destroy);
   ecore_evas_callback_resize_set(d.ee, _canvas_resize_cb);
   ecore_evas_show(d.ee);

   evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));

   evas::rectangle bg(efl::eo::parent = canvas);
   bg.name_set("background");
   bg.color_set(255, 255, 255, 255);
   bg.position_set( 0, 0);
   bg.evas::object::size_set(d.bg, WIDTH, HEIGHT);

   d.layers[0] = evas_object_layer_get(d.bg);
   d.layers[1] = d.layers[0] - 1;
   d.layers[2] = d.layers[0] + 1;

   d.cur_layer = 1;
   bg.layer_set(d.layers[d.cur_layer]);

   bg.visibility_set(EINA_TRUE);

   bg.focus_set(EINA_TRUE);
   evas_object_event_callback_add(bg, EVAS_CALLBACK_KEY_DOWN, _on_keydown, NULL);

   d.rects[2] = evas_object_rectangle_add(d.canvas);
   evas_object_name_set(d.rects[2], "blue");
   evas_object_color_set(d.rects[2], 0, 0, 255, 255);

   evas_object_resize(d.rects[2], WIDTH / 2.2, WIDTH / 2.2);
   evas_object_move(d.rects[2], WIDTH / 6, WIDTH / 4.5);
   evas_object_show(d.rects[2]);
   evas_object_event_callback_add(d.rects[2], EVAS_CALLBACK_MOUSE_DOWN, _on_mouse_down, NULL);

   d.rects[1] = evas_object_rectangle_add(d.canvas);
   evas_object_name_set(d.rects[1], "green");
   evas_object_color_set(d.rects[1], 0, 255, 0, 255);

   evas_object_resize(d.rects[1], WIDTH / 2.2, WIDTH / 2.2);
   evas_object_move(d.rects[1], WIDTH / 2.5, WIDTH / 7);
   evas_object_show(d.rects[1]);
   evas_object_event_callback_add(
     d.rects[1], EVAS_CALLBACK_MOUSE_DOWN, _on_mouse_down, NULL);

   d.rects[0] = evas_object_rectangle_add(d.canvas);
   evas_object_name_set(d.rects[0], "red");
   evas_object_color_set(d.rects[0], 255, 0, 0, 255);

   evas_object_resize(d.rects[0], WIDTH / 2.2, WIDTH / 2.2);
   evas_object_move(d.rects[0], WIDTH / 3, WIDTH / 2.5);
   evas_object_show(d.rects[0]);
   evas_object_event_callback_add(rects[0], EVAS_CALLBACK_MOUSE_DOWN, _on_mouse_down, NULL);

   fprintf(stdout, commands);
   ecore_main_loop_begin();

   ::ecore_evas_shutdown();
   return 0;

error:
   fprintf(stderr, "you got to have at least one evas engine built and linked"
                   " up to ecore-evas for this example to run properly.\n");
   return -1;
}
