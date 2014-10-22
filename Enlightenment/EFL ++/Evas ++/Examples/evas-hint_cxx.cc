#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define PACKAGE_EXAMPLES_DIR "/home/luciana/Enlightenment/scr/efl/src/examples/evas"
#endif

#include <Ecore.h>
#include <Ecore_Evas.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Eina.hh>
#include <Evas.hh>
#include <Eo.hh>
#include <Efl.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"
#include "canvas/evas_box.eo.hh"
#include "canvas/evas_image.eo.hh"


#define WIDTH  320
#define HEIGHT 480

static const char commands[] = \
  "commands are:\n"
  "\tShift + a - change alignment hints on top rectangle\n"
  "\tShift + m - change min. size hint on top rectangle\n"
  "\tShift + n - change max. size hint on top rectangle\n"
  "\tShift + p - change padding hints on top rectangle\n"
  "\tShift + w - change weight hints on top rectangle\n\n"
  "\tControl + a - change alignment hints on bottom rectangle\n"
  "\tControl + m - change min. size hint on bottom rectangle\n"
  "\tControl + n - change max. size hint on bottom rectangle\n"
  "\tControl + p - change padding hints on bottom rectangle\n"
  "\tControl + w - change weight hints on bottom rectangle\n\n"
  "\ts - print current hints information\n"
  "\th - print help\n";

static const char *border_img_path = PACKAGE_EXAMPLES_DIR "/red.png";

struct coord_tuple
{
   Evas_Coord w, h;
};

struct weight_tuple
{
   double x, y;
};

struct padding_tuple
{
   Evas_Coord l, r, t, b;
};

struct rect_data
{
   struct coord_tuple   *min_ptr;
   struct coord_tuple    min[4];

   struct coord_tuple   *max_ptr;
   struct coord_tuple    max[4];

   struct weight_tuple  *align_ptr;
   struct weight_tuple   align[3];

   struct weight_tuple  *weight_ptr;
   struct weight_tuple   weight[3];

   struct padding_tuple *padding_ptr;
   struct padding_tuple  padding[3];
};

Ecore_Evas      *ee;
evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));
struct rect_data t_data, b_data;
evas::box box(efl::eo::parent = canvas);
evas::rectangle bg(efl::eo::parent = canvas);
evas::rectangle t_rect(efl::eo::parent = canvas);
evas::rectangle b_rect(efl::eo::parent = canvas);
evas::image border(efl::eo::parent = canvas);


static void
_canvas_resize_cb(Ecore_Evas *ee)
{
   int w, h;

   ::ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
   bg.evas::object::size_set(w, h);

   box.position_set((w / 4), (h / 4));
   box.evas::object::size_set((w / 2), (h / 2));

   border.position_set((w / 4) - 3, (h / 4) - 3);
   border.evas::object::size_set((w / 2) + 6, (h / 2) + 6);

}

static void
_print_rect_stats(evas::rectangle rect)
{
   Evas_Coord w, h, l, r, t, b;
   double x, y;

   rect.size_hint_align_get(&x, &y);
   fprintf(stdout, "\talign hints: h(%f), v(%f)\n", x, y);

   rect.size_hint_min_get(&w, &h);
   fprintf(stdout, "\tmin. size hints: h(%d), v(%d)\n", w, h);

   rect.size_hint_max_get(&w, &h);
   fprintf(stdout, "\tmax. size hints: h(%d), v(%d)\n", w, h);

   rect.size_hint_padding_get( &l, &r, &t, &b);
   fprintf(stdout, "\tpadding hints: l(%d), r(%d), t(%d), b(%d)\n",
           l, r, t, b);

   rect.size_hint_weight_get( &x, &y);
   fprintf(stdout, "\tweight hints: h(%f), v(%f)\n", x, y);
}

static void
_on_keydown(void *data EINA_UNUSED, Evas *evas EINA_UNUSED, Evas_Object *o EINA_UNUSED, Evas_Event_Key_Down *ev)
{
  //Evas_Event_Key_Down *ev = einfo;
  evas::rectangle rect;
   struct rect_data *r_data = NULL;
   const Evas_Modifier *mods;
   const char *name = NULL;

   mods = evas_key_modifier_get(evas);
   if (evas_key_modifier_is_set(mods, "Shift"))
     {
        rect = t_rect;
        r_data = &t_data;
        name = "top";
     }
   else if (evas_key_modifier_is_set(mods, "Control"))
     {
        rect = b_rect;
        r_data = &b_data;
        name = "bottom";
     }
   else if (strcmp(ev->key, "h") == 0)
     {
        fprintf(stdout, commands);
        return;
     }
   else if (strcmp(ev->key, "s") == 0) 
     {
        fprintf(stdout, "Top rectangle:\n");
        _print_rect_stats(t_rect);

        fprintf(stdout, "\nBottom rectangle:\n");
        _print_rect_stats(b_rect);

        return;
     }

   if (!rect) return;

   if (strcmp(ev->key, "a") == 0)
     {
        (r_data->align_ptr)++;

        if ((unsigned int)
            (((unsigned char *)(r_data->align_ptr)) - ((unsigned char *)(r_data->align))) >=
            sizeof(r_data->align))
          r_data->align_ptr = r_data->align;

       rect.size_hint_align_set(r_data->align_ptr->x, r_data->align_ptr->y);

        fprintf(stdout, "Changing align hints for %s rect. to (%f, %f)\n",
                name, r_data->align_ptr->x, r_data->align_ptr->y);
        return;
     }

   if (strcmp(ev->key, "m") == 0)
     {
        (r_data->min_ptr)++;

        if ((unsigned int)
            (((unsigned char *)(r_data->min_ptr)) - ((unsigned char *)(r_data->min))) >=
            sizeof(r_data->min))
          r_data->min_ptr = r_data->min;

        rect.size_hint_min_set(r_data->min_ptr->w, r_data->min_ptr->h);

        fprintf(stdout, "Changing min. size hints for %s rect. to (%d, %d)\n",
                name, r_data->min_ptr->w, r_data->min_ptr->h);
        return;
     }

   if (strcmp(ev->key, "n") == 0)
     {
        (r_data->max_ptr)++;

        if ((unsigned int)
            (((unsigned char *)(r_data->max_ptr)) - ((unsigned char *)(r_data->max))) >=
            sizeof(r_data->max))
          r_data->max_ptr = r_data->max;

       rect.size_hint_max_set(r_data->max_ptr->w, r_data->max_ptr->h);

        fprintf(stdout, "Changing max. size hints for %s rect. to (%d, %d)\n",
                name, r_data->max_ptr->w, r_data->max_ptr->h);
        return;
     }

   if (strcmp(ev->key, "p") == 0)
     {
        (r_data->padding_ptr)++;

        if ((unsigned int)
            (((unsigned char *)(r_data->padding_ptr)) - ((unsigned char *)(r_data->padding))) >=
            sizeof(r_data->padding))
          r_data->padding_ptr = r_data->padding;

	rect.size_hint_padding_set(r_data->padding_ptr->l, r_data->padding_ptr->r,
          r_data->padding_ptr->t, r_data->padding_ptr->b);

        fprintf(stdout, "Changing padding size hints for %s rect."
                        " to (%d, %d, %d, %d)\n",
                name, r_data->padding_ptr->l, r_data->padding_ptr->r,
                r_data->padding_ptr->t, r_data->padding_ptr->b);
        return;
     }

   if (strcmp(ev->key, "w") == 0)
     {
        (r_data->weight_ptr)++;

        if ((unsigned int)
            (((unsigned char *)(r_data->weight_ptr)) - ((unsigned char *)(r_data->weight))) >=
            sizeof(r_data->weight))
          r_data->weight_ptr = r_data->weight;

        rect.size_hint_weight_set(r_data->weight_ptr->x, r_data->weight_ptr->y);

        fprintf(stdout, "Changing weight hints for %s rect. to (%f, %f)\n",
                name, r_data->weight_ptr->x, r_data->weight_ptr->y);
        return;
     }
}

static void
_on_destroy(Ecore_Evas *ee EINA_UNUSED)
{
   ecore_main_loop_quit();
}

int
main(void)
{
  efl::eina::eina_init eina_init;
  efl::eo::eo_init init;
  if (!::ecore_evas_init()) return EXIT_FAILURE;
  if (!::evas_init()) return EXIT_FAILURE;

   struct rect_data init_data = \
   {
      .min = {{0, 0}, {30, 30}, {100, 70}, {200, 200}},
      .max = {{0, 0}, {100, 100}, {100, 70}, {300, 300}},
      .align = {{0.0, 0.0}, {0.5, 0.5}, {1.0, 0.5}},
      .weight = {{0.0, 0.0}, {3, 6}, {10, 100}},
      .padding = {{0, 0, 0, 0}, {3, 6, 9, 12}, {10, 20, 0, 30}}
   };

   t_data = init_data;

   t_data.min_ptr = t_data.min + 1;
   t_data.max_ptr = t_data.max + 1;
   t_data.align_ptr = t_data.align;
   t_data.weight_ptr = t_data.weight;
   t_data.padding_ptr = t_data.padding;

   b_data = init_data;

   b_data.min_ptr = b_data.min + 1;
   b_data.max_ptr = b_data.max + 1;
   b_data.align_ptr = b_data.align;
   b_data.weight_ptr = b_data.weight;
   b_data.padding_ptr = b_data.padding;

   ee = ::ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);
   if (!ee)
     goto error;

   ::ecore_evas_callback_destroy_set(ee, _on_destroy);
   ::ecore_evas_callback_resize_set(ee, _canvas_resize_cb);
   ::ecore_evas_show(ee);

   bg.color_set(255, 255, 255, 255); 
   bg.position_set(0, 0); 
   bg.evas::object::size_set(WIDTH, HEIGHT); 
   bg.visibility_set(EINA_TRUE);

   bg.focus_set(EINA_TRUE);
   evas_object_event_callback_add(bg, EVAS_CALLBACK_KEY_DOWN, _on_keydown, NULL);

   box.layout_set(evas_object_box_layout_vertical, NULL, NULL);
   box.visibility_set(EINA_TRUE);

  border.file_set( border_img_path, NULL);
   border.border_set(3, 3, 3, 3);
   border.border_center_fill_set(EVAS_BORDER_FILL_NONE);
   border.visibility_set(EINA_TRUE);

   t_rect.color_set(0, 0, 255, 255);

   t_rect.size_hint_min_set(t_data.min_ptr->w, t_data.min_ptr->h);
   t_rect.visibility_set(EINA_TRUE);
   box.append(t_rect);

   b_rect.color_set(0, 255, 0, 255);

   b_rect.size_hint_min_set(b_data.min_ptr->w, b_data.min_ptr->h);
   b_rect.visibility_set(EINA_TRUE);
   box.append(b_rect);

   _canvas_resize_cb(ee);

   fprintf(stdout, commands);
   ecore_main_loop_begin();
   ::ecore_evas_shutdown();
   return 0;

error:
   fprintf(stderr, "You got to have at least one evas engine built and linked"
                   " up to ecore-evas for this example to run properly.\n");
   return -1;
}
