#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

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
  Evas_Object *e_ret, *img_1, *img_clip;

  e_e = ecore_evas_new(NULL,0,0,800,1000,NULL);
  if (!e_e) return EXIT_FAILURE;

  ecore_evas_show(e_e);
  e_evas = ecore_evas_get(e_e);
  if (!e_evas) return EXIT_FAILURE;

  e_ret = evas_object_rectangle_add(e_evas);
  if (!e_ret) return EXIT_FAILURE;
  evas_object_color_set(e_ret,0,155,255,255);
  evas_object_move(e_ret,0,0);
  evas_object_resize(e_ret,800,1000);
  evas_object_show(e_ret);

  img_1 = evas_object_image_add(e_evas);
  evas_object_image_file_set(img_1,"/home/luciana/Public/img_1.jpeg",NULL);
  evas_object_move(img_1,200,300);
  evas_object_image_fill_set(img_1,0,0,252,200);
  evas_object_resize(img_1,252,200);
  evas_object_show(img_1);
  
  Evas_Load_Error err;
  if( (err = evas_object_image_load_error_get(img_1)) != EVAS_LOAD_ERROR_NONE)
    {
      fprintf(stderr, "error: %s\n", evas_load_error_str(err));
      exit(EXIT_FAILURE);
    }

  img_clip = evas_object_rectangle_add(e_evas);
  evas_object_color_set(img_clip,255,255,255,100);
  evas_object_move(img_clip,200,300);
  evas_object_resize(img_clip,252,200);
  evas_object_clip_set(img_1,img_clip);
  evas_object_show(img_clip);
  
  ecore_main_loop_begin();

  ecore_evas_free(e_e);
  ecore_evas_shutdown();
  return 0;
}
