#include <iostream>

#ifdef HAVE_CONFIG_H
# include <elementary_config.h>
#endif

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

extern "C"
{
#include <Eo.h>
#include <Evas.h>
#include <Elementary.h>
#include <elm_widget.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_scrollable.h"
}

#include <elm_win.eo.hh>
#include <elm_box.eo.hh>
#include <elm_icon.eo.hh>
#include <elm_diskselector.eo.hh>
#include <elm_button.eo.hh>

#include <Eina.hh>
#include <iostream>

static int counter = 3;

void
_ds_selected_cb(::elm_diskselector obj, Eo_Event_Description const& desc, void* info)
{
//printf("Selected Item %s\n", elm_object_item_text_get(it));
std::cout << "Selected Item " << it.text_get() << std::endl;
    }

void
_add_cb(void *data, ::elm_diskselector ds, Eo_Event_Description const& desc, void* info)
{
  Elm_Object_Item *ds_it;
  char label[32];
  snprintf(label, sizeof(label), "Item %i", counter++);
  ::elm_diskselector ds_it(ds.item_append(label, NULL, NULL, NULL));
  if (!ds_it) std::cout << "Error adding item" << std::endl;
}

void
_add_ic_cb(void *data, Evas_Object *obj, void *event_info)
{

  Elm_Object_Item *ds_it;
  Evas_Object *ic, *ds = data;
  char label[32];

 snprintf(label, sizeof(label), "Item %i", counter++);
 ::elm_icon ic(efl::eo::parent = ds);
 ic.standard_set("home");

 //ds_it = elm_diskselector_item_append(ds, label, NULL, NULL, NULL);
 ::elm_diskselector ds_it(ds.item_append(label, NULL, NULL, NULL));
 if (!ds_it) std::cout << "Error adding item with icon" << std::endl;
}

void
_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
  Elm_Object_Item *ds_it = event_info;
  std::cout << "Selected label: " << ds_it.text_get() << std::endl;
}

static void
_add_func_cb(void *data, Evas_Object *obj, void *event_info)
{
  Elm_Object_Item *ds_it;
  Evas_Object *ds = data;
  char label[32];

  snprintf(label, sizeof(label), "Item %i", counter++);
  //   ds_it = elm_diskselector_item_append(ds, label, NULL, _sel_cb, NULL);
  ::elm_diskselector ds_it(ds.item_append(label, NULL, _sel_cb, NULL));
  if (!ds_it) std::cout << "Error adding item" << std::endl;
}

void
_sel_data_cb(void *data, Evas_Object *obj, void *event_info)
{
  char *content = data;
  Elm_Object_Item *ds_it = event_info;
  std::cout << "Selected label: " << ds_it.text_get() << "with data: " << content << std::endl;
}

void
_free_data(void *data, Evas_Object *obj, void *event_info)
{
  free(data);
}

void
_add_data_cb(void *data, Evas_Object *obj, void *event_info)
{
  Elm_Object_Item *ds_it;
  Evas_Object *ds = data;
  char label[32];
  char *content = malloc(sizeof(char) * 32);

  snprintf(content, 32, "Item content %i", counter);
  snprintf(label, sizeof(label), "Item %i", counter++);
  ::elm_diskselector ds_it(ds.item_append(label, NULL, _sel_data_cb, content));
  //   ds_it = elm_diskselector_item_append(ds, label, NULL, _sel_data_cb, content);
  if (!ds_it)
    {
     std::cout << "Error adding item" << std::endl;
     return;
   }
 ds_it.del_cb_set(_free_data);
}

void
_del_cb(void *data, Evas_Object *obj, void *event_info)
{
  Elm_Object_Item *selected_ds_it;
  Evas_Object *ds = data;

  // selected_ds_it = elm_diskselector_selected_item_get(ds);
  selected_ds_it = ds.selected_item_get();
  selected_ds_it.del();
}

static void
_unselect_cb(void *data, Evas_Object *obj, void *event_info)
{
  Elm_Object_Item *selected_ds_it;
  Evas_Object *ds = data;

  // selected_ds_it = elm_diskselector_selected_item_get(ds);
  selected_ds_it = ds.selected_item_get();
  selected_ds_it.item_selected_set(false);
}

void
_print_cb(void *data, Evas_Object *obj, void *event_info)
{
  const Eina_List *l, *items;
  Elm_Object_Item *ds_it;
  Evas_Object *ds = data;

  items = elm_diskselector_items_get(ds);
  items = ds.items_get();
  EINA_LIST_FOREACH(items, l, ds_it)
    std::cout << ds_it.text_get() << std::endl;
}

void
_clear_cb(void *data, Evas_Object *obj, void *event_info)
{
  Evas_Object *ds = data;
  ds.clear();
}

void
_select_first_cb(void *data, Evas_Object *obj, void *event_info)
{
  Elm_Object_Item *first_ds_it;
  Evas_Object *ds = data;

  first_ds_it = ds.first_item_get();
  if (first_ds_it)
    first_ds_it.item_selected_set(true);
}

void
_select_last_cb(void *data, Evas_Object *obj, void *event_info)
{
  Elm_Object_Item *last_ds_it;
  Evas_Object *ds = data;

  last_ds_it = ds.last_item_get();
  if (last_ds_it)
    last_ds_it.item_selected_set(true);
}

void
_select_next_cb(void *data, Evas_Object *obj, void *event_info)
{
  Elm_Object_Item *selected_ds_it, *next_ds_it;
  Evas_Object *ds = data;

  selected_ds_it = ds.selected_item_get();
  if (!selected_ds_it) return;

  next_ds_it = selected_ds_it.item_next_get();
  if (next_ds_it)
    next_ds_it.item_selected_set(true);
}

void
_select_prev_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *selected_ds_it, *prev_ds_it;
   Evas_Object *ds = data;

   selected_ds_it = ds.selected_item_get();
   if (!selected_ds_it) return;

   prev_ds_it = selected_ds_it.item_prev_get();
   if (prev_ds_it)
     prev_ds_it.item_selected_set(true);
}



EAPI_MAIN int
elm_main (int argc, char *argv[])
{

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("diskselector", "Diskselector Items Example"));
  win.autodel_set(true);

  ::elm_box bx(efl::eo::parent = win);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);

  ::elm_diskselector ds(efl::eo::parent = win);
  ds.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  ds.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  //  evas_object_smart_callback_add(ds, "selected", _ds_selected_cb, NULL);
  //  ds.smart_callback_add("selected", _ds_selected_cb, NULL);
  bx.pack_end(ds);
  ds.visibility_set(true);

  ds.item_append("Item 0", NULL, NULL, NULL);
  ds.item_append("Item 1", NULL, NULL, NULL);
  ds.item_append("Item 2", NULL, NULL, NULL);

  ::elm_box hbx(efl::eo::parent = win);
  hbx.horizontal_set(true);
  hbx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  hbx.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx.pack_end(hbx);
  hbx.visibility_set(true);

  ::elm_button bt(efl::eo::parent = win);
  bt.text_set("text" , "Append item");
  bt.callback_clicked_add(&_add_cb);
  hbx.pack_end(bt);
  bt.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt.visibility_set(true);

  ::elm_button bt2(efl::eo::parent = win);
  bt2.text_set("text" , "Append with icon");
  bt2.smart_callback_add("clicked", _add_ic_cb, ds);
  hbx.pack_end(bt2);
  bt2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt2.visibility_set(true);

  ::elm_button bt3(efl::eo::parent = win);
  bt3.text_set("text" , "Append with selected function");
  bt3.smart_callback_add("clicked", _add_func_cb, ds);
  hbx.pack_end(bt3);
  bt3.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt3.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt3.visibility_set(true);

  ::elm_button bt4(efl::eo::parent = win);
  bt4.text_set("text" , "Append with data");
  bt4.smart_callback_add("clicked", _add_data_cb, ds);
  hbx.pack_end(bt4);
  bt4.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt4.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt4.visibility_set(true);

  ::elm_box hbx2(efl::eo::parent = win);
  hbx2.horizontal_set(true);
  hbx2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  hbx2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx.pack_end(hbx2);
  bt.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  hbx2.visibility_set(true);

  ::elm_button bt5(efl::eo::parent = win);
  bt5.text_set("text" , "Delete item");
  bt5.smart_callback_add("clicked", _del_cb, ds);
  hbx2.pack_end(bt5);
  bt5.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt5.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt5.visibility_set(true);

  ::elm_button bt6(efl::eo::parent = win);
  bt6.text_set("text" , "Unselect item");
  bt6.smart_callback_add("clicked", _unselect_cb, ds);
  hbx2.pack_end(bt6);
  bt6.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt6.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt6.visibility_set(true);

  ::elm_button bt7(efl::eo::parent = win);
  bt7.text_set("text" , "Print items");
  bt7.smart_callback_add("clicked", _print_cb, ds);
  hbx2.pack_end(bt7);
  bt7.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt7.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt7.visibility_set(true);

  ::elm_button bt8(efl::eo::parent = win);
  bt8.text_set("text", "Clear");
  bt8.smart_callback_add("clicked", _clear_cb, ds);
  hbx2.pack_end(bt8);
  bt8.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt8.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt8.visibility_set(true);

  ::elm_box hbx3(efl::eo::parent = win);
  hbx3.horizontal_set(true);
  hbx3.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  hbx3.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx.pack_end(hbx3);
  bt5.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt5.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  hbx3.visibility_set(true);

  ::elm_button bt9(efl::eo::parent = win);
  bt9.text_set("text" , "Select first item");
  bt9.smart_callback_add("clicked", _select_first_cb, ds);
  hbx3.pack_end(bt9);
  bt9.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt9.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt9.visibility_set(true);

  ::elm_button bt10(efl::eo::parent = win);
  bt10.text_set("text" , "Select last item");
  bt10.smart_callback_add("clicked", _select_last_cb, ds);
  hbx3.pack_end(bt10);
  bt10.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt10.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt10.visibility_set(true);

  ::elm_button bt11(efl::eo::parent = win);
  bt11.text_set("text" , "Select next item");
  bt11.smart_callback_add("clicked", _select_next_cb, ds);
  hbx3.pack_end(bt11);
  bt11.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt11.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt11.visibility_set(true);

  ::elm_button bt12(efl::eo::parent = win);
  bt12.text_set("text", "Select previous item");
  bt12.smart_callback_add("clicked", _select_prev_cb, ds);
  hbx3.pack_end(bt12);
  bt12.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt12.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt12.visibility_set(true);

  win.visibility_set(true);

  elm_run();
  elm_shutdown();
  
  return 0;
  
}
ELM_MAIN();
