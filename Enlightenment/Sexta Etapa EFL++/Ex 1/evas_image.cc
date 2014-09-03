
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include <Evas.h>
#include <Ecore.h>
#include <Eo.h>
#include <Ecore_Evas.h>

#include <Eo.hh>
#include <Eina.hh>
#include <Evas.hh>
#include <Ecore.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_image.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

namespace efl { namespace evas {
    using ::evas::canvas;
    using ::evas::rectangle;
    using ::evas::image;
  } }

int main()
{
  Ecore_Evas *ee;
  efl::eina::eina_init eina_in;
  efl::eo::eo_init eo_in;
  efl::ecore::ecore_init ecore_in;
  ::ecore_evas_init();
  ::evas_init();

  ee = ::ecore_evas_new(NULL, 10, 10, 1600, 1000,NULL);
  ::ecore_evas_show(ee);

  //{
    efl::evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));
    efl::evas::rectangle rect(efl::eo::parent = canvas);
    rect.color_set(0,155,255,255);
    rect.position_set(0,0);
    rect.size_set(1600,1000);
    rect.visibility_set(true);
    
    // efl::evas::image cute_1(efl::eo::parent = canvas);
    // //cute_1.filled_set(true);
    // cute_1.file_plain_set("/home/luciana/Public/Enlightenment/cute_cat.jpeg");
    // cute_1.position_set(0,0);
    // cute_1.size_set(500,500);
    // cute_1.fill_set(0,0,640,400);
    // cute_1.visibility_set(true);

    //canvas.render();
    //::ecore_main_loop_begin();
    //}  
  //   ::evas_image cute_2(efl::eo::parent = canvas);
  //   cute_2.file_set("/home/luciana/Public/Enlightenment/cute_cat.jpeg",NULL);
  //   cute_2.position_set(960,600);
  //   cute_2.size_set(640,400);
  //   cute_2.fill_set(0,0,640,400);
  //   cute_2.visibility_set(true);
  

    evas::image cute_1_mini(efl::eo::parent = canvas);
    cute_1_mini.file_set("/home/luciana/Public/Enlightenment/cute_cat.jpeg", "");
    cute_1_mini.position_set(640,400);
    cute_1_mini.size_set(640,400);
    cute_1_mini.fill_set(0,0,320,200);
    cute_1_mini.size_set(320,200);
    cute_1_mini.visibility_set(true);
  // }

  // cute_mini_clip_1 = evas_object_rectangle_add(e_evas);
  // evas_object_color_set(cute_mini_clip_1,255,255,255,255);
  // evas_object_move(cute_mini_clip_1,640,400);
  // evas_object_resize(cute_mini_clip_1,160,100);
  // evas_object_clip_set(cute_mini_1,cute_mini_clip_1);
  // evas_object_show(cute_mini_clip_1);
 
  ::ecore_main_loop_begin();

  ::ecore_evas_free(ee);
  ::ecore_evas_shutdown();
  return 0;
}
