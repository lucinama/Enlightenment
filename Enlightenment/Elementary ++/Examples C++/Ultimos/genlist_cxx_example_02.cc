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
#include <pthread.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_text.h"
#include "elm_interface_scrollable.h"
}

#include <Elementary.hh>
#include <Eina.hh>

#include <iostream>

#include <time.h>

#define N_ITEMS 300

static Elm_Genlist_Item_Class *_itc = NULL;

static char *
_item_label_get(void *data, Evas_Object *obj, const char *part)
{
   time_t t = (time_t)ecore_time_unix_get();
   char buf[256];
   int i = (int)(long)data;
   if (i % 2)
     {
        int n;
        snprintf(buf, sizeof(buf), "Very Long Item # %i - realized at %s", i, ctime(&t));
        n = strlen(buf);
        buf[n - 1] = '\0';
     }
   else
     snprintf(buf, sizeof(buf), "short item # %i", i);
   return strdup(buf);
}

static Evas_Object *
_item_content_get(::elm_icon ic, const char *part)
{
   if (!strcmp(part, "icon"))
     elm_icon_standard_set(ic, "clock");

   ic.size_hint_aspect_set(EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   return ic;
}

static void
_item_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
   printf("sel item data [%p] on genlist obj [%p], item pointer [%p]\n",
          data, obj, event_info);
}

static void
_show_status_cb(void *data, Evas_Object *o, void *event_info)
{
   Evas_Object *list = data;
   Evas_Coord x, y, w, h, mx, my;
   Elm_Object_Item *glit = elm_genlist_selected_item_get(list);

   const Eina_List *selected, *l, *realized;
   printf("\nfirst selected item: %p\n", glit);

   selected = elm_genlist_selected_items_get(list);
   printf("all selected items (%d): ", eina_list_count(selected));
   EINA_LIST_FOREACH(selected, l, glit)
     printf("%p ", glit);
   printf("\n");

   realized = elm_genlist_realized_items_get(list);
   printf("realized items (%d): ", eina_list_count(realized));
   EINA_LIST_FOREACH(realized, l, glit)
     printf("%p  ", glit);
   printf("\n");
   printf("genlist mode: %d\n", elm_genlist_decorate_mode_get(list));
   printf("mode item: %p\n", elm_genlist_decorated_item_get(list));

   evas_object_geometry_get(list, &x, &y, &w, &h);
   mx = w / 2 + x;
   my = h / 2 + y;
   glit = elm_genlist_at_xy_item_get(list, mx, my, NULL);
   printf("item in the middle of the screen: %p\n", glit);
}

static void
_realize_cb(void *data, Evas_Object *o, void *event_info)
{
   Evas_Object *list = data;
   elm_genlist_realized_items_update(list);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   int i;

	::elm_win win(elm_win_util_standard_add("genlist", "Genlist - simple"));
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
	win.autodel_set(true);

	::elm_box box(efl::eo::parent = win);
	box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(box);
   	box.visibility_set(true);

	::elm_genlist list(efl::eo::parent = win);

   if (!_itc)
     {
        _itc = elm_genlist_item_class_new();
        _itc->item_style = "default";
        _itc->func.text_get = _item_label_get;
        _itc->func.content_get = _item_content_get;
        _itc->func.state_get = NULL;
        _itc->func.del = NULL;
     }

   Eina_Bool hbounce, vbounce, always, no_sel;
   Elm_Scroller_Policy hp, vp;
   Elm_Object_Select_Mode sel_mode;

   always = no_sel = EINA_FALSE;
   sel_mode = list.select_mode_get();
   if (sel_mode == ELM_OBJECT_SELECT_MODE_ALWAYS)
     always = EINA_TRUE;
   else if (sel_mode == ELM_OBJECT_SELECT_MODE_NONE)
     no_sel = EINA_TRUE;

   std::cout << "default values:" << std::endl;
   std::cout <<  "always select: " << always << std::endl;
   list.bounce_get(&hbounce, &vbounce);
   std::cout << "bounce - horizontal: " << hbounce << ", vertical: " << vbounce << std::endl;
   std::cout << "homogeneous: " <<  list.homogeneous_get() << std::endl;
   std::cout << "horizontal mode: " << list.mode_get() << std::endl;
   std::cout << "longpress timeout: " << list.longpress_timeout_get() << std::endl;
    std::cout << "multi selection: " << list.multi_select_get() << std::endl;
   std::cout << "no selection mode: " << no_sel << std::endl;
   list.policy_get(&hp, &vp);
  	std::cout << "scroller policy - horizontal: " << hp << ", vertical: " << vp << std::endl;
   std::cout << "block count: " << list.block_count_get() << std::endl;

   list.bounce_allow_set(EINA_FALSE, EINA_FALSE);
   list.homogeneous_set(EINA_FALSE);
   list.mode_set(ELM_LIST_LIMIT);
   list.multi_select_set(EINA_TRUE);
   list.select_mode_set(ELM_OBJECT_SELECT_MODE_DEFAULT);
   list.policy_set(ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_ON);
   list.longpress_timeout_set(0.5);
   list.block_count_set(16);

   for (i = 0; i < N_ITEMS; i++)
     {
        list.item_append(_itc,(void *)(long)i, NULL,ELM_GENLIST_ITEM_NONE, _item_sel_cb, NULL); // XXX
     }

   list.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   list.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   box.pack_end(list);
  	list.visibility_set(true);

	::elm_box hbox(efl::eo::parent = win);
	hbox.horizontal_set(true);
	hbox.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	hbox.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   	box.pack_end(hbox);
   	hbox.visibility_set(true);

 	::elm_button btn(efl::eo::parent = win);
 	elm_object_text_set(btn._eo_ptr(), "Show status"); // XXX
	btn.size_hint_weight_set( 0, 0);
	btn.size_hint_align_set(0.5, 0.5);
	 btn.callback_clicked_add(&_show_status_cb);
	hbox.pack_end(btn);
   	btn.visibility_set(true);

 	::elm_button btn2(efl::eo::parent = win);
 	elm_object_text_set(btn2._eo_ptr(), "Realize"); // XXX
	btn2.size_hint_weight_set( 0, 0);
	btn2.size_hint_align_set(0.5, 0.5);
	 btn2.callback_clicked_add(&_realize_cb);
	hbox.pack_end(btn2);
   	btn2.visibility_set(true);

   win.evas::object::size_set(200, 320);
   win.visibility_set(true);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
