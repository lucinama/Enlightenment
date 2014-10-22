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

static const char *img_path = PACKAGE_EXAMPLES_DIR "/enlightenment.png";
static const char *commands = \
  "commands are:\n"
  "\tp - change proxy image's source\n"
  "\ts - print noise image's stride value\n"
  "\ta - save noise image to disk (/tmp dir)\n"
  "\tv - change source visibility\n"
  "\te - enable/disable source events\n"
  "\th - print help\n";

const char *file_path = "/tmp/evas-images2-example.png";
const char *quality_str = "quality=100";

struct test_data
{
   Ecore_Evas  *ee;
   Evas        *evas;
   Evas_Object *logo, *noise_img, *proxy_img, *bg;
};

static struct test_data d = {0};

static void
_mouse_down(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,
            void *event_info)
{
   Evas_Event_Mouse_Down *ev = event_info;
   printf("Mouse Down - obj(%p), coords(%d %d)\n", obj, ev->canvas.x,
          ev->canvas.y);
}

static void
_mouse_move(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,
            void *event_info)
{
   Evas_Event_Mouse_Move *ev = event_info;
   printf("Mouse Move - obj(%p), coords(%d %d)\n", obj, ev->cur.canvas.x,
          ev->cur.canvas.y);
}

static void
_mouse_up(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,
          void *event_info)
{
   Evas_Event_Mouse_Up *ev = event_info;
   printf("Mouse Up - obj(%p), coords(%d %d)\n", obj, ev->canvas.x,
          ev->canvas.y);
}

static void
_multi_down(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,
            void *event_info)
{
   Evas_Event_Multi_Down *ev = event_info;
   printf("Multi Down - obj(%p), coords(%d %d)\n", obj, ev->canvas.x,
          ev->canvas.y);
}

static void
_multi_move(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,
             void *event_info)
{
   Evas_Event_Multi_Move *ev = event_info;
   printf("Multi Move - obj(%p), coords(%d %d)\n", obj, ev->cur.canvas.x,
          ev->cur.canvas.y);
}

static void
_multi_up(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,
          void *event_info)
{
   Evas_Event_Multi_Up *ev = event_info;
   printf("Multi Up - obj(%p), coords(%d %d)\n", obj, ev->canvas.x,
          ev->canvas.y);
}

static void
_mouse_in(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,
          void *event_info)
{
   Evas_Event_Mouse_In *ev = event_info;
   printf("Mouse In - obj(%p), coords(%d %d)\n", obj, ev->canvas.x,
          ev->canvas.y);
}

static void
_mouse_out(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,
           void *event_info)
{
   Evas_Event_Mouse_Out *ev = event_info;
   printf("Mouse Out - obj(%p), coords(%d %d)\n", obj, ev->canvas.x,
          ev->canvas.y);
}

static void
_hold(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,
      void *event_info)
{
   Evas_Event_Hold *ev = event_info;
   printf("Hold - obj(%p), hold(%d)\n", obj, ev->hold);
}

static void
_on_preloaded(void        *data EINA_UNUSED,
              Evas        *e EINA_UNUSED,
              Evas_Object *obj EINA_UNUSED,
              void        *event_info EINA_UNUSED)
{
    fprintf(stdout, "Image has been pre-loaded!\n");
}

static void
_on_destroy(Ecore_Evas *ee EINA_UNUSED)
{
   ecore_main_loop_quit();
}

static void
_canvas_resize_cb(Ecore_Evas *ee)
{
   int w, h;

   ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
   evas_object_resize(d.bg, w, h);
}

static void
_on_keydown(void        *data EINA_UNUSED,
            Evas        *evas EINA_UNUSED,
            Evas_Object *o EINA_UNUSED,
            void        *einfo)
{
   Evas_Event_Key_Down *ev = einfo;

   if (strcmp(ev->key, "h") == 0) 
     {
        fprintf(stdout, commands);
        return;
     }

   if (strcmp(ev->key, "s") == 0) 
     {
        int stride = evas_object_image_stride_get(d.noise_img);

        fprintf(stdout, "Image has row stride value of %d, which accounts"
                        " for %d pixels\n", stride, stride / 4);

        return;
     }

   if (strcmp(ev->key, "p") == 0) /* change proxy's source */
     {
        Evas_Object *source = evas_object_image_source_get(d.proxy_img);

        if (source == d.logo) source = d.noise_img;
        else source = d.logo;

        evas_object_image_source_set(d.proxy_img, source);

        fprintf(stdout, "Proxy image's source changed\n");

        return;
     }

   if (strcmp(ev->key, "a") == 0)
     {
        if (!evas_object_image_save(d.noise_img, file_path, NULL, quality_str))
          fprintf(stderr, "Cannot save image to '%s' (flags '%s')\n",
                  file_path, quality_str);
        else
          fprintf(stdout, "Image saved to '%s' (flags '%s'), check it out with "
                          "an image viewer\n", file_path, quality_str);

        return;
     }

   if (strcmp(ev->key, "v") == 0)
     {
        Eina_Bool src_visible =
           evas_object_image_source_visible_get(d.proxy_img);
        evas_object_image_source_visible_set(d.proxy_img, !src_visible);
        return;
     }

   if (strcmp(ev->key, "e") == 0)
     {
        Eina_Bool src_events = evas_object_image_source_events_get(d.proxy_img);
        evas_object_image_source_events_set(d.proxy_img, !src_events);
        return;
     }
}

int
main(void)
{
   unsigned int i;
   unsigned int pixels[(WIDTH / 4) * (HEIGHT / 4)];

   srand(time(NULL));

   if (!ecore_evas_init())
     return EXIT_FAILURE;

   d.ee = ecore_evas_new(NULL, 10, 10, WIDTH, HEIGHT, NULL);
   if (!d.ee)
     goto error;

   ecore_evas_callback_destroy_set(d.ee, _on_destroy);
   ecore_evas_callback_resize_set(d.ee, _canvas_resize_cb);
   ecore_evas_show(d.ee);

   evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));

   evas::rectangle bg(efl::eo::parent = canvas);
   bg.color_set(255, 255, 255, 255);
   bg.position_set(0, 0); 
   bg.evas::object::size_set(WIDTH, HEIGHT); 
   bg.visibility_set(EINA_TRUE);

   evas_object_focus_set(d.bg, EINA_TRUE);
   evas_object_event_callback_add(
     d.bg, EVAS_CALLBACK_KEY_DOWN, _on_keydown, NULL);

   logo = evas_object_image_filled_add(d.evas);

   evas_object_event_callback_add(logo, EVAS_CALLBACK_IMAGE_PRELOADED, _on_preloaded, NULL);
   logo.preload(EINA_TRUE);

   evas_object_image_file_set(d.logo, img_path, NULL);
   evas_object_resize(d.logo, WIDTH / 2, HEIGHT / 2);
   evas_object_event_callback_add(d.logo, EVAS_CALLBACK_MOUSE_DOWN, _mouse_down, 0);
   evas_object_event_callback_add(d.logo, EVAS_CALLBACK_MOUSE_MOVE, _mouse_move, 0);
   evas_object_event_callback_add(d.logo, EVAS_CALLBACK_MOUSE_UP, _mouse_up, 0);
   evas_object_event_callback_add(d.logo, EVAS_CALLBACK_MOUSE_IN, _mouse_in, 0);
   evas_object_event_callback_add(d.logo, EVAS_CALLBACK_MOUSE_OUT, _mouse_out, 0);
   evas_object_event_callback_add(d.logo, EVAS_CALLBACK_MULTI_DOWN, _multi_down, 0);
   evas_object_event_callback_add(d.logo, EVAS_CALLBACK_MULTI_UP, _multi_up, 0);
   evas_object_event_callback_add(d.logo, EVAS_CALLBACK_MULTI_MOVE, _multi_move, 0);
   evas_object_event_callback_add(d.logo, EVAS_CALLBACK_HOLD, _hold, 0);

   evas_object_show(d.logo);

   for (i = 0; i < sizeof(pixels) / sizeof(pixels[0]); i++)
     pixels[i] = rand();

   evas::image noise_img(efl::eo::parent = canvas);
   noise_img.size_set(WIDTH / 4, HEIGHT / 4);
   noise_img.data_set( pixels);
   noise_img.filled_set( EINA_TRUE);
   noise_img.position_set((WIDTH * 3) / 4, 0);
   noise_img.evas::object::size_set(WIDTH / 4, HEIGHT / 4);
   noise_img.visibility_set(EINA_TRUE);
   fprintf(stdout, "Creating noise image with size %d, %d\n", WIDTH / 4, HEIGHT / 4);

   d.proxy_img = evas_object_image_filled_add(d.evas);
   proxy_img.source_set(logo);
   proxy_img.position_set(WIDTH / 4, HEIGHT / 2);
   proxy_img.evas::object::size_set(d.proxy_img, WIDTH / 2, HEIGHT / 2);
   proxy_img.visibility_set(EINA_TRUE);

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
