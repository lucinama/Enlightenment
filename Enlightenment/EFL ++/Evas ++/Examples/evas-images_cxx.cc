#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define PACKAGE_EXAMPLES_DIR "/home/luciana/Enlightenment/src/efl/src/examples/evas"
#endif

#include <Ecore.h>
#include <Ecore_Evas.h>
#include <stdio.h>
#include <errno.h>

#include <Eina.hh>
#include <Evas.hh>
#include <Eo.hh>
#include <Efl.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"
#include "canvas/evas_image.eo.hh"

#define WIDTH  (320)
#define HEIGHT (240)

static const char *border_img_path = PACKAGE_EXAMPLES_DIR "/red.png";
static const char *valid_path = PACKAGE_EXAMPLES_DIR "/enlightenment.png";
static const char *bogus_path = "/tmp/non-existent-220986.png";
static const char *commands = \
  "commands are:\n"
  "\tx - change image's x fill coordinate\n"
  "\ty - change image's y fill coordinate\n"
  "\tw - change image's w fill size\n"
  "\te - change image's h fill size\n"
  "\tf - toggle image filled property (overrides fill)\n"
  "\ta - toggle image's alpha channel usage\n"
  "\tm - toggle border's smooth scaling\n"
  "\tt - change border's thickness\n"
  "\tb - change border's center region aspect\n"
  "\tc - change border's scaling factor\n"
  "\ts - print image's fill property status\n"
  "\th - print help\n";

struct test_data
{
   Ecore_Evas  *ee;
   Evas        *evas;
   Evas_Object *img1, *img2, *bg, *border;
};

static struct test_data d = {0};

static void
_on_destroy(Ecore_Evas *ee EINA_UNUSED)
{
   ecore_main_loop_quit();
}

/* here just to keep our example's window size and background image's
 * size in synchrony */
static void
_canvas_resize_cb(Ecore_Evas *ee)
{
   int w, h;

   ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
   evas_object_resize(d.bg, w, h);
}

static const char *
_border_fill_mode_to_str(Evas_Border_Fill_Mode mode)
{
   switch (mode)
     {
      case EVAS_BORDER_FILL_NONE:
        return "none";

      case EVAS_BORDER_FILL_DEFAULT:
        return "default";

      case EVAS_BORDER_FILL_SOLID:
        return "solid";

      default:
        return "invalid";
     }
}

static void
_on_keydown(void        *data EINA_UNUSED,
            Evas        *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void        *einfo)
{
   Evas_Event_Key_Down *ev = einfo;

   if (strcmp(ev->key, "h") == 0) /* print help */
     {
        fprintf(stdout, commands);
        return;
     }

   if (strcmp(ev->key, "m") == 0) /* toggle border image's smooth scaling */
     {
        Eina_Bool smooth_scale = evas_object_image_smooth_scale_get(d.border);

        evas_object_image_smooth_scale_set(d.border, !smooth_scale);

        fprintf(stdout, "Image's border is now %s smooth scaling\n",
                smooth_scale ? "without" : "with");

        return;
     }

   if (strcmp(ev->key, "t") == 0)
     {
        int l, r, t, b;

        evas_object_image_border_get(d.border, &l, &r, &t, &b);

        l = (l + 3) % 9;
        r = (r + 3) % 9;
        t = (t + 3) % 9;
        b = (b + 3) % 9;

        evas_object_image_border_set(d.border, l, r, t, b);

        fprintf(stdout, "Image's border thickness is now %d\n", l);

        return;
     }

   if (strcmp(ev->key, "c") == 0)
     {
        double scale = evas_object_image_border_scale_get(d.border);

        scale *= 2;
        if (scale > 4.0) scale = 1.0;

        evas_object_image_border_scale_set(d.border, scale);

        fprintf(stdout, "Image's border scaling factor is now %f\n", scale);

        return;
     }

   if (strcmp(ev->key, "b") == 0)
     {
        Eina_Bool fill = \
          evas_object_image_border_center_fill_get(d.border);

        fill = (fill + 1) % 3;

        evas_object_image_border_center_fill_set(d.border, fill);

        fprintf(stdout, "Image's border center region aspect is now \"%s\"\n",
                _border_fill_mode_to_str(fill));

        return;
     }

   if (strcmp(ev->key, "a") == 0) /* toggle alpha channel usage */
     {
        Eina_Bool alpha = evas_object_image_alpha_get(d.img1);

        evas_object_image_alpha_set(d.img1, !alpha);

        fprintf(stdout, "Image's alpha channel is now %s\n",
                alpha ? "off" : "on");

        return;
     }

   if (strcmp(ev->key, "f") == 0) 
     {
        Eina_Bool filled = evas_object_image_filled_get(d.img1);

        evas_object_image_filled_set(d.img1, !filled);

        fprintf(stdout, "Image's x filled property is now %s\n",
                filled ? "off" : "on");

        return;
     }

   if (strcmp(ev->key, "x") == 0) 
     {
        Evas_Coord x, y, w, h;

        evas_object_image_fill_get(d.img1, &x, &y, &w, &h);
        x = (x + 20) % (WIDTH / 2);
        evas_object_image_fill_set(d.img1, x, y, w, h);

        fprintf(stdout, "Image's x fill coordinate changed to %d\n", x);

        return;
     }

   if (strcmp(ev->key, "y") == 0) 
     {
        Evas_Coord x, y, w, h;

        evas_object_image_fill_get(d.img1, &x, &y, &w, &h);
        y = (y + 20) % (HEIGHT / 2);
        evas_object_image_fill_set(d.img1, x, y, w, h);

        fprintf(stdout, "Image's y fill coordinate changed to %d\n", y);

        return;
     }

   if (strcmp(ev->key, "w") == 0)
     {
        Evas_Coord x, y, w, h;

        evas_object_image_fill_get(d.img1, &x, &y, &w, &h);
        if (w == (WIDTH / 4)) w = (WIDTH / 2);
        else if (w == WIDTH / 2) w = WIDTH;
        else w = (WIDTH / 4);
        evas_object_image_fill_set(d.img1, x, y, w, h);

        fprintf(stdout, "Image's w fill size changed to %d\n", w);

        return;
     }

   if (strcmp(ev->key, "e") == 0)
     {
        Evas_Coord x, y, w, h;

        evas_object_image_fill_get(d.img1, &x, &y, &w, &h);
        if (h == (HEIGHT / 4)) h = (HEIGHT / 2);
        else if (h == HEIGHT / 2) h = HEIGHT;
        else h = (HEIGHT / 4);
        evas_object_image_fill_set(d.img1, x, y, w, h);

        fprintf(stdout, "Image's h fill size changed to %d\n", h);

        return;
     }

   if (strcmp(ev->key, "s") == 0)
     {
        Evas_Coord x, y, w, h;

        evas_object_image_fill_get(d.img1, &x, &y, &w, &h);

        fprintf(stdout, "Image has fill properties set to: %d, %d, %d, %d\n",
                x, y, w, h);

        return;
     }
}

int
main(void)
{
   int err;

   if (!ecore_evas_init())
     return EXIT_FAILURE;

   ee = ::ecore_evas_new(NULL, 10, 10, WIDTH, HEIGHT, NULL);
   if (!ee)
     goto error;

   ecore_evas_callback_destroy_set(ee, _on_destroy);
   ecore_evas_callback_resize_set(ee, _canvas_resize_cb);
   ::ecore_evas_show(ee);

   evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));

   evas::rectangle bg(efl::eo::parent = canvas);
   bg.color_set(255, 255, 255, 255);
   bg.position_set(0, 0); 
   bg.evas::object::size_set(WIDTH, HEIGHT); 
   bg.visibility_set(EINA_TRUE);

   evas::image img1(efl::eo::parent = canvas);
   img1.file_set(valid_path, NULL);
   err = evas_object_image_load_error_get(d.img1);
   if (err != EVAS_LOAD_ERROR_NONE)
     {
        fprintf(stderr, "could not load image '%s'. error string is \"%s\"\n",
                valid_path, evas_load_error_str(err));
     }
   else
     {
        fprintf(stdout,
                "loaded image '%s' with succes! error string is \"%s\"\n",
                valid_path, evas_load_error_str(err));

        img1.position_set(3, 3);
        img1.fill_set(d.img1, 0, 0, WIDTH / 2, HEIGHT / 2);
	img1.evas::object::size_set(WIDTH / 2, HEIGHT / 2);
        img1.visibility_set(EINA_TRUE);

        bg.focus_set(EINA_TRUE);
        evas_object_event_callback_add(bg, EVAS_CALLBACK_KEY_DOWN, _on_keydown, NULL);
     }

    d.border = evas_object_image_filled_add(d.evas);
    border.file_set( border_img_path, NULL);
   border.border_set(3, 3, 3, 3);
   border.border_center_fill_set( EVAS_BORDER_FILL_NONE);

   border.position_set( 0, 0);
   border.evas::object::size_set((WIDTH / 2) + 6, (HEIGHT / 2) + 6);
   border.visibility_set(EINA_TRUE);

   evas::image img2(efl::eo::parent = canvas);
   img2.file_set(bogus_path, NULL);
   err = evas_object_image_load_error_get(d.img2);
   if (err != EVAS_LOAD_ERROR_NONE)
     {
        fprintf(stderr, "could not load image '%s': error string is \"%s\"\n",
                bogus_path, evas_load_error_str(err));
     }
   else
     {
        img2.position_set( WIDTH / 2, HEIGHT / 2);
        img2.fill_set(0, 0, WIDTH / 2, HEIGHT / 2);
        img2.evas::object::size_set(WIDTH / 2, HEIGHT / 2);
        img2.visibility_set(EINA_TRUE);
     }

   fprintf(stdout, commands);
   ecore_main_loop_begin();

   ecore_evas_free(d.ee);
   ecore_evas_shutdown();
   return 0;

error:
   fprintf(stderr, "you got to have at least one evas engine built and linked"
                   " up to ecore-evas for this example to run properly.\n");
   ecore_evas_shutdown();
   return -1;
}
