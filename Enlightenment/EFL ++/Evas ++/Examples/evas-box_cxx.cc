#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <Ecore.h>
#include <Ecore_Evas.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WIDTH  (640)
#define HEIGHT (480)

#include <Evas.hh>
#include <Eina.hh>
#include <Eo.hh>
#include <Efl.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"
#include "canvas/evas_box.eo.hh"

static const char *border_img_path = PACKAGE_EXAMPLES_DIR "/red.png";

static const char *commands = \
  "commands are:\n"
  "\ta - change the box's alignment values\n"
  "\tp - change the box's padding values\n"
  "\t1 - change the box's layout to horizontal\n"
  "\t2 - change the box's layout to vertical\n"
  "\t3 - change the box's layout to horizontal homogeneous\n"
  "\t4 - change the box's layout to vertical homogeneous\n"
  "\t5 - change the box's layout to horizontal maximum size homogeneous\n"
  "\t6 - change the box's layout to vertical maximum size homogeneous\n"
  "\t7 - change the box's layout to horizontal flow\n"
  "\t8 - change the box's layout to vertical flow\n"
  "\t9 - change the box's layout to stack\n"
  "\t0 - change the box's layout to a custom-made one\n"
  "\tCtrl + NUMBER - insert a new child object at that position in the box\n"
  "\tShift + NUMBER - remove the child object at that position in the box\n"
  "\th - print help\n";

Ecore_Evas  *ee;
evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));
evas::rectangle bg(efl::eo::parent = canvas);
evas::box box(efl::eo::parent = canvas);
evas::image border(efl::eo::parent = canvas);

static void
_custom_layout(Evas_Object *o, Evas_Object_Box_Data *p, void *data EINA_UNUSED)
{
   int x, y, w, h;
   int xx, yy, ww, hh;
   int count;
   Eina_List *l;
   Evas_Object_Box_Option *opt;

   o.geometry_get(&x, &y, &w, &h);
   count = eina_list_count(p->children);
   ww = w / (count ? : 1);
   hh = h / (count ? : 1);
   if (ww < 1) ww = 1;
   if (hh < 1) hh = 1;

   xx = x;
   yy = y;
   EINA_LIST_FOREACH(p->children, l, opt)
     {
        evas_object_move(opt->obj, xx, yy);
        xx += ww;
        yy += hh;
     }
}

static Evas_Object * 
_new_rectangle_add(Evas *e)
{
   evas::rectangle o(efl::eo::parent = e);
   o.evas::object::size_set(10, 10);
   o.color_set(0, 255, 0, 255);
   o.visibility_set(true);

   return o;
}

static void
_on_keydown(void *data EINA_UNUSED, Evas *evas EINA_UNUSED, Evas_Object *o EINA_UNUSED, void *einfo)
{
   Evas_Event_Key_Down *ev = einfo;
   const Evas_Modifier *mods = evas_key_modifier_get(evas);

   if (strcmp(ev->key, "h") == 0)
     {
        fprintf(stdout, "%s",  commands);
        return;
     }

   if (evas_key_modifier_is_set(mods, "Shift"))
     {
        int pos;
        Eina_Bool ret;
        Evas_Object *obj;
        Eina_List *children;

        pos = atoi(ev->key);
        children = box.children_get();

        obj = eina_list_nth(children, pos);
        if (!obj) goto list_free;

        ret = box.remove_at(pos);
        if (ret) evas_object_del(obj);

list_free:
        eina_list_free(children);
        return;
     }

   if (evas_key_modifier_is_set(mods, "Control"))
     {
        Evas_Object *o_;
        int pos;
        pos = atoi(ev->key);
        o_ = _new_rectangle_add(canvas);
        if (!box.insert_at(o_, pos))
          box.append(o_);
        return;
     }

   if (strcmp(ev->key, "a") == 0)
     {
        double h, v;

        box.align_get(&h, &v);

        if (h == 0.5)
          h = v = 1.0;
        else if (h == 1.0)
          h = v = -1.0;
        else if (h == -1.0)
          h = v = 0.0;
        else if (h == 0.0)
          h = v = 0.5;

        box.align_set(h, v);

        fprintf(stdout, "Applying new alignment values (%.1f, %.1f)"
                        " on the box\n", h, v);
        return;
     }

   if (strcmp(ev->key, "p") == 0)
     {
        int h, v;

	box.padding_get(&h, &v);

        if (h == 0)
          h = v = 50;
        else
          h = v = 0;

        box.adding_set(h, v);

        fprintf(stdout, "Applying new padding values (%d, %d)"
                        " on the box\n", h, v);
        return;
     }

   if (strcmp(ev->key, "1") == 0)
     {
        box.layout_set(evas_object_box_layout_horizontal, NULL, NULL);

        fprintf(stdout, "Applying '%s' layout on the box\n", "horizontal");
        return;
     }

   if (strcmp(ev->key, "2") == 0)
     {
        box.layout_set(evas_object_box_layout_vertical, NULL, NULL);

        fprintf(stdout, "Applying '%s' layout on the box\n", "vertical");
        return;
     }

   if (strcmp(ev->key, "3") == 0)
     {
        box.layout_set(evas_object_box_layout_homogeneous_horizontal, NULL, NULL);

        fprintf(stdout, "Applying '%s' layout on the box\n",
                "horizontal homogeneous");
        return;
     }

   if (strcmp(ev->key, "4") == 0)
     {
        box.layout_set(evas_object_box_layout_homogeneous_vertical, NULL, NULL);

        fprintf(stdout, "Applying '%s' layout on the box\n",
                "vertical homogeneous");
        return;
     }

   if (strcmp(ev->key, "5") == 0)
     {
        box.layout_set(evas_object_box_layout_homogeneous_max_size_horizontal,NULL, NULL);

        fprintf(stdout, "Applying '%s' layout on the box\n",
                "horizontal maximum size homogeneous");
        return;
     }

   if (strcmp(ev->key, "6") == 0)
     {
        box.layout_set(evas_object_box_layout_homogeneous_max_size_vertical,NULL, NULL);

        fprintf(stdout, "Applying '%s' layout on the box\n",
                "vertical maximum size homogeneous");
        return;
     }

   if (strcmp(ev->key, "7") == 0)
     {
        box.layout_set(evas_object_box_layout_flow_horizontal, NULL, NULL);

        fprintf(stdout, "Applying '%s' layout on the box\n", "horizontal flow");
        return;
     }

   if (strcmp(ev->key, "8") == 0)
     {
       box.layout_set(evas_object_box_layout_flow_vertical, NULL, NULL);

        fprintf(stdout, "Applying '%s' layout on the box\n", "vertical flow");
        return;
     }

   if (strcmp(ev->key, "9") == 0)
     {
        box.layout_set(evas_object_box_layout_stack, NULL, NULL);

        fprintf(stdout, "Applying '%s' layout on the box\n", "stack");
        return;
     }

   if (strcmp(ev->key, "0") == 0)
     {
       box.layout_set(_custom_layout, NULL, NULL);

        fprintf(stdout, "Applying '%s' layout on the box\n", "CUSTOM");
        return;
     }
}

static void
_on_delete(Ecore_Evas *ee EINA_UNUSED)
{
   ecore_main_loop_quit();
}

static void
_canvas_resize_cb(Ecore_Evas *ee)
{
   int w, h;

   ::ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);

   bg.evas::object::size_set(w, h);

   box.position_set((w / 4), (h / 4));
   box.evas::object::size_set((w / 2), (h / 2));

   border.position_set((w / 4) - 2, (h / 4) - 2);
   border.evas::object::size_set((w / 2) + 4, (h / 2) + 4);
}

int
main(void)
{
   int i;

   srand(time(NULL));

  efl::eina::eina_init eina_init;
  efl::eo::eo_init init;
  if (!::ecore_evas_init()) return EXIT_FAILURE;
  if (!::evas_init()) return EXIT_FAILURE;

   ee = ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);
   if (!d.ee)
     goto panic;

   ::ecore_evas_callback_delete_request_set(d.ee, _on_delete);
   ::ecore_evas_callback_resize_set(d.ee, _canvas_resize_cb);
   ::ecore_evas_show(d.ee);

   bg.color_set(255, 255, 255, 255);
   bg.visibility_set(EINA_TRUE);
   bg.focus_set(EINA_TRUE);
   bg.event_callback_add(EVAS_CALLBACK_KEY_DOWN, _on_keydown, NULL);

   box.visibility_set(EINA_TRUE);

   for (i = 1; i <= 5; i++)
     {
       evas::rectangle o(efl::eo::parent = canvas);
       evas::rectangle last(efl::eo::parent = canvas);
       o.size_hint_min_set(50, 50);
       o.color_set(rand() % 256, rand() % 256, rand() % 256, 255);
       o.visibility_set(EINA_TRUE);

        if (!box.append(o))
          {
             fprintf(stderr, "Error appending child object on the box!\n");
             goto error;
          }
     }

   border.file_set(border_img_path, NULL);
   border.border_set(2, 2, 2, 2);
   border.border_center_fill_set(EVAS_BORDER_FILL_NONE);
   border.visibility_set(EINA_TRUE);

   fprintf(stdout, "%s", commands);

   _canvas_resize_cb(ee);
   ::ecore_main_loop_begin();
   ::ecore_evas_shutdown();
   return 0;

 error:
   ::ecore_evas_shutdown();
   return -1;

 panic:
   fprintf(stderr, "You got to have at least one evas engine built and linked"
	   " up to ecore-evas for this example to run properly.\n");
   return -2;
}

