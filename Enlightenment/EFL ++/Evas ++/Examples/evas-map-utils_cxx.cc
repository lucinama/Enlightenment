#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define PACKAGE_EXAMPLES_DIR "/home/luciana/Enlightenment/src/efl/src/examples/evas"
#endif

#include <Ecore.h>
#include <Ecore_Evas.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <Eina.hh>
#include <Evas.hh>
#include <Eo.hh>
#include <Efl.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"
#include "canvas/evas_image.eo.hh"

#define WIDTH  480
#define HEIGHT 480

Ecore_Evas *ee;
evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));

typedef struct
{
   struct {
        int r, g, b, a;
   } colors[6];
   int colors_index;
   int frame;
   Eina_Bool   alpha : 1;
   Eina_Bool   smooth : 1;
   Eina_Bool   backface_culling : 1;
   Eina_Bool   apply_perspective : 1;
   Eina_Bool   apply_lighting : 1;
} App_Data;

static const char *help_string =
        "Valid commands:\n"
        "\ta - toggle alpha for maps\n"
        "\ts - toggle smooth for maps\n"
        "\tc - switch map color\n"
        "\tb - toggle backface culling\n"
        "\tp - toggle perspective\n"
        "\tl - toggle lighting\n"
        "\th - prints this help\n";

static Eina_Bool
_anim_cb(void *data)
{
   App_Data *ad = data;
   Evas_Map *m;
   evas::image o2(efl::eo::parent = canvas);
   evas::image o3(efl::eo::parent = canvas);
   evas::image o4(efl::eo::parent = canvas);
   evas::rectangle o1(efl::eo::parent = canvas);
   int r, g, b, a;
   int win_w, win_h, img_w, img_h;
   Evas_Coord x, y, w, h;

   ::evas_output_size_get(canvas, &win_w, &win_h);

   m = ::evas_map_new(4);
   ::evas_map_smooth_set(m, ad->smooth);
   ::evas_map_alpha_set(m, ad->alpha);

   r = ad->colors[ad->colors_index].r;
   g = ad->colors[ad->colors_index].g;
   b = ad->colors[ad->colors_index].b;
   a = ad->colors[ad->colors_index].a;
   ::evas_map_util_points_color_set(m, r, g, b, a);

   o1 = ::evas_object_name_find(canvas, "obj1");
evas_object_geometry_get(01, &x, &y, &w, &h);

   ::evas_map_util_points_populate_from_object(m, o1);
   ::evas_map_util_rotate(m, 3 * ad->frame, x + (w / 2), y + (h / 2));
   ::evas_object_map_set(o1, m);
   ::evas_object_map_enable_set(o1, EINA_TRUE);

   o2 = evas_object_name_find(canvas, "obj2");
   evas_object_geometry_get(o2, &x, &y, &w, &h);
   o2.size_get(&img_w, &img_h);

   ::evas_map_util_points_populate_from_object_full(m, o2, 100);
   ::evas_map_point_image_uv_set(m, 0, 0, 0);
   ::evas_map_point_image_uv_set(m, 1, img_w, 0);
   ::evas_map_point_image_uv_set(m, 2, img_w, img_h);
   ::evas_map_point_image_uv_set(m, 3, 0, img_h);
   ::evas_map_util_3d_rotate(m, ad->frame * 6, ad->frame * 6, ad->frame * 6,
                           x + (w / 3), y + 10, 0);
   if (ad->apply_lighting)
     ::evas_map_util_3d_lighting(m, win_w / 2, win_h / 2, -100,
                               255, 255, 255, 0, 0, 0);
   ::evas_object_map_set(o2, m);
   ::evas_object_map_enable_set(o2, EINA_TRUE);

   o3 = evas_object_name_find(canvas, "obj3");
   ::evas_object_geometry_get(o3, &x, &y, &w, &h);
   ::evas_object_image_size_get(o3, &img_w, &img_h);

   ::evas_map_util_points_populate_from_geometry(m, x, y + (h / 2), w, h, -20);
   ::evas_map_point_image_uv_set(m, 0, 0, 0);
   ::evas_map_point_image_uv_set(m, 1, img_w, 0);
   ::evas_map_point_image_uv_set(m, 2, img_w, img_h);
   ::evas_map_point_image_uv_set(m, 3, 0, img_h);
   ::evas_map_util_3d_rotate(m, 20, ad->frame * 6, 0, x + (w / 2), y + (w / 2), w / 2);

   if (ad->apply_perspective)
     ::evas_map_util_3d_perspective(m, x + (w / 2), y + (h / 2), 0, 256);
   if (ad->apply_lighting)
     {
        Evas_Coord mx, my;
        ::evas_pointer_canvas_xy_get(canvas, &mx, &my);
        ::evas_map_util_3d_lighting(m, mx, my, -256,
                                  255, 255, 255, 0, 0, 0);
     }
   if (ad->backface_culling)
     {
        if (evas_map_util_clockwise_get(m))
          o3.visibility_set(EINA_TRUE);
        else
          o3.visibility_set(EINA_FALSE);
     }
   else
     o3.visibility_set(EINA_TRUE);
::evas_object_map_set(o3, m);
::evas_object_map_enable_set(o3, EINA_TRUE);

::evas_map_free(m);

   o4 = evas_object_name_find(canvas, "obj4");
   ::evas_object_geometry_get(o4, &x, &y, &w, &h);
   (o4.source_get()).size_get(&img_w, &img_h);

   m = ::evas_map_new(4);
   ::evas_map_point_coord_set(m, 0, x, y + h, 0);
   ::evas_map_point_coord_set(m, 1, x + w, y + h, 0);
   ::evas_map_point_coord_set(m, 2, win_w - 10, win_h - 30, 0);
   ::evas_map_point_coord_set(m, 3, (win_w / 2) + 10, win_h - 30, 0);
   ::evas_map_point_image_uv_set(m, 0, 0, img_h);
   ::evas_map_point_image_uv_set(m, 1, img_w, img_h);
   ::evas_map_point_image_uv_set(m, 2, img_w, 2 * (img_h / 3));
   ::evas_map_point_image_uv_set(m, 3, 0, 2 * (img_h / 3));
   ::evas_map_point_color_set(m, 0, 200, 200, 200, 150);
   ::evas_map_point_color_set(m, 1, 200, 200, 200, 150);
   ::evas_map_point_color_set(m, 2, 0, 0, 0, 0);
   ::evas_map_point_color_set(m, 3, 0, 0, 0, 0);
   ::evas_object_map_set(o4, m);
   ::evas_object_map_enable_set(o4, EINA_TRUE);

   ::evas_map_free(m);

   ad->frame = (ad->frame + 1) % 60;

   return EINA_TRUE;
}

static void
_on_keydown(void *data, Evas *e EINA_UNUSED, Evas_Object *o EINA_UNUSED, Evas_Event_Key_Down *ev)
{
   App_Data *ad = data;
   //Evas_Event_Key_Down *ev = event;
   switch (ev->key[0])
     {
      case 'a':
         ad->alpha = !ad->alpha;
         break;
      case 's':
         ad->smooth = !ad->smooth;
         break;
      case 'c':
         ad->colors_index = (ad->colors_index + 1) % 6;
         break;
      case 'b':
         ad->backface_culling = !ad->backface_culling;
         break;
      case 'p':
         ad->apply_perspective = !ad->apply_perspective;
         break;
      case 'l':
         ad->apply_lighting = !ad->apply_lighting;
         break;
      case 'h':
         puts(help_string);
         break;
      default:
         break;
     }
}

static void
_objs_fit(Evas *e)
{
   int w, h;

   evas::image o2(efl::eo::parent = canvas);
   evas::image o3(efl::eo::parent = canvas);
   evas::image o4(efl::eo::parent = canvas);
   evas::rectangle o1(efl::eo::parent = canvas);

   e.output_size_get( &w, &h);
   w /= 2;
   h /= 2;

   o1 = e.name_find("obj1");
   o1.position_set(w / 4, h / 4);
   o1.evas::object::size_set(w / 2, h / 2);

   o2 = e.name_find("obj2");
   o2.position_set(5 * w / 4, h / 4);
   o2.evas::object::size_set(w / 2, h / 2);

   o3 = e.name_find("obj3");
   o3.position_set( w / 4, 5 * h / 4);
   o3.evas::object::size_set(w / 2, h / 2);

   os = e.name_find("obj4_source");
   os.position_set(5 * w / 4, 5 * h / 4);
   os.evas::object::size_set( w / 2, h / 2);

   o4 = e.name_find("obj4");
   o4.position_set(5 * w / 4, 5 * h / 4);
   o4.evas::object::size_set( w / 2, h / 2);
}

static void
_on_resize(void *data EINA_UNUSED, Evas *e, Evas_Object *o EINA_UNUSED, void *event EINA_UNUSED)
{
   _objs_fit(e);
}

static void
_on_free(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *o EINA_UNUSED, void *event EINA_UNUSED)
{
   ecore_main_loop_quit();
}

int
main(void)
{
   Evas_Object *osrc;
   static App_Data d = {
        .colors = {
             { 255, 255, 255, 255 },
             { 128, 128, 0, 128 },
             { 255, 0, 0, 255 },
             { 64, 128, 255, 255 },
             { 11, 23, 58, 132 },
             { 0, 0, 0, 255 }
        },
        .colors_index = 0,
        .frame = 0,
        .alpha = EINA_FALSE,
        .smooth = EINA_FALSE,
        .backface_culling = EINA_FALSE,
        .apply_perspective = EINA_TRUE,
        .apply_lighting = EINA_TRUE
   };

  efl::eina::eina_init eina_init;
  efl::eo::eo_init init;
  if (!::ecore_evas_init()) return EXIT_FAILURE;
  if (!::evas_init()) return EXIT_FAILURE;

  ee = ::ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);
   if (!ee)
     goto error;

   evas::image bg(efl::eo::parent = canvas);
   bg.file_set("cube1.png", NULL);
   ::ecore_evas_object_associate(ee, bg, 0);
   bg.focus_set(EINA_TRUE);
   bg.position_set( 0, 0);
   bg.evas::object::size_set( WIDTH, HEIGHT);
   bg.visibility_set(EINA_TRUE);

   evas::rectangle o1(efl::eo::parent = canvas);
   o1.name_set("obj1");
   o1.color_set(128, 0, 200, 200);
   o1.visibility_set(EINA_TRUE);

   evas::image o2(efl::eo::parent = canvas);
   o2.name_set("obj2");
   o2.image_file_set("enlightenment.png", NULL);
   o2.visibility_set(EINA_TRUE);

   evas::image o3(efl::eo::parent = canvas);
   o3.name_set("obj3");
   o3.file_set("enlightenment.png", NULL);
   o3.visibility_set(EINA_TRUE);

   evas::image osrc(efl::eo::parent = canvas);
   osrc.file_set("im1.png", NULL);
   osrc.name_set("obj4_source");
   osrc.visibility_set(EINA_TRUE);

   evas::image o4(efl::eo::parent = canvas);
   o4.source_set(osrc);
   o4.name_set("obj4");
   o4.visibility_set(EINA_TRUE);

   _objs_fit(d.canvas);

   ::evas_object_event_callback_add(bg, EVAS_CALLBACK_KEY_DOWN, _on_keydown, &d);
   ::evas_object_event_callback_add(bg, EVAS_CALLBACK_RESIZE, _on_resize, NULL);
   ::evas_object_event_callback_add(bg, EVAS_CALLBACK_FREE, _on_free, NULL);

   ::ecore_animator_add(_anim_cb, &d);

   ecore_main_loop_begin();

   ::ecore_evas_shutdown();
   return 0;

error:
   fprintf(stderr, "you got to have at least one evas engine built and linked"
                   " up to ecore-evas for this example to run properly.\n");
   ecore_evas_shutdown();
   return -1;
}
