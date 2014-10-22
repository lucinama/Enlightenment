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

static int counter = 3;

static void
_prepend_cb(void *data, ::elm_button obj, void *event_info)
{
   Elm_Object_Item *list_it;
   Evas_Object *li = data;
   char label[32];

   snprintf(label, sizeof(label), "Item %i", counter++);
   list_it = elm_list_item_prepend(li, label, NULL, NULL, NULL, NULL);
   elm_list_go(li);
   if (!list_it)
     printf("Error adding item\n");
}

static void
_add_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *list_it;
   Evas_Object *li = data;
   char label[32];

   snprintf(label, sizeof(label), "Item %i", counter++);
   list_it = elm_list_item_append(li, label, NULL, NULL, NULL, NULL);
   elm_list_go(li);
   if (!list_it)
     printf("Error adding item\n");
}

static void
_add_ic_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *list_it;
   Evas_Object *ic, *li = data;
   char label[32];

   snprintf(label, sizeof(label), "Item %i", counter++);
   ic = elm_icon_add(li);
   elm_icon_standard_set(ic, "home");
   elm_image_resizable_set(ic, EINA_FALSE, EINA_FALSE);

   list_it = elm_list_item_append(li, label, ic,  NULL, NULL, NULL);
   elm_list_go(li);
   if (!list_it)
     printf("Error adding item with icon\n");
}

static void
_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *list_it = event_info;
   printf("Selected label: %s\n", elm_object_item_text_get(list_it));
}

static void
_add_func_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *list_it;
   Evas_Object *li = data;
   char label[32];

   snprintf(label, sizeof(label), "Item %i", counter++);
   list_it = elm_list_item_append(li, label, NULL, NULL, _sel_cb, NULL);
   elm_list_go(li);
   if (!list_it)
     printf("Error adding item\n");
}

static void
_sel_data_cb(void *data, Evas_Object *obj, void *event_info)
{
   char *content = data;
   Elm_Object_Item *list_it = event_info;
   printf("Selected label: %s with data: %s\n",
          elm_object_item_text_get(list_it), content);
}

static void
_free_data(void *data, Evas_Object *obj, void *event_info)
{
   free(data);
}

static void
_add_data_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *list_it;
   Evas_Object *li = data;
   char label[32];
   char *content = malloc(sizeof(char) * 32);

   snprintf(content, 32, "Item content %i", counter);
   snprintf(label, sizeof(label), "Item %i", counter++);
   list_it = elm_list_item_append(li, label, NULL, NULL, _sel_data_cb, content);
   elm_list_go(li);
   if (!list_it)
     {
        printf("Error adding item\n");
        return;
     }
   elm_object_item_del_cb_set(list_it, _free_data);
}

static void
_del_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *selected_item;
   Evas_Object *li = data;

   selected_item = elm_list_selected_item_get(li);
   elm_object_item_del(selected_item);
   elm_list_go(li);
}

static void
_unselect_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *selected_item;
   Evas_Object *li = data;

   selected_item = elm_list_selected_item_get(li);
   elm_list_item_selected_set(selected_item, EINA_FALSE);
}

static void
_print_cb(void *data, Evas_Object *obj, void *event_info)
{
   const Eina_List *l, *items;
   Elm_Object_Item *list_it;
   Evas_Object *li = data;

   items = elm_list_items_get(li);
   EINA_LIST_FOREACH(items, l, list_it)
     printf("%s\n", elm_object_item_text_get(list_it));
}

static void
_clear_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *li = data;
   elm_list_clear(li);
}

static void
_select_next_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *selected_item, *next_item;
   Evas_Object *li = data;

   selected_item = elm_list_selected_item_get(li);
   if (!selected_item) return;

   next_item = elm_list_item_next(selected_item);
   if (next_item)
     elm_list_item_selected_set(next_item, EINA_TRUE);
}

static void
_insert_after_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *selected_item, *list_it;
   Evas_Object *li = data;
   char label[32];

   selected_item = elm_list_selected_item_get(li);
   if (!selected_item) return;

   snprintf(label, sizeof(label), "Item %i", counter++);
   list_it = elm_list_item_insert_after(li, selected_item, label, NULL, NULL,
                                        NULL, NULL);
   elm_list_go(li);
   if (!list_it)
     printf("Error adding item\n");
}

static void
_select_prev_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *selected_item, *prev_item;
   Evas_Object *li = data;

   selected_item = elm_list_selected_item_get(li);
   if (!selected_item) return;

   prev_item = elm_list_item_prev(selected_item);
   if (prev_item)
     elm_list_item_selected_set(prev_item, EINA_TRUE);
}

static void
_insert_before_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *selected_item, *list_it;
   Evas_Object *li = data;
   char label[32];

   selected_item = elm_list_selected_item_get(li);
   if (!selected_item) return;

   snprintf(label, sizeof(label), "Item %i", counter++);
   list_it = elm_list_item_insert_before(li, selected_item, label, NULL, NULL,
                                         NULL, NULL);
   elm_list_go(li);
   if (!list_it)
     printf("Error adding item\n");
}

static void
_set_separator_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *selected_item;
   Evas_Object *li = data;

   selected_item = elm_list_selected_item_get(li);
   if (!selected_item) return;
   elm_list_item_separator_set(selected_item, EINA_TRUE);
   elm_list_go(li);
}

static void
_disable_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *selected_item;
   Evas_Object *li = data;

   selected_item = elm_list_selected_item_get(li);
   if (!selected_item) return;
   elm_object_item_disabled_set(selected_item, EINA_TRUE);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	::elm_win win(elm_win_util_standard_add("list", "List Items Example"));
  	win.autodel_set(true);

 	::elm_box bx(efl::eo::parent = win);
	bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(bx);
   	bx.visibility_set(true);

 	::elm_list li(efl::eo::parent = win);
	li.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	li.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
	bx.pack_end(li);

   elm_list_item_append(li, "Item 0", NULL, NULL, NULL, NULL);  // XXX
   elm_list_item_append(li, "Item 1", NULL, NULL, NULL, NULL);  // XXX
   elm_list_item_append(li, "Item 2", NULL, NULL, NULL, NULL);  // XXX

 	::elm_box hbx(efl::eo::parent = win);
	hbx.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	hbx.size_hint_align_set(EVAS_HINT_FILL, 0);
	bx.pack_end(hbx);
   	hbx.visibility_set(true);

 	::elm_button bt(efl::eo::parent = win);
 	elm_object_text_set(bt._eo_ptr(), "Prepend item"); // XXX
 	bt.callback_clicked_add(&_prepend_cb);
 	hbx.pack_end(bt);
	bt.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt.visibility_set(true);
 	
	 ::elm_button bt2(efl::eo::parent = win);
 	elm_object_text_set(bt2._eo_ptr(), "Append item"); // XXX
 	bt2.callback_clicked_add(&_add_cb);
 	hbx.pack_end(bt2);
	bt2.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt2.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt2.visibility_set(true);

	::elm_box hbx2(efl::eo::parent = win);
	hbx2.horizontal_set(true);
	hbx2.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	hbx2.size_hint_align_set(EVAS_HINT_FILL, 0);
	bx.pack_end(hbx2);
   	hbx2.visibility_set(true);

	 ::elm_button bt3(efl::eo::parent = win);
 	elm_object_text_set(bt3._eo_ptr(), "Append with icon"); // XXX
 	bt3.callback_clicked_add(&_add_ic_cb);
 	hbx2.pack_end(bt3);
	bt3.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt3.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt3.visibility_set(true);

	 ::elm_button bt4(efl::eo::parent = win);
 	elm_object_text_set(bt4._eo_ptr(),"Append with selected function"); // XXX
 	bt4.callback_clicked_add(&_add_func_cb);
 	hbx2.pack_end(bt4);
	bt4.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt4.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt4.visibility_set(true);

	 ::elm_button bt5(efl::eo::parent = win);
 	elm_object_text_set(bt5._eo_ptr(),"Append with data"); // XXX
 	bt5.callback_clicked_add(&_add_data_cb);
 	hbx2.pack_end(bt5);
	bt5.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt5.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt5.visibility_set(true);

	::elm_box hbx3(efl::eo::parent = win);
	hbx3.horizontal_set(true);
	hbx3.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	hbx3.size_hint_align_set(EVAS_HINT_FILL, 0);
	bx.pack_end(hbx3);
	bt5.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
   	bt5.size_hint_align_set(EVAS_HINT_FILL, 0);
   	hbx3.visibility_set(true);

	 ::elm_button bt6(efl::eo::parent = win);
 	elm_object_text_set(bt6._eo_ptr(), "Delete item"); // XXX
 	bt6.callback_clicked_add(&_del_cb);
 	hbx3.pack_end(bt6);
	bt6.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt6.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt6.visibility_set(true);

	 ::elm_button bt7(efl::eo::parent = win);
 	elm_object_text_set(bt7._eo_ptr(), "Unselect item"); // XXX
 	bt7.callback_clicked_add(&_unselect_cb);
 	hbx3.pack_end(bt7);
	bt7.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt7.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt7.visibility_set(true);

	 ::elm_button bt8(efl::eo::parent = win);
 	elm_object_text_set(bt8._eo_ptr(), "Print items"); // XXX
 	bt8.callback_clicked_add(&_print_cb);
 	hbx3.pack_end(bt8);
	bt8.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt8.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt8.visibility_set(true);

	 ::elm_button bt9(efl::eo::parent = win);
 	elm_object_text_set(bt9._eo_ptr(), "Clear"); // XXX
 	bt9.callback_clicked_add(&_clear_cb);
 	hbx3.pack_end(bt9);
	bt9.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt9.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt9.visibility_set(true);

	::elm_box hbx4(efl::eo::parent = win);
	hbx4.horizontal_set(true);
	hbx4.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	hbx4.size_hint_align_set(EVAS_HINT_FILL, 0);
	bx.pack_end(hbx4);
	bt9.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
   	bt9.size_hint_align_set(EVAS_HINT_FILL, 0);
   	hbx4.visibility_set(true);

	 ::elm_button bt10(efl::eo::parent = win);
 	elm_object_text_set(bt10._eo_ptr(),"Select next item"); // XXX
 	bt10.callback_clicked_add(&_select_next_cb);
 	hbx4.pack_end(bt10);
	bt10.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt10.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt10.visibility_set(true);

	 ::elm_button bt11(efl::eo::parent = win);
 	elm_object_text_set(bt11._eo_ptr(), "Insert after item"); // XXX
 	bt11.callback_clicked_add(&_insert_after_cb);
 	hbx4.pack_end(bt11);
	bt11.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt11.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt11.visibility_set(true);

	 ::elm_button bt12(efl::eo::parent = win);
 	elm_object_text_set(bt12._eo_ptr(), "Select previous item"); // XXX
 	bt12.callback_clicked_add(&_select_prev_cb);
 	hbx4.pack_end(bt12);
	bt12.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt12.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt12.visibility_set(true);

	 ::elm_button bt13(efl::eo::parent = win);
 	elm_object_text_set(bt13._eo_ptr(), "Insert before item"); // XXX
 	bt13.callback_clicked_add(&_insert_before_cb);
 	hbx4.pack_end(bt13);
	bt13.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt13.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt13.visibility_set(true);

	::elm_box hbx5(efl::eo::parent = win);
	hbx5.horizontal_set(true);
	hbx5.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	hbx5.size_hint_align_set(EVAS_HINT_FILL, 0);
	bx.pack_end(hbx5);
   	hbx5.visibility_set(true);

	 ::elm_button bt14(efl::eo::parent = win);
 	elm_object_text_set(bt14._eo_ptr(), "Set as separator"); // XXX
 	bt14.callback_clicked_add(&_set_separator_cb);
 	hbx5.pack_end(bt14);
	bt14.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt14.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt14.visibility_set(true);

	 ::elm_button bt15(efl::eo::parent = win);
 	elm_object_text_set(bt15._eo_ptr(), "Disable item"); // XXX
 	bt15.callback_clicked_add(&_disable_cb);
 	hbx5.pack_end(bt15);
	bt15.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
	bt15.size_hint_align_set(EVAS_HINT_FILL, 0);
   	bt15.visibility_set(true);

   li.go();
   li.visibility_set(true);

   win.evas::object::size_set(320, 600);
   win.visibility_set(true);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
