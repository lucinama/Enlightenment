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

#define N_ITEMS 6

typedef struct _Node_Data {
     Eina_List *children;
     int value;
     int level;
     Eina_Bool favorite;
} Node_Data;

static Elm_Genlist_Item_Class *_itc = NULL;
static Elm_Genlist_Item_Class *_itp = NULL;
static Elm_Genlist_Item_Class *_itfav = NULL;
static int nitems = 0;

static char *
_item_label_get(void *data, Evas_Object *obj, const char *part)
{
   char buf[256];
   Node_Data *d = data;

   if (!strcmp(part, "elm.text"))
     snprintf(buf, sizeof(buf), "Item # %i (level %i)", d->value, d->level);

   return strdup(buf);
}

static Evas_Object *
_item_content_get(void *data, Evas_Object *obj, const char *part)
{
   Evas_Object *ic = elm_icon_add(obj);

   if (!strcmp(part, "elm.swallow.icon"))
     elm_icon_standard_set(ic, "file");

   evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   return ic;
}

static void
_item_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
   printf("sel item data [%p] on genlist obj [%p], item pointer [%p]\n",
          data, obj, event_info);
}

static char *
_parent_label_get(void *data, Evas_Object *obj, const char *part)
{
   char buf[256];
   Node_Data *d = data;

   snprintf(buf, sizeof(buf), "Group %d (%d items)", d->value / 7,
            eina_list_count(d->children));

   return strdup(buf);
}

static Evas_Object *
_parent_content_get(void *data, Evas_Object *obj, const char *part)
{
   Evas_Object *ic = elm_icon_add(obj);

   if (!strcmp(part, "elm.swallow.icon"))
     elm_icon_standard_set(ic, "folder");

   evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   return ic;
}

static char *
_favorite_label_get(void *data, Evas_Object *obj, const char *part)
{
   char buf[256];
   Node_Data *d = data;

   if (!strcmp(part, "elm.text"))
     snprintf(buf, sizeof(buf), "Favorite # %i", d->value);

   return strdup(buf);
}

static Evas_Object *
_favorite_content_get(void *data, Evas_Object *obj, const char *part)
{
   Evas_Object *ic = elm_icon_add(obj);

   if (!strcmp(part, "elm.swallow.icon"))
     elm_icon_standard_set(ic, "apps");

   evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   return ic;
}

static void
_append_cb(void *data, Evas_Object *o, void *event_info)
{
   Evas_Object *list = data;
   Elm_Object_Item *glit, *parent = NULL;
   Node_Data *pdata, *d = malloc(sizeof(*d));

   d->children = NULL;
   d->value = nitems++;
   d->favorite = EINA_FALSE;

   glit = elm_genlist_selected_item_get(list);
   if (glit)
     parent = elm_genlist_item_parent_get(glit);

   if (parent)
     {
        d->level = elm_genlist_item_expanded_depth_get(parent) + 1;
        pdata = elm_object_item_data_get(parent);
        pdata->children = eina_list_append(pdata->children, d); 

   else
     d->level = 0;

   elm_genlist_item_append(list, _itc,
                           d, parent,
                           ELM_GENLIST_ITEM_NONE,
                           _item_sel_cb, NULL);   // XXX
}

static void
_favorite_cb(void *data, Evas_Object *o, void *event_info)
{
   Evas_Object *list = data;
   Elm_Object_Item *glit = elm_genlist_selected_item_get(list);

   if (!glit) return;

   Node_Data *d = elm_object_item_data_get(glit);
   d->favorite = !d->favorite;
   if (d->favorite)
     elm_genlist_item_item_class_update(glit, _itfav);
   else
     {
        if (d->children)
          elm_genlist_item_item_class_update(glit, _itp);
        else
          elm_genlist_item_item_class_update(glit, _itc);
     }

   elm_genlist_item_update(glit);
}

static void
_add_child_cb(void *data, Evas_Object *o, void *event_info)
{
   Evas_Object *list = data;
   Elm_Object_Item *glit = elm_genlist_selected_item_get(list);
   Elm_Object_Item *glit_prev, *glit_parent;

   if (!glit) return;

   Node_Data *d = elm_object_item_data_get(glit);
   glit_prev = elm_genlist_item_prev_get(glit);
   glit_parent = elm_genlist_item_parent_get(glit);

   Eina_Bool change_item = !d->children;

   Node_Data *ndata = malloc(sizeof(*ndata));
   ndata->value = nitems++;
   ndata->children = NULL;
   ndata->favorite = EINA_FALSE;
   ndata->level = elm_genlist_item_expanded_depth_get(glit) + 1;
   d->children = eina_list_append(d->children, ndata);

   if (change_item)
     {
        elm_object_item_del(glit);

        if (glit_prev != glit_parent)
          glit = elm_genlist_item_insert_after(list, _itp, d, glit_parent,
                                               glit_prev,
                                               ELM_GENLIST_ITEM_TREE,
                                               _item_sel_cb, NULL);
        else
          glit = elm_genlist_item_prepend(list, _itp, d, glit_parent,
                                          ELM_GENLIST_ITEM_TREE,
                                          _item_sel_cb, NULL);
        elm_genlist_item_expanded_set(glit, EINA_FALSE);
        elm_genlist_item_selected_set(glit, EINA_TRUE);
     }
   else if (elm_genlist_item_expanded_get(glit))
     {
        elm_genlist_item_append(list, _itc, ndata, glit,
                                ELM_GENLIST_ITEM_NONE, _item_sel_cb, NULL);
     }

   elm_genlist_item_update(glit);

}

static void
_clear_list(Node_Data *d)
{
   Node_Data *tmp;

   EINA_LIST_FREE(d->children, tmp)
      _clear_list(tmp);
   free(d);
}

static void
_del_item_cb(void *data, Evas_Object *o, void *event_info)
{
   Evas_Object *list = data;
   Elm_Object_Item *glit = elm_genlist_selected_item_get(list);
   Elm_Object_Item *glit_parent = NULL;

   if (!glit) return;

   Node_Data *pdata, *d = elm_object_item_data_get(glit);
   glit_parent = elm_genlist_item_parent_get(glit);
   elm_genlist_item_subitems_clear(glit);
   elm_object_item_del(glit);

   _clear_list(d);

   if (!glit_parent) return;

   pdata = elm_object_item_data_get(glit_parent);
   pdata->children = eina_list_remove(pdata->children, d);
   elm_genlist_item_update(glit_parent);
}

static void
_expand_request_cb(void *data, Evas_Object *o, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   printf("expand request on item: %p\n", event_info);
   elm_genlist_item_expanded_set(glit, EINA_TRUE);
}

static void
_contract_request_cb(void *data, Evas_Object *o, void *event_info)
{
   Elm_Object_Item *glit = event_info;
   printf("contract request on item: %p\n", event_info);
   elm_genlist_item_expanded_set(glit, EINA_FALSE);
}

static void
_expanded_cb(void *data, Evas_Object *o, void *event_info)
{
   Eina_List *l;
   Elm_Object_Item *glit = event_info;
   Node_Data *it_data, *d = elm_object_item_data_get(glit);
   Evas_Object *list = elm_object_item_widget_get(glit);

   Elm_Genlist_Item_Class *ic;

   EINA_LIST_FOREACH(d->children, l, it_data)
     {
       Elm_Object_Item *nitem;
       Elm_Genlist_Item_Type type = ELM_GENLIST_ITEM_NONE;
       printf("expanding item: #%d from parent #%d\n", it_data->value, d->value);
       if (it_data->favorite)
	 ic = _itfav;
       else if (it_data->children)
	 {
	   ic = _itp;
	   type = ELM_GENLIST_ITEM_TREE;
	 }
       else
	 ic = _itc;

       nitem = elm_genlist_item_append(list, ic, it_data, glit,
				       type, _item_sel_cb, NULL);
       elm_genlist_item_expanded_set(nitem, EINA_FALSE);
     }
}

 static void
   _contracted_cb(void *data, Evas_Object *o, void *event_info)
 {
   Elm_Object_Item *glit = event_info;
   elm_genlist_item_subitems_clear(glit);
 }

 static Evas_Object *
   _button_add(Evas_Object *list, Evas_Object *box, const char *label, Evas_Smart_Cb cb)
 {
   Evas_Object *bt;

   bt = elm_button_add(elm_object_parent_widget_get(list));
   elm_object_text_set(bt, label);
   elm_box_pack_end(box, bt);
   evas_object_show(bt);

   if (cb)
     evas_object_smart_callback_add(bt, "clicked", cb, list);

   return bt;
 }

 EAPI_MAIN int
   elm_main (int argc, char *argv[])
 {
   int i;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   ::elm_win win(elm_win_util_standard_add("genlist", "Genlist"));
   win.autodel_set(true);

   ::elm_box box(efl::eo::parent = win);
   box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   win.resize_object_add(box);
   box.visibility_set(true);

   if (!_itc)
     {
       _itc = elm_genlist_item_class_new();
       _itc->item_style = "default";
       _itc->func.text_get = _item_label_get;
       _itc->func.content_get = _item_content_get;
       _itc->func.state_get = NULL;
       _itc->func.del = NULL;
     }

   if (!_itp)
     {
       _itp = elm_genlist_item_class_new();
       _itp->item_style = "default";
       _itp->func.text_get = _parent_label_get;
       _itp->func.content_get = _parent_content_get;
       _itp->func.state_get = NULL;
       _itp->func.del = NULL;
     }

   if (!_itfav)
     {
       _itfav = elm_genlist_item_class_new();
       _itfav->item_style = "default";
       _itfav->func.text_get = _favorite_label_get;
       _itfav->func.content_get = _favorite_content_get;
       _itfav->func.state_get = NULL;
       _itfav->func.del = NULL;
     }


   ::elm_genlist list(efl::eo::parent = win);

   list.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   list.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   box.pack_end(list);
  list.visibility_set(true);

   ::elm_box fbox(efl::eo::parent = win);
   fbox.layout_set(evas_object_box_layout_flow_horizontal, NULL, NULL);
   fbox.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
   fbox.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   box.pack_end(fbox);
   fbox.visibility_set(true);

   _button_add(list, fbox, "append item", _append_cb);
   _button_add(list, fbox, "favorite", _favorite_cb);
   _button_add(list, fbox, "add child", _add_child_cb);
   _button_add(list, fbox, "del item", _del_item_cb);

   for (i = 0; i < N_ITEMS; i++)
     {
       Elm_Object_Item *gli = NULL, *glg = NULL;
       Node_Data *data = malloc(sizeof(*data)); // data for this item
       data->children = NULL;
       data->value = i;
       data->favorite = EINA_FALSE;
       nitems++;

       Node_Data *pdata = NULL; // data for the parent of the group

       printf("creating item: #%d\n", data->value);
       if (i % 3 == 0)
	 {
	   glg = gli = elm_genlist_item_append(list, _itp, data, NULL,
					       ELM_GENLIST_ITEM_TREE,
					       _item_sel_cb, NULL);
	   elm_genlist_item_expanded_set(glg, EINA_TRUE);
	   pdata = data;
	   data->level = 0;
	 }
       else
	 {
	   gli = elm_genlist_item_append(list, _itc, data, glg,
					 ELM_GENLIST_ITEM_NONE,
					 _item_sel_cb, NULL);
	   if (pdata)
	     pdata->children = eina_list_append(pdata->children, data);
	   data->level = 1;
	 }
     }

   list.callback_expand_request_add(&_expand_request_cb);
   list.callback_contract_request_add(&_contract_request_cb);
   list.callback_expanded_add(&_expanded_cb);
   list.callback_contracted_add(&_contracted_cb);

   win.evas::object::size_set(420, 600);
   win.visibility_set(true);

   elm_run();
   elm_shutdown();

   return 0;
 }
 ELM_MAIN()
