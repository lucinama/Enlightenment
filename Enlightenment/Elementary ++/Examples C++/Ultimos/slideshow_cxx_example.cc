#ifdef HAVE_CONFIG_H
# include <elementary_config.h>
#endif

extern "C"
{
#define ELM_INTERNAL_API_ARGESFSDFEFC
#define ELM_INTERFACE_ATSPI_ACCESSIBLE_PROTECTED
#define ELM_INTERFACE_ATSPI_COMPONENT_PROTECTED
#define ELM_INTERFACE_ATSPI_ACTION_PROTECTED
#define ELM_INTERFACE_ATSPI_VALUE_PROTECTED
#define ELM_INTERFACE_ATSPI_EDITABLE_TEXT_PROTECTED
#define ELM_INTERFACE_ATSPI_TEXT_PROTECTED
#define ELM_INTERFACE_ATSPI_SELECTION_PROTECTED
#define ELM_INTERFACE_ATSPI_IMAGE_PROTECTED
#define ELM_INTERFACE_ATSPI_WIDGET_ACTION_PROTECTED

#include <Eo.h>
#include <Evas.h>
#include <Elementary.h>
#include <elm_widget.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_text.h"
#include "elm_interface_scrollable.h"
}

#include <Elementary.hh>
#include <Eina.hh>

#define IMG_NUM 8

static Evas_Object *bt_start, *bt_stop;
static Elm_Slideshow_Item_Class itc;

static void
_notify_show(::elm_slideshow data, Evas_Object *obj, void *event_info)
{
  data.visibility_set(EINA_TRUE);
}

/* jump to next item, cyclically */
static void
_next(::elm_slideshow data, Evas_Object *obj, void *event_info)
{
  data.next();
}

static void
_previous(::elm_slideshow data, Evas_Object *obj, void *event_info)
{
   data.previous();
}

static void
_first(::elm_slideshow data, Evas_Object *obj, void *event_info)
{
   data.item_show();
}

static void
_last(::elm_slideshow data, Evas_Object *obj, void *event_info)
{
   data.item_show();
}

static void
_mouse_in_cb(::elm_notify data, Evas_Object *obj, void *event_info)
{
   data.timeout_set(0.0);
   data.visibility_set(EINA_TRUE);
}

static void
_mouse_out_cb(::elm_notify data, Evas_Object *obj, void *event_info)
{
   data.timeout_set( 3.0);
}

/* transition changed */
static void
_transition_select(void *data, ::elm_slideshow slideshow, void *event_info)
{
  slideshow.transition_set(data);
  elm_object_text_set(obj._eo_ptr(), data);  // XXX
}

static void
_layout_select(void *data, ::elm_slideshow slideshow, void *event_info)
{
   slideshow.layout_set(data);
   elm_object_text_set(obj._eo_ptr(), data);  // XXX
}

/* start the show! */
static void
_start( ::elm_slideshow slideshow, void *event_info)
{
  ::elm_spinner data;
   slideshow.timeout_set(data.value_get());

   bt_start.disabled_set(EINA_TRUE);
   bt_stop.disabled_set(EINA_FALSE);
}

static void
_stop(void *data, ::elm_slideshow slideshow, void *event_info)
{
   slideshow.timeout_set(0.0);
    bt_start.disabled_set(EINA_FALSE);
    bt_stop.disabled_set( EINA_TRUE);
}

/* slideshow transition time has changed */
static void
_spin(void *data, ::elm_slideshow slideshow, void *event_info)
{
  ::elm_spinner data;
   if (slideshow.timeout_get() > 0)
     slideshow.timeout_set(data.value_get());
}

/* get our images to make slideshow items */
static Evas_Object *
_get(void *data, ::elm_photo photo)
{
  photo.file_set(data);
  photo.fill_inside_set(EINA_TRUE);
  photo.style_set("shadow");

  return photo;
}

/* ordering alphabetically */
static int
_cmp_func(const void *data1, const void *data2)
{
   const char *img_path1, *img_path2;

   const Elm_Object_Item *slide_it1 = data1;
   const Elm_Object_Item *slide_it2 = data2;

   img_path1 = slide_it1.item_data_get();
   img_path2 = slide_it2.item_data_get();

   return strcasecmp(img_path1, img_path2);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   Elm_Object_Item *slide_first = NULL, *slide_last = NULL, *slide_it = NULL;
   const char *transition, *layout;
   const Eina_List *l, *list;
   const char *data_dir;
   char img[IMG_NUM][PATH_MAX];
   char *img_files[] =
     {
        "logo.png", "plant_01.jpg", "rock_01.jpg", "rock_02.jpg", "sky_01.jpg",
        "wood_01.jpg", "mystrale.jpg", "mystrale_2.jpg"
     };
   int i = 0;

   elm_app_info_set(elm_main, "elementary", "images");

   data_dir = elm_app_data_dir_get();
   for (i = 0; i < IMG_NUM; i++)
     snprintf(img[i], PATH_MAX, "%s/images/%s", data_dir, img_files[i]);

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   ::elm_win win(elm_win_util_standard_add("slideshow", "Slideshow example"));
   win.autodel_set(true);

   ::elm_slideshow slideshow(efl::eo::parent = win);
   slideshow.loop_set(slideshow, EINA_TRUE);
   slideshow.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   win.resize_object_add(slideshow);
   slideshow.visibility_set(EINA_TRUE);

   itc.func.get = _get;
   itc.func.del = NULL;

   for (i = 0; i < IMG_NUM; i++)
     {
       slide_it = slideshow.item_sorted_insert( &itc, img[i], _cmp_func);
       if (!slide_first) slide_first = slide_it;
     }
   slide_last = slide_it;

   list = slideshow..items_get();
   fprintf(stdout, "List of items in the slideshow:\n");
   EINA_LIST_FOREACH(list, l, slide_it)
     fprintf(stdout, "\t%s\n",
             (const char *)elm_object_item_data_get(slide_it));

   ::elm_notify notify(efl::eo::parent = win);
   notify.align_set(0.5, 1.0);
   notify.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   notify.timeout_set(3.0);
   notify.visibility_set(EINA_TRUE);

   ::elm_box bx(efl::eo::parent = win);
   bx.horizontal_set(EINA_TRUE);
   elm_object_content_set(notify._eo_ptr(), bx._eo_ptr()); // XXX
   bx.visibility_set(EINA_TRUE);

   bx.event_callback_add(EVAS_CALLBACK_MOUSE_IN, _mouse_in_cb, notify);
   bx.event_callback_add(EVAS_CALLBACK_MOUSE_OUT, _mouse_out_cb, notify);

   ::elm_button bt(efl::eo::parent = win);
   elm_object_text_set(bt._eo_ptr(), "First");  // XXX
   bt.callback_clicked_add(&_first);
   bx.pack_end(bt);
   bt.visibility_set(EINA_TRUE);

   ::elm_button bt2(efl::eo::parent = win);
   elm_object_text_set(bt2._eo_ptr(), "Previous"); // XXX
   bt3.callback_clicked_add(&_previous);
   bx.pack_end(bt2);
   bt2.visibility_set(EINA_TRUE);

   ::elm_button bt3(efl::eo::parent = win);
   elm_object_text_set(bt3._eo_ptr(), "Next"); // XXX
   bt3.callback_clicked_add(&_next);
   bx.pack_end(bt3);
   bt3.visibility_set(EINA_TRUE);

   ::elm_button bt4(efl::eo::parent = win);
   elm_object_text_set(bt4._eo_ptr(), "Last");  // XXX
   bt4.callback_clicked_add(&_last);
   bx.pack_end(bt4);
   bt4.visibility_set(EINA_TRUE);

   ::elm_hoversel hv(efl::eo::parent = win);
   bx.pack_end(hv);
   EINA_LIST_FOREACH(slideshow.transitions_get(), l, transition)
     hv.item_add(transition, NULL, 0, _transition_select, transition);
   elm_object_text_set(hv._eo_ptr(), eina_list_data_get(slideshow.transitions_get())); // XXX
   hv.visibility_set(EINA_TRUE);

   ::elm_hoversel hv2(efl::eo::parent = win);
   bx.pack_end(hv2);
   EINA_LIST_FOREACH(slideshow.layouts_get(), l, layout)
     hv.item_add(layout, NULL, 0, _layout_select, layout);
   elm_object_text_set(hv._eo_ptr(), elm_slideshow_layout_get(slideshow));  // XXX
   hv2.visibility_set(EINA_TRUE);

   ::elm_spinner spin(efl::eo::parent = win);
   spin.label_format_set("%2.0f s");
   spin.callback_changed_add(&_spin);
   spin.step_set(1);
   spin.min_max_set(1, 30);
   spin.value_set(3);
   bx.pack_end(spin);
   spin.visibility_set(EINA_TRUE);

   ::elm_button bt(efl::eo::parent = win);
   bt_start = bt;
   elm_object_text_set(bt._eo_ptr(), "Start");  // XXX
   bt.callback_clicked_add(&_start);
   bx.pack_end(bt);
   bt.visibility_set(EINA_TRUE);

   ::elm_button bt2(efl::eo::parent = win);
   bt_stop = bt2;
   elm_object_text_set(bt2._eo_ptr(), "Stop"); // XXX
   bt2.callback_clicked_add(&_stop);
   bx.pack_end(bt2);
   bt2.disabled_set(EINA_TRUE);
   bt2.visibility_set(EINA_TRUE);

   slideshow.event_callback_add(EVAS_CALLBACK_MOUSE_UP, _notify_show, notify);
   slideshow.event_callback_add(EVAS_CALLBACK_MOUSE_MOVE, _notify_show, notify);

   win.evas::object::size_set(600, 400);
   win.visibility_set(EINA_TRUE);

   elm_run();
   elm_shutdown();

   return 0;
 }
 ELM_MAIN()
