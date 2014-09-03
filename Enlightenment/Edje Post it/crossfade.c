#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <Eina.h>
#include <Evas.h>
#include <Ecore.h>
#include <Ecore_Evas.h>
#include <Edje.h>

#define WIDTH 1600
#define HEIGHT 800

static Evas_Object *test(Evas *canvas)
{
  Evas_Object *edje;
  edje = edje_object_add(canvas);

  if (!edje)
    {
      printf("Erro cód 165");
      return NULL;
    }

  if(!edje_object_file_set(edje, "/home/luciana/Public/Enlightenment/Edje Post it/crossfade.edj",
			   "test"))
     {
       printf("Erro cód 23");
       /* evas_object_del(edje); */
       return NULL;
     }

  /* evas_object_move(edje, 0, 0); */
  evas_object_resize(edje, WIDTH, HEIGHT);
  evas_object_show(edje);
  return edje;
}

int main(int argv)
{
  Ecore_Evas *ee;
  Evas *canvas;
  Evas_Object *edje;
  ecore_evas_init();
  edje_init();
  ee = ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);

  canvas = ecore_evas_get(ee);
  edje = test(canvas);

  if (!edje)
    return -2;
  ecore_evas_show(ee);
  ecore_main_loop_begin();
  evas_object_del(edje);
  ecore_evas_free(ee);
  edje_shutdown();
  ecore_evas_shutdown();
  return 0;
}
