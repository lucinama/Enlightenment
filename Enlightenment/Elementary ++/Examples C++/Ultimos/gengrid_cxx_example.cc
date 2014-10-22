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

typedef struct _Example_Item
{
   const char *path;
} Example_Item;

static const char *imgs[9] =
{
   "panel_01.jpg",
   "plant_01.jpg",
   "rock_01.jpg",
   "rock_02.jpg",
   "sky_01.jpg",
   "sky_02.jpg",
   "sky_03.jpg",
   "sky_04.jpg",
   "wood_01.jpg",
};

static Elm_Gengrid_Item_Class *gic = NULL;
static Evas_Object *before_bt, *after_bt;

static void
_horizontal_grid(void        *data,
                 Evas_Object *obj,
                 void        *event_info)
{
   Evas_Object *grid = data;

   elm_gengrid_horizontal_set(grid, elm_check_state_get(obj));
}

static void
_always_select_change(void        *data,
                      Evas_Object *obj,
                      void        *event_info)
{
   Evas_Object *grid = data;
   Eina_Bool always = elm_check_state_get(obj);

   if (always)
     elm_gengrid_select_mode_set(grid, ELM_OBJECT_SELECT_MODE_ALWAYS);
   else
     elm_gengrid_select_mode_set(grid, ELM_OBJECT_SELECT_MODE_DEFAULT);

   fprintf(stdout, "\"Always select\" mode for gengrid items is now %s\n",
           always ? "on" : "off");
}

static void
_bouncing_change(void        *data,
                 Evas_Object *obj,
                 void        *event_info)
{
   Evas_Object *grid = data;
   Eina_Bool bounce = elm_check_state_get(obj);

   elm_scroller_bounce_set(grid, bounce, bounce);

   fprintf(stdout, "Bouncing effect for gengrid is now %s\n",
           bounce ? "on" : "off");
}

static void
_multi_change(void        *data,
              Evas_Object *obj,
              void        *event_info)
{
   Evas_Object *grid = data;
   Eina_Bool multi = elm_check_state_get(obj);

   elm_gengrid_multi_select_set(grid, multi);

   fprintf(stdout, "Multi-selection for gengrid is now %s\n",
           multi ? "on" : "off");

   elm_object_disabled_set(before_bt, multi);
   elm_object_disabled_set(after_bt, multi);

   if (!multi)
     {
        Elm_Object_Item *gg_it;
        const Eina_List *selected = elm_gengrid_selected_items_get(grid), *l;
        EINA_LIST_FOREACH(selected, l, gg_it)
           elm_gengrid_item_selected_set(gg_it, EINA_FALSE);
     }
}

static void
_no_sel_change(void        *data,
               Evas_Object *obj,
               void        *event_info)
{
   Evas_Object *grid = data;
   Eina_Bool no_sel = elm_check_state_get(obj);

   if (no_sel)
     elm_gengrid_select_mode_set(grid, ELM_OBJECT_SELECT_MODE_NONE);
   else
     elm_gengrid_select_mode_set(grid, ELM_OBJECT_SELECT_MODE_DEFAULT);

   fprintf(stdout, "Selection for gengrid items is now %s\n",
           no_sel ? "disabled" : "enabled");
}

static void
_grid_sel(void        *data,
          Evas_Object *obj,
          void        *event_info)
{
   unsigned int x, y;
   Example_Item *it = elm_object_item_data_get(event_info);

   elm_gengrid_item_pos_get(event_info, &x, &y);

   fprintf(stdout, "Item [%p], with data [%p], path %s, at position (%d, %d),"
           " has been selected\n", event_info, data, it->path, x, y);
}

static Example_Item *
_item_new(void)
{
   Example_Item *it;

   it = malloc(sizeof(*it));
   it->path = eina_stringshare_add(imgs[rand() % (sizeof(imgs) /
                                                  sizeof(imgs[0]))]);
   return it;
}

static void
_before_bt_clicked(void        *data,
                   Evas_Object *obj,
                   void        *event_info)
{
   Example_Item *it;
   Evas_Object *grid = data;
   Elm_Object_Item *sel;

   sel = elm_gengrid_selected_item_get(grid);
   if (!sel)
     return;

   it = _item_new();
   elm_gengrid_item_insert_before(grid, gic, it, sel, _grid_sel, NULL);
}

static void
_after_bt_clicked(void        *data,
                  Evas_Object *obj,
                  void        *event_info)
{
   Example_Item *it;
   Evas_Object *grid = data;
   Elm_Object_Item *sel;

   sel = elm_gengrid_selected_item_get(grid);
   if (!sel)
     return;

   it = _item_new();
   elm_gengrid_item_insert_after(grid, gic, it, sel, _grid_sel, NULL);
}

static void
_prepend_bt_clicked(void        *data,
                    Evas_Object *obj,
                    void        *event_info)
{
   Example_Item *it;
   Evas_Object *grid = data;

   it = _item_new();
   elm_gengrid_item_prepend(grid, gic, it, _grid_sel, NULL);
}

static void
_append_bt_clicked(void        *data,
                   Evas_Object *obj,
                   void        *event_info)
{
   Evas_Object *grid = data;
   Example_Item *it = _item_new();

   elm_gengrid_item_append(grid, gic, it, _grid_sel, NULL);
}

static void
_clear_cb(void        *data,
          Evas_Object *obj,
          void        *event_info)
{
   elm_gengrid_clear(data);

   fprintf(stdout, "Clearing the grid!\n");
}

static void
_bring_1st_clicked(void        *data,
                   Evas_Object *obj,
                   void        *event_info)
{
   Elm_Object_Item *gg_it = elm_gengrid_first_item_get(data);

   if (!gg_it) return;

   elm_gengrid_item_bring_in(gg_it, ELM_GENGRID_ITEM_SCROLLTO_IN);
}

static void
_show_last_clicked(void        *data,
                   Evas_Object *obj,
                   void        *event_info)
{
   Elm_Object_Item *gg_it = elm_gengrid_last_item_get(data);

   if (!gg_it) return;

   elm_gengrid_item_show(gg_it, ELM_GENGRID_ITEM_SCROLLTO_IN);
}

static void
_toggle_disabled_cb(void        *data,
                    Evas_Object *obj,
                    void        *event_info)
{
   Elm_Object_Item *gg_it = elm_gengrid_selected_item_get(data);

   if (!gg_it) return;

   elm_gengrid_item_selected_set(gg_it, EINA_FALSE);
   elm_object_item_disabled_set(gg_it, EINA_TRUE);
}

static void
_size_changed(void        *data,
              Evas_Object *obj,
              void        *event_info)
{
   Evas_Object *grid = data;
   int size = elm_spinner_value_get(obj);

   elm_gengrid_item_size_set(grid, size, size);
}

static void
_double_click(void        *data,
              Evas_Object *obj,
              void        *event_info)
{
   fprintf(stdout, "Double click on item with handle %p\n", event_info);
}

static void
_long_pressed(void        *data,
              Evas_Object *obj,
              void        *event_info)
{
   fprintf(stdout, "Long press on item with handle %p\n", event_info);
}

static char *
_grid_label_get(void        *data,
                Evas_Object *obj,
                const char  *part)
{
   const Example_Item *it = data;
   char buf[256];

   snprintf(buf, sizeof(buf), "Photo %s", it->path);
   return strdup(buf);
}

static Evas_Object *
_grid_content_get(void        *data,
                  Evas_Object *obj,
                  const char  *part)
{
   const Example_Item *it = data;

   if (!strcmp(part, "elm.swallow.icon"))
     {
        Evas_Object *icon = elm_bg_add(obj);
        char buf[PATH_MAX];

        snprintf(buf, sizeof(buf), "%s/images/%s", elm_app_data_dir_get(),
                 it->path);

        elm_bg_file_set(icon, buf, NULL);
        evas_object_size_hint_aspect_set(icon, EVAS_ASPECT_CONTROL_VERTICAL, 1,
                                         1);
        evas_object_show(icon);
        return icon;
     }
   else if (!strcmp(part, "elm.swallow.end"))
     {
        Evas_Object *ck;
        ck = elm_check_add(obj);
        evas_object_propagate_events_set(ck, EINA_FALSE);
        evas_object_show(ck);
        return ck;
     }

   return NULL;
}

static Eina_Bool
_grid_state_get(void        *data,
                Evas_Object *obj,
                const char  *part)
{
   return EINA_FALSE;
}

static void
_grid_del(void        *data,
          Evas_Object *obj)
{
   Example_Item *it = data;

   eina_stringshare_del(it->path);
   free(it);
}

static void
_grid_scroll_stopped_cb(void        *data,
                        Evas_Object *obj,
                        void        *event_info)
{
   int h_pagenumber = 0, v_pagenumber = 0;
   elm_scroller_current_page_get(obj, &h_pagenumber, &v_pagenumber);
   fprintf(stdout, "Grid current horiz page is %d, vert page is %d\n",
           h_pagenumber, v_pagenumber);
}

static void
_h_align_change_cb(void        *data,
                   Evas_Object *obj,
                   void        *event_info)
{
   double v_align;
   double val = elm_slider_value_get(obj);

   elm_gengrid_align_get(data, NULL, &v_align);

   fprintf(stdout, "Setting horizontal alignment to %f\n", val);
   elm_gengrid_align_set(data, val, v_align);
}

static void
_v_align_change_cb(void        *data,
                   Evas_Object *obj,
                   void        *event_info)
{
   double h_align;
   double val = elm_slider_value_get(obj);

   elm_gengrid_align_get(data, &h_align, NULL);

   fprintf(stdout, "Setting vertical alignment to %f\n", val);
   elm_gengrid_align_set(data, h_align, val);
}

static void
_page_change_cb(void        *data,
                Evas_Object *obj,
                void        *event_info)
{
   double val = elm_slider_value_get(obj);

   elm_scroller_page_relative_set(data, val, val);

   fprintf(stdout, "Setting grid page's relative size to %f\n", val);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   Eina_Bool bounce;
   double h, v;

   srand(time(NULL));

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   
   elm_app_info_set(elm_main, "elementary", "images");

	::elm_win win(elm_win_util_standard_add(("gengrid", "Generic Grid Example"));
	win.autodel_set(true);

 	::elm_box bx(efl::eo::parent = win);
	bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(bx);
   	bx.visibility_set(true);

	::elm_gengrid grid(efl::eo::parent = win);
   grid.item_size_set(150, 150);
   grid.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   grid.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   bx.pack_end(grid);
   grid.callback_clicked_double_add(&_double_click);
   grid.callback_longpressed_add(&_long_pressed);
   grid.visibility_set(true);

 	::elm_box hbx1(efl::eo::parent = win);
	hbx1.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
   	bx.pack_end(hbx1);
   	hbx1.visibility_set(true);

 	::elm_button bt(efl::eo::parent = win);
	elm_object_text_set(bt._eo_ptr(), "Append"); // XXX
    bt.callback_clicked_add(&_append_bt_clicked);
   	hbx1.pack_end(bt);
   	bt.visibility_set(true);

 	::elm_button bt2(efl::eo::parent = win);
	elm_object_text_set(bt2._eo_ptr(), "Prepend"); // XXX
    bt2.callback_clicked_add(&_prepend_bt_clicked);
   	hbx1.pack_end(bt2);
   	bt2.visibility_set(true);

 	::elm_button beforebt(efl::eo::parent = win);
	elm_object_text_set(beforebt._eo_ptr(), "Insert before"); // XXX
    beforebt.callback_clicked_add(&_before_bt_clicked);
   	hbx1.pack_end(beforebt);
   	beforebt.visibility_set(true);
   	
	::elm_button afterbt(efl::eo::parent = win);
	elm_object_text_set(afterbt._eo_ptr(), "Insert after"); // XXX
    afterbt.callback_clicked_add(&_after_bt_clicked);
   	hbx1.pack_end(afterbt);
   	afterbt.visibility_set(true);
  	
  	::elm_button bt3(efl::eo::parent = win);
	elm_object_text_set(bt3._eo_ptr(), "Clear"); // XXX
    bt3.callback_clicked_add(&_clear_cb);
   	hbx1.pack_end(bt3);
   	bt3.visibility_set(true);

  	::elm_button bt4(efl::eo::parent = win);
	elm_object_text_set(bt4._eo_ptr(), "Bring in 1st"); // XXX
    bt4.callback_clicked_add(&_bring_1st_clicked);
   	hbx1.pack_end(bt4);
   	bt4.visibility_set(true);

 	::elm_button bt4(efl::eo::parent = win);
	elm_object_text_set(bt4._eo_ptr(), "Bring in 1st"); // XXX
    bt4.callback_clicked_add(&_bring_1st_clicked);
   	hbx1.pack_end(bt4);
   	bt4.visibility_set(true);

 	::elm_button bt5(efl::eo::parent = win);
	elm_object_text_set(bt5._eo_ptr(), "Show last"); // XXX
    bt5.callback_clicked_add(&_show_last_clicked);
   	hbx1.pack_end(bt5);
   	bt5.visibility_set(true);

 	::elm_spinner sp(efl::eo::parent = win);
   sp.min_max_set(10, 1024);
   sp.value_set(150);
   sp.label_format_set(sp, "Item size: %.0f");
   sp.callback_changed_add(&_size_changed);
   sp.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   hbx1.pack_end(sp);
   sp.visibility_set(true);

 	::elm_box hbx2(efl::eo::parent = win);
	hbx2.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
	hbx2.horizontal_set(true);
   	bx.pack_end(hbx2);
   	hbx2.visibility_set(true);

	::elm_button bt6(efl::eo::parent = win);
	elm_object_text_set(bt6._eo_ptr(), "Disable item"); // XXX
    bt6.callback_clicked_add(&_toggle_disabled_cb);
   	hbx2.pack_end(bt6);
   	bt6.visibility_set(true);

	::elm_check ck(efl::eo::parent = win);
	elm_object_text_set(ck._eo_ptr(), "Horizontal mode"); // XXX
    ck.callback_changed_add(&_horizontal_grid);
   	hbx2.pack_end(ck);
   	ck.visibility_set(true);

	::elm_check ck2(efl::eo::parent = win);
	elm_object_text_set(ck2._eo_ptr(), "Always select"); // XXX
    ck2.callback_changed_add(&_always_select_change);
   	hbx2.pack_end(ck2);
   	ck2.visibility_set(true);

	::elm_check ck3(efl::eo::parent = win); 
	grid.bounce_allow_get(&bounce, NULL);  // XXX
	elm_object_text_set(ck3._eo_ptr(), "Bouncing"); // XXX
	ck3.state_set(bounce);
	ck3.callback_changed_add(&_bouncing_change);
   	hbx2.pack_end(ck3);
   	ck3.visibility_set(true);

	::elm_check ck4(efl::eo::parent = win); 
	elm_object_text_set(ck4._eo_ptr(), "Multi-selection"); // XXX
	ck4.state_set(grid.multi_select_get());
	ck4.callback_changed_add(&_multi_change);
   	hbx2.pack_end(ck4);
   	ck4.visibility_set(true);

	::elm_check ck5(efl::eo::parent = win); 
	elm_object_text_set(ck5._eo_ptr(), "No selection"); // XXX
	ck5.callback_changed_add(&_no_sel_change);
   	hbx2.pack_end(ck5);
   	ck5.visibility_set(true);

 	::elm_box hbx3(efl::eo::parent = win);
	hbx3.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
	hbx3.horizontal_set(true);
   	bx.pack_end(hbx3);
   	hbx3.visibility_set(true);

    grid.align_get(&h, &v);
   	grid.callback_scroll_anim_stop_add(&_grid_scroll_stopped_cb);

 	::elm_slider sl(efl::eo::parent = win);
 		elm_object_text_set(sl._eo_ptr(), "Horiz. alignment"); // XXX
     sl.span_size_set(100);
    sl.size_hint_align_set(0.5, EVAS_HINT_FILL);
    sl.size_hint_weight_set(0.0, EVAS_HINT_EXPAND);
    sl.indicator_format_set("%1.1f");
   sl.value_set(h);
   hbx3.pack_end(sl);
    sl.visibility_set(true);

    sl.callback_changed_add(&_h_align_change_cb);

 	::elm_slider sl2(efl::eo::parent = win);
 		elm_object_text_set(sl2._eo_ptr(), "Vert. alignment"); // XXX
     sl2.span_size_set(100);
    sl2.size_hint_align_set(0.5, EVAS_HINT_FILL);
    sl2.size_hint_weight_set(0.0, EVAS_HINT_EXPAND);
    sl2.indicator_format_set("%1.1f");
   sl2.value_set(v);
   hbx3.pack_end(sl2);
    sl2.visibility_set(true);

    sl2.callback_changed_add(&_v_align_change_cb);

   grid.align_get(&h, &v);

 	::elm_slider sl3(efl::eo::parent = win);
 		elm_object_text_set(sl3._eo_ptr(), "Page rel. size"); // XXX
     sl3.span_size_set(100);
    sl3.size_hint_align_set(0.5, EVAS_HINT_FILL);
    sl3.size_hint_weight_set(0.0, EVAS_HINT_EXPAND);
    sl3.indicator_format_set("%1.1f");
   sl3.value_set(h);
   hbx3.pack_end(sl3);
    sl3.visibility_set(true);

   grid._page_change_cb(sl, NULL);
   sl3.callback_changed_add(&_page_change_cb);

   if (!gic)
     {
        gic = elm_gengrid_item_class_new();
        gic->item_style = "default";
        gic->func.text_get = _grid_label_get;
        gic->func.content_get = _grid_content_get;
        gic->func.state_get = _grid_state_get;
        gic->func.del = _grid_del;
     } // we only create the first time its needed. we dont unref/free

   _append_bt_clicked(grid, NULL, NULL);  // XXX
   _append_bt_clicked(grid, NULL, NULL);  // XXX
   _append_bt_clicked(grid, NULL, NULL);  // XXX

   win.evas::object::size_set(600, 600);
  win.visibility_set(true);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
