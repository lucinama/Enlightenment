#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define PACKAGE_EXAMPLES_DIR "/home/luciana/Enlightenment/src/efl/src/examples/evas"
#endif

#include <Ecore.h>
#include <Ecore_Evas.h>
#include <Edje.h>
#include <stdio.h>
#include <errno.h>

#include <Eina.hh>
#include <Evas.hh>
#include <Eo.hh>
#include <Efl.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"
#include "canvas/evas_image.eo.hh"

#define WIDTH         320
#define HEIGHT        480

static const char *border_img_path = PACKAGE_EXAMPLES_DIR "/red.png";
static const char *edje_file_path = PACKAGE_EXAMPLES_DIR "/aspect.edj";

struct test_data
{
   Ecore_Evas  *ee;
   evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));
   Evas_Object *bg, *rect, *container, *border;
};

static struct test_data d = {0};

/* here just to keep our example's window size and background image's
 * size in synchrony */
static void
_canvas_resize_cb(Ecore_Evas *ee)
{
   int w, h;

   ::ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
   bg.evas::object::size_set( w, h);
}

static const char *
_get_aspect_name(Evas_Aspect_Control aspect)
{
   switch (aspect)
     {
      case 0:
        return "NONE";

      case 1:
        return "NEITHER";

      case 2:
        return "HORIZONTAL";

      case 3:
        return "VERTICAL";

      case 4:
        return "BOTH";

      default:
        return "INVALID";
     }
}

static void
_on_keydown(void *data EINA_UNUSED, Evas *evas EINA_UNUSED, Evas_Object *o, void *einfo)
{
   const Evas_Modifier *mods;
   Evas_Event_Key_Down *ev = einfo;

   mods = evas_key_modifier_get(evas_object_evas_get(o));

   if (evas_key_modifier_is_set(mods, "Shift") &&
       strcmp(ev->key, "h") == 0) /* print help */
     {
        fprintf(stdout, "commands are:\n"
                        "\tc - cycle aspect control on object\n"
                        "\th - change horizontal aspect component\n"
                        "\tv - change vertical aspect component\n"
                        "\ts - print current object's status\n"
                        "\tH - print help\n");
        return;
     }

   if (strcmp(ev->key, "s") == 0) /* get aspect status of the obj */
     {
        Evas_Coord w, h;
        Evas_Aspect_Control aspect;

        rect.size_hint_aspect_get(&aspect, &w, &h);

        fprintf(stdout, "Object has aspect %s, with horizontal compontent %d"
                        " and vertical compontent %d\n",
                _get_aspect_name(aspect), w, h);

        return;
     }

   if (strcmp(ev->key, "c") == 0) /* cycle aspect control on obj */
     {
        Evas_Coord w, h;
        Evas_Aspect_Control aspect;

        rect.size_hint_aspect_get(&aspect, &w, &h);

        aspect = (aspect + 1) % 5;

        rect.size_hint_aspect_set(aspect, w, h);

        fprintf(stdout, "Changing aspect control to %s\n",
                _get_aspect_name(aspect));

        return;
     }

   if (strcmp(ev->key, "h") == 0) /* change horizontal aspect component */
     {
        Evas_Coord w, h;
        Evas_Aspect_Control aspect;

        rect.size_hint_aspect_get(&aspect, &w, &h);

        w = (w + 1) % 3;

        rect.size_hint_aspect_set(aspect, w, h);

        fprintf(stdout, "Changing horizontal aspect component to %d\n", w);

        return;
     }

   if (strcmp(ev->key, "v") == 0) /* change vertical aspect component */
     {
        Evas_Coord w, h;
        Evas_Aspect_Control aspect;

        rect.size_hint_aspect_get(&aspect, &w, &h);

        h = (h + 1) % 3;

        rect.size_hint_aspect_set(aspect, w, h);

        fprintf(stdout, "Changing vertical aspect component to %d\n", h);

        return;
     }
}

int
main(void)
{
   Eina_Bool ret;

   efl::eina::eina_init eina_init;
   efl::eo::eo_init init;
   if (!::ecore_evas_init()) return EXIT_FAILURE;
   if (!::evas_init()) return EXIT_FAILURE;
   if (!::edje_init()) return EXIT_FAILURE;

   ee = ::ecore_evas_new(NULL, 10, 10, WIDTH, HEIGHT, NULL);
   if (!ee)
     goto error;

   ::ecore_evas_callback_resize_set(d.ee, _canvas_resize_cb);
   ::ecore_evas_show(d.ee);

   evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));

   evas::rectangle bg(efl::eo::parent = canvas);
   bg.color_set(255, 255, 255, 255);
   bg.position_set(0, 0); 
   bg.evas::object::size_set(WIDTH, HEIGHT); 
   bg.visibility_set(EINA_TRUE);

   bg.focus_set(EINA_TRUE);
   evas_object_event_callback_add(d.bg, EVAS_CALLBACK_KEY_DOWN, _on_keydown, NULL);

   d.container = edje_object_add(d.canvas);
   ret = edje_object_file_set(d.container, edje_file_path, "main");
   if (!ret)
     {
        Edje_Load_Error err = edje_object_load_error_get(d.container);
        const char *msg = edje_load_error_str(err);
        fprintf(stderr, "could not load 'main' from %s: %s",
                edje_file_path, msg);

        goto panic;
     }

   evas_object_move(d.container, (WIDTH / 4), (HEIGHT / 4));
   evas_object_resize(d.container, (WIDTH / 2), (HEIGHT / 2));
   evas_object_show(d.container);

   evas::rectangle rect(efl::eo::parent = canvas);
   rect.color_set( 0, 0, 255, 255);
   rect.size_hint_aspect_set(EVAS_ASPECT_CONTROL_NONE, 1, 1);
   rect.visibility_set(EINA_TRUE);

   edje_object_part_swallow(d.container, "content", d.rect);
   evas_object_smart_changed(d.container);

   evas::image border(efl::eo::parent = canvas);
   border.file_set(border_img_path, NULL);
   border.border_set(3, 3, 3, 3);
   border.border_center_fill_set(EVAS_BORDER_FILL_NONE);
   border.position_set((WIDTH / 4) - 3, (HEIGHT / 4) - 3);
   border.evas::object::size_set((WIDTH / 2) + 6, (HEIGHT / 2) + 6);
   border.visibility_set(EINA_TRUE);

   ecore_main_loop_begin();

   ecore_evas_free(d.ee);
   ecore_evas_shutdown();
   edje_shutdown();
   return 0;

error:
   fprintf(stderr, "you got to have at least one evas engine built and linked"
                   " up to ecore-evas for this example to run properly.\n");
panic:
   ecore_evas_free(ee);
   ecore_evas_shutdown();
   edje_shutdown();

   return -1;
}
