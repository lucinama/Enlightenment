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
  Evas_Object *e_ret, *img_1, *img_clip, *cute_1, *cute_2, *cute_mini_1, *cute_mini_2, *cute_mini_clip_1, *cute_mini_clip_2;

  e_e = ecore_evas_new(NULL,0,0,1600,1000,NULL);
  if (!e_e) return EXIT_FAILURE;

  ecore_evas_show(e_e);
  e_evas = ecore_evas_get(e_e);
  if (!e_evas) return EXIT_FAILURE;

  e_ret = evas_object_rectangle_add(e_evas);
  if (!e_ret) return EXIT_FAILURE;
  evas_object_color_set(e_ret,0,155,255,255);
  evas_object_move(e_ret,0,0);
  evas_object_resize(e_ret,1600,1000);
  evas_object_show(e_ret);

  cute_1 = evas_object_image_add(e_evas);
  evas_object_image_file_set(cute_1,"/home/luciana/Public/Enlightenment/cute_cat.jpeg",NULL);
  evas_object_move(cute_1,0,0);
  evas_object_resize(cute_1,640,400);
  evas_object_image_fill_set(cute_1,0,0,640,400);
  evas_object_show(cute_1);
 
  cute_2 = evas_object_image_add(e_evas);
  evas_object_image_file_set(cute_2,"/home/luciana/Public/Enlightenment/cute_cat.jpeg",NULL);
  evas_object_move(cute_2,960,600);
  evas_object_resize(cute_2,640,400);
  evas_object_image_fill_set(cute_2,0,0,640,400);
  evas_object_show(cute_2); 
  

  cute_mini_1 = evas_object_image_add(e_evas);
  evas_object_image_file_set(cute_mini_1,"/home/luciana/Public/Enlightenment/cute_cat.jpeg",NULL);
  evas_object_move(cute_mini_1,640,400);
  evas_object_resize(cute_mini_1,640,400);
  evas_object_image_fill_set(cute_mini_1,0,0,320,200);
  evas_object_resize(cute_mini_1,320,200);
  evas_object_show(cute_mini_1);

  cute_mini_2 = evas_object_image_add(e_evas);
  evas_object_image_file_set(cute_mini_2,"/home/luciana/Public/Enlightenment/cute_cat.jpeg",NULL);
  evas_object_move(cute_mini_2,640,400);
  evas_object_resize(cute_mini_2,640,400);
  evas_object_image_fill_set(cute_mini_2,0,0,320,200);
  evas_object_resize(cute_mini_2,320,200);
  evas_object_show(cute_mini_2);
    
  Evas_Load_Error err;
  if( (err = evas_object_image_load_error_get(img_1)) != EVAS_LOAD_ERROR_NONE)
    {
      fprintf(stderr, "error: %s\n", evas_load_error_str(err));
      exit(EXIT_FAILURE);
    }

  /* cute_mini_alpha = evas_object_rectangle_add(e_evas); */
  /* evas_object_color_set(cute_mini_alpha,255,255,255,155); */
  /* evas_object_move(cute_mini_alpha,6400,400); */
  /* evas_object_resize(cute_mini_alpha,320,200); */
  /* evas_object_clip_set(cute_mini,cute_mini_alpha); */
  /* evas_object_show(cute_mini_alpha); */
  
  cute_mini_clip_1 = evas_object_rectangle_add(e_evas);
  evas_object_color_set(cute_mini_clip_1,255,255,255,255);
  evas_object_move(cute_mini_clip_1,640,400);
  evas_object_resize(cute_mini_clip_1,160,100);
  evas_object_clip_set(cute_mini_1,cute_mini_clip_1);
  evas_object_show(cute_mini_clip_1);

  cute_mini_clip_2 = evas_object_rectangle_add(e_evas);
  evas_object_color_set(cute_mini_clip_2,255,255,255,255);
  evas_object_move(cute_mini_clip_2,800,500);
  evas_object_resize(cute_mini_clip_2,160,100);
  evas_object_clip_set(cute_mini_2,cute_mini_clip_2);
  evas_object_show(cute_mini_clip_2);

  ecore_main_loop_begin();

  ecore_evas_free(e_e);
  ecore_evas_shutdown();
  return 0;
}
