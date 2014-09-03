#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <Eo.h>
#include <Evas.h>
#include <Ecore.h>
#include <Ecore_Evas.h>
#include <stdio.h>

int main(void)
{
  if(!ecore_evas_init())
    return EXIT_FAILURE;

  Ecore_Evas *e_e;
  Evas *e_evas;
  Eo *e_ret;

  e_e = ecore_evas_new(NULL,0,0,500,500,NULL);
  if (!e_evas) return EXIT_FAILURE;
  
  ecore_evas_show(e_e);
  e_evas = ecore_evas_get(e_e);
  if(!e_evas) return EXIT_FAILURE;

  e_ret = eo_add(evas_obj_rectangle_add(e_evas));
  eo_do(e_ret, evas_obj_move(0,0), evas_obj_resize(500,500), evas_obj_color_set(0,155,255,200));

  evas_object_show(e_ret);

  ecore_main_loop_begin();
  
  ecore_evas_free(e_e);
  ecore_evas_shutdown();
  return 0;
}

