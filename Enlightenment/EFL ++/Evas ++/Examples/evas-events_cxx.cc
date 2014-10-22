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
  "\ta - toggle animation timer\n"
  "\tc - cycle between focus and key grabs for key input\n"
  "\td - delete canvas callbacks\n"
  "\tf - freeze input for 3 seconds\n"
  "\tp - toggle precise point collision detection on image\n"
  "\tControl + o - add an obscured rectangle\n"
  "\th - print help\n";

struct test_data
{
   Ecore_Evas  *ee;
   Evas        *canvas;
   Evas_Object *img, *bg;
   Ecore_Timer *resize_timer, *freeze_timer;
   Eina_Bool    obscured, focus;
};

static struct test_data d = {0};

static void
_canvas_resize_cb(Ecore_Evas *ee)
{
   int w, h;

   ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
   bg.evas::object::size_set(w, h);
}

static void
_object_focus_in_cb(void *data EINA_UNUSED,
                    Evas *e,
                    void *event_info)
{
   fprintf(stdout, "An object got focused: %s\n",
           evas_object_name_get(event_info));

   fprintf(stdout, "Let's recheck it: %s\n",
           evas_object_name_get(evas_focus_get(e)));

   fprintf(stdout, "And again: %s\n", evas_object_focus_get(event_info) ?
           "OK!" : "Oops, something is bad.");
}

static void
_render_flush_cb(void *data EINA_UNUSED,
                 Evas *e EINA_UNUSED,
                 void *event_info EINA_UNUSED)
{
   fprintf(stdout, "Canvas is about to flush its rendering pipeline!\n");
}

static Eina_Bool
_resize_cb(void *data EINA_UNUSED)
{
   int w, h, cw, ch;

   evas_object_geometry_get(d.img, NULL, NULL, &w, &h);
   ecore_evas_geometry_get(d.ee, NULL, NULL, &cw, &ch);

   if (w < cw)
     img.evas::object::size_set(cw, ch);
   else
     img.evas::0object::size_set(cw / 2, ch / 2);

   return EINA_TRUE;
}

static Eina_Bool
_thaw_cb(void *data EINA_UNUSED)
{
   fprintf(stdout, "Canvas was frozen %d times, now thawing.\n",
           evas_event_freeze_get(d.canvas));
   evas_event_thaw(d.canvas);
   return EINA_FALSE;
}

static void
_on_mouse_in(void        *data EINA_UNUSED,
             Evas        *evas EINA_UNUSED,
             Evas_Object *o EINA_UNUSED,
             void        *einfo EINA_UNUSED)
{
   fprintf(stdout, "Enlightenment logo has had the mouse in.\n");
}

static void
_on_mouse_out(void        *data EINA_UNUSED,
              Evas        *evas EINA_UNUSED,
              Evas_Object *o EINA_UNUSED,
              void        *einfo EINA_UNUSED)
{
   fprintf(stdout, "Enlightenment logo has had the mouse out.\n");
} 

static void
_on_keydown(void        *data EINA_UNUSED,
            Evas        *evas,
            Evas_Object *o EINA_UNUSED,
            void        *einfo)
{
   const Evas_Modifier *mods;
   Evas_Event_Key_Down *ev = einfo;

   fprintf(stdout, "We've got key input: %s\n", ev->key);
   fprintf(stdout, "It actually came from %s\n", d.focus ?
           "focus" : "key grab");

   if (strcmp(ev->key, "h") == 0)
     {
        fprintf(stdout, commands);
        return;
     }

   if (strcmp(ev->key, "a") == 0)
     {
        if (d.resize_timer != NULL)
          {
             fprintf(stdout, "Stopping animation timer\n");
             ecore_timer_del(d.resize_timer);
             d.resize_timer = NULL;
          }
        else
          {
             fprintf(stdout, "Re-issuing animation timer\n");
             d.resize_timer = ecore_timer_add(2, _resize_cb, NULL);
          }
        return;
     }

   if (strcmp(ev->key, "c") == 0)
     {
        Eina_Bool ret;
        Evas_Modifier_Mask mask =
          evas_key_modifier_mask_get(d.canvas, "Control");

        fprintf(stdout, "Switching to %s for key input\n", d.focus ?
                "key grabs" : "focus");

        if (d.focus)
          {
             evas_object_focus_set(d.bg, EINA_FALSE);
             fprintf(stdout, "Focused object is now %s\n",
                     evas_focus_get(d.canvas) ?
                     "still valid! Something went wrong." : "none.");

             ret = evas_object_key_grab(d.bg, "a", 0, 0, EINA_TRUE);
             if (!ret)
               {
                  fprintf(stdout, "Something went wrong with key grabs.\n");
                  goto c_end;
               }
             ret = evas_object_key_grab(d.bg, "c", 0, 0, EINA_TRUE);
             if (!ret)
               {
                  fprintf(stdout, "Something went wrong with key grabs.\n");
                  goto c_end;
               }
             ret = evas_object_key_grab(d.bg, "d", 0, 0, EINA_TRUE);
             if (!ret)
               {
                  fprintf(stdout, "Something went wrong with key grabs.\n");
                  goto c_end;
               }
             ret = evas_object_key_grab(d.bg, "f", 0, 0, EINA_TRUE);
             if (!ret)
               {
                  fprintf(stdout, "Something went wrong with key grabs.\n");
                  goto c_end;
               }
             ret = evas_object_key_grab(d.bg, "p", 0, 0, EINA_TRUE);
             if (!ret)
               {
                  fprintf(stdout, "Something went wrong with key grabs.\n");
                  goto c_end;
               }
             ret = evas_object_key_grab(d.bg, "o", mask, 0, EINA_TRUE);
             if (!ret)
               {
                  fprintf(stdout, "Something went wrong with key grabs.\n");
                  goto c_end;
               }
             ret = evas_object_key_grab(d.bg, "h", 0, 0, EINA_TRUE);
             if (!ret)
               {
                  fprintf(stdout, "Something went wrong with key grabs.\n");
                  goto c_end;
               }
          }
        else
          {
             evas_object_key_ungrab(d.bg, "a", 0, 0);
             evas_object_key_ungrab(d.bg, "c", 0, 0);
             evas_object_key_ungrab(d.bg, "d", 0, 0);
             evas_object_key_ungrab(d.bg, "f", 0, 0);
             evas_object_key_ungrab(d.bg, "p", 0, 0);
             evas_object_key_ungrab(d.bg, "o", mask, 0);
             evas_object_key_ungrab(d.bg, "h", 0, 0);

             evas_object_focus_set(d.bg, EINA_TRUE);
          }

c_end:
        d.focus = !d.focus;

        return;
     }

   if (strcmp(ev->key, "d") == 0)
     {
        fprintf(stdout, "Deleting canvas event callbacks\n");
        evas_event_callback_del_full(evas, EVAS_CALLBACK_RENDER_FLUSH_PRE,
                                     _render_flush_cb, NULL);
        evas_event_callback_del_full( evas, EVAS_CALLBACK_CANVAS_OBJECT_FOCUS_IN,
          _object_focus_in_cb, NULL);
        return;
     }

   if (strcmp(ev->key, "f") == 0) 
     {
        fprintf(stdout, "Freezing input for 3 seconds\n");
        evas_event_freeze(evas);
        d.freeze_timer = ecore_timer_add(3, _thaw_cb, NULL);
        return;
     }

   if (strcmp(ev->key, "p") == 0)
     {
        Eina_Bool precise = evas_object_precise_is_inside_get(d.img);

        fprintf(stdout, "Toggling precise point collision detection %s on"
                        " Enlightenment logo\n", precise ? "off" : "on");
        evas_object_precise_is_inside_set(d.img, !precise);

        return;
     }

   mods = evas_key_modifier_get(evas);
   if (evas_key_modifier_is_set(mods, "Control") &&
       (strcmp(ev->key, "o") == 0))
     {
        fprintf(stdout, "Toggling obscured rectangle on canvas\n");
        if (!d.obscured)
          {
             int w, h;
             evas_output_viewport_get(evas, NULL, NULL, &w, &h);
             evas_obscured_rectangle_add(evas, w / 4, h / 4, w / 2, h / 2);
          }
        else
          {
             int w, h;
             Eina_Rectangle *rect;
             Eina_List *updates, *l;

             evas_output_viewport_get(evas, NULL, NULL, &w, &h);
             evas_obscured_clear(evas);

             evas_damage_rectangle_add(evas, 0, 0, w, h);

             updates = evas_render_updates(evas);

             EINA_LIST_FOREACH(updates, l, rect)
               {
                  fprintf(stdout, "Rectangle (%d, %d, %d, %d) on canvas got a"
                                  " rendering update.\n", rect->x, rect->y,
                          rect->w,
                          rect->h);
               }
             evas_render_updates_free(updates);
          }
        d.obscured = !d.obscured;
     }
}

int
main(void)
{
   int err;

   if (!ecore_evas_init())
     return EXIT_FAILURE;

   d.ee = ::ecore_evas_new(NULL, 10, 10, WIDTH, HEIGHT, NULL);
   if (!d.ee)
     goto error;

   ::ecore_evas_callback_resize_set(d.ee, _canvas_resize_cb);
   ::ecore_evas_show(d.ee);

   evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));

   evas_event_callback_add(d.canvas, EVAS_CALLBACK_RENDER_FLUSH_PRE,
                           _render_flush_cb, NULL);
   if (evas_alloc_error() != EVAS_ALLOC_ERROR_NONE)
     {
        fprintf(stderr, "ERROR: Callback registering failed! Aborting.\n");
        goto panic;
     }

   evas_event_callback_add(d.canvas, EVAS_CALLBACK_CANVAS_OBJECT_FOCUS_IN,
                           _object_focus_in_cb, NULL);
   if (evas_alloc_error() != EVAS_ALLOC_ERROR_NONE)
     {
        fprintf(stderr, "ERROR: Callback registering failed! Aborting.\n");
        goto panic;
     } 

   evas::rectangle bg(efl::eo::parent = canvas);
   bg.name_set("our dear rectangle");
   bg.color_set(255, 255, 255, 255);
   bg.position_set(0, 0); 
   bg.evas::object::size_set(WIDTH, HEIGHT); 
   bg.visibility_set(EINA_TRUE);

   bg.focus_set(EINA_TRUE);
   focus = EINA_TRUE;

   evas_object_event_callback_add(
     d.bg, EVAS_CALLBACK_KEY_DOWN, _on_keydown, NULL);
   if (evas_alloc_error() != EVAS_ALLOC_ERROR_NONE)
     {
        fprintf(stderr, "ERROR: Callback registering failed! Aborting.\n");
        goto panic;
     }

   evas::image img(efl::eo::parent = canvas);
   img.image_file_set(img_path, NULL);
   err = evas_object_image_load_error_get(img);
   if (err != EVAS_LOAD_ERROR_NONE)
     {
        goto panic;
     }
   else
     {
       img.position_set(0, 0); 
       img.evas::object::size_set(WIDTH, HEIGHT);
       img.visibility_set(EINA_TRUE);
       evas_object_event_callback_add(img, EVAS_CALLBACK_MOUSE_IN, _on_mouse_in, NULL);
       evas_object_event_callback_add(img, EVAS_CALLBACK_MOUSE_OUT, _on_mouse_out, NULL);
     }

   d.resize_timer = ecore_timer_add(2, _resize_cb, NULL);

   fprintf(stdout, commands);
   ecore_main_loop_begin();

   ecore_evas_free(ee);
   ecore_evas_shutdown();
   return 0;

error:
   fprintf(stderr, "you got to have at least one evas engine built and linked"
                   " up to ecore-evas for this example to run properly.\n");
panic:
   ecore_evas_shutdown();
   return -1;
}
