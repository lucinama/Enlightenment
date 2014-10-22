#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <Evas.h>
#include <Ecore.h>
#include <Ecore_Evas.h>

#include <stdlib.h>

#include <Eo.hh>
#include <Evas.hh>
#include <Eina.hh>
#include <Efl.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"
#include "canvas/evas_table.eo.hh"

#define WIDTH  100
#define HEIGHT 150

Ecore_Evas  *ee;
evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));

static void
_on_destroy(Ecore_Evas *ee EINA_UNUSED)
{
::ecore_main_loop_quit();
}

static void
_canvas_resize_cb(Ecore_Evas *ee)
{
   int w, h;

   evas::rectangle bg(efl::eo::parent = canvas);
   ::ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
   bg.evas::object::size_set(w, h);
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
   fprintf(stderr, "you got to have at least one evas engine built and linked"
	   " up to ecore-evas for this example to run properly.\n");

   ::ecore_evas_callback_destroy_set(ee, _on_destroy);
   ::ecore_evas_callback_resize_set(ee, _canvas_resize_cb);
   ::ecore_evas_show(ee);

   evas::rectangle bg(efl::eo::parent = canvas);
   bg.color_set(255, 255, 255, 255);
   bg.position_set( 0, 0);
   bg.evas::object::size_set(WIDTH, HEIGHT); 
   bg.visibility_set(true);

   evas::table table(efl::eo::parent = canvas);
   table.homogeneous_set(EVAS_OBJECT_TABLE_HOMOGENEOUS_NONE);
   table.padding_set( 0, 0);
   table.evas::object::size_set(WIDTH, HEIGHT);
   table.visibility_set(true);

   evas::rectangle rect(efl::eo::parent = canvas);
   rect.color_set(255, 0, 0, 255);
   rect.size_hint_min_set(100, 50);
   rect.visibility_set(true);
   table.pack(rect, 1, 1, 2, 1);

   evas::rectangle rect2(efl::eo::parent = canvas);
   rect2.color_set( 0, 255, 0, 255);
   rect2.size_hint_min_set( 50, 100);
   rect2.visibility_set(true);
   table.pack(rect2, 1, 2, 1, 2);

   evas::rectangle rect3(efl::eo::parent = canvas);
   rect3.color_set(0, 0, 255, 255);
   rect3.size_hint_min_set(50, 50);
   rect3.visibility_set(true);
   table.pack(rect3, 2, 2, 1, 1);

   evas::rectangle rect4(efl::eo::parent = canvas);
   rect4.color_set(255, 255, 0, 255);
   rect4.size_hint_min_set(50, 50);
   rect4.visibility_set(true);
   table.pack(rect4, 2, 3, 1, 1);

   ::ecore_main_loop_begin();

   ::ecore_evas_free(ee);
   ::ecore_evas_shutdown();
   return 0;
}
