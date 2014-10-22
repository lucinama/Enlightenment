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

typedef struct
{
  Evas_Object *win;
  Evas_Object *edit_buffer;
} App_Data;

typedef struct
{
  int size;
  int vsize;
  int width, height;

  const char *emo;

  App_Data *ad;
} App_Inwin_Data;

static void
_edit_buffer_insert(::elm_entry e, const char *text)
{
  e.entry_insert(text);
  e.focus_set(true);
}

static void
_it_sel_cb(void *data, Evas_Object *obj, void *event)
{
  App_Inwin_Data *aid = data;
  Elm_Object_Item *gg_it = event;

  aid->emo = elm_object_item_data_get(gg_it);

  elm_naviframe_item_simple_promote(aid->naviframe, aid->settings);
}

static char *
_emo_label_get(void *data, Evas_Object *obj, const char *part)
{
  return strdup(data);
}

static Evas_Object *
_emo_content_get(void *data, Evas_Object *obj, const char *part)
{
  ::elm_layout o;

  if (strcmp(part, "icon"))
    return NULL;
  o = elm_layout_add(obj);
  if (!o.theme_set("entry/emoticon", data, "default"))
    {
      fprintf(stderr, "Failed to set layout");
      return NULL;
    }
  return o;
}

static void
_emo_del(void *data, Evas_Object *obj)
{
  free(data);
}

static Evas_Object *
_page_grid_add(Evas_Object *parent, App_Inwin_Data *aid)
{
  Evas_Object *grid;
  char *theme, *emo;
  Eina_List *emos, *it;
  static Elm_Gengrid_Item_Class *it_class;
  it_class = elm_gengrid_item_class_new();
  it_class->item_style = "default";
  it_class->func.text_get = _emo_label_get;
  it_class->func.content_get = _emo_content_get;
  it_class->func.del = _emo_del;

  theme = elm_theme_list_item_path_get("default", NULL);
  if (!theme) return NULL;
  emos = edje_file_collection_list(theme);
  free(theme);
  if (!emos) return NULL;

  grid = elm_gengrid_add(parent);
  elm_gengrid_item_size_set(grid, 64, 80);
  evas_object_size_hint_weight_set(grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  evas_object_size_hint_align_set(grid, EVAS_HINT_FILL, EVAS_HINT_FILL);

  EINA_LIST_FOREACH(emos, it, emo)
    {
      char name[512];

      if (strncmp(emo, "elm/entry/emoticon/", 19))
	continue;
      sscanf(emo, "elm/entry/emoticon/%[^/]/default", name);
      elm_gengrid_item_append(grid, it_class, strdup(name), _it_sel_cb, aid);
    }
  edje_file_collection_list_free(emos);
  elm_gengrid_item_class_free(it_class);

  return grid;
}

static void
_btn_insert_cb(void *data, Evas_Object *obj, void *event)
{
  App_Inwin_Data *aid = data;
  const char *size[] = {
    "size",
    "absize",
    "relsize"
  };
  const char *vsize[] = {
    "full",
    "ascent"
  };
  char buf[512];

  snprintf(buf, sizeof(buf), "<item %s=%dx%d vsize=%s href=emoticon/%s>"
	   "</item>", size[aid->size], aid->width, aid->height,
	   vsize[aid->vsize], aid->emo);
  _edit_buffer_insert(aid->ad->edit_buffer, buf);

  evas_object_del(aid->inwin);
}

static void
_width_changed_cb(void *data, Evas_Object *obj, void *event)
{
  App_Inwin_Data *aid = data;

  aid->width = atoi(elm_object_text_get(obj));
}

static void
_height_changed_cb(void *data, Evas_Object *obj, void *event)
{
  App_Inwin_Data *aid = data;

  aid->height = atoi(elm_object_text_get(obj));
}

static Evas_Object *
_page_settings_add(Evas_Object *parent, App_Inwin_Data *aid)
{
  char buf[100];
  static Elm_Entry_Filter_Accept_Set accept_set = {
    .accepted = "0123456789",
    .rejected = NULL
  };
  static Elm_Entry_Filter_Limit_Size limit_size = {
    .max_char_count = 5,
    .max_byte_count = 0
  };

  ::elm_box box(efl::eo::parent = parent);
  box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  box.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);

  ::elm_frame sizeopts(efl::eo::parent = parent);
  elm_object_text_set(sizeopts._eo_ptr(), "Size"); // XXX
  sizeopts.size_hint_weight_set(sizeopts, EVAS_HINT_EXPAND, 0.0);
  sizeopts.size_hint_align_set(sizeopts, EVAS_HINT_FILL, EVAS_HINT_FILL);
  box.pack_end(sizeopts);
  sizeopts.visibility_set(true);

  ::elm_box box2(efl::eo::parent = parent);
  box2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  box2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_object_content_set(sizeopts._eo_ptr(), box2._eo_ptr()); // XXX
  box2.visibility_set(true);

  ::elm_box sizebox(efl::eo::parent = parent);
  sizebox.horizontal_set(true);
  sizebox.size_hint_weight_set(EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
  sizebox.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box2.pack_end(sizebox);
  sizebox.visibility_set(true);

  ::elm_radio rsize(efl::eo::parent = parent);
  elm_object_text_set(rsize._eo_ptr(), "Scale adjusted (size)"); // XXX
  rsize.state_value_set(0);
  rsize.value_pointer_set(&aid->size);
  sizebox.pack_end(rsize);
  rsize.visibility_set(true);

  ::elm_radio rabsize(efl::eo::parent = parent);
  elm_object_text_set(rabsize._eo_ptr(), "Absolute size (absize)"); // XXX
  rabsize.state_value_set(1);
  rabsize.value_pointer_set(&aid->size);
  rabsize.group_add(rsize);
  sizebox.pack_end(rabsize);
  rabsize.visibility_set(true);

  ::elm_radio rrelsize(efl::eo::parent = parent);
  elm_object_text_set(rrelsize._eo_ptr(), "Relative to line (relsize)"); // XXX
  rrelbsize.state_value_set(2);
  rrelsize.value_pointer_set(&aid->size);
  rrelsize.group_add(rsize);
  sizebox.pack_end(rrelsize);
  rrelsize.visibility_set(true);

  ::elm_box vsizebox(efl::eo::parent = parent);
  vsizebox.horizontal_set(true);
  vsizebox.size_hint_weight_set(EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
  vsizebox.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box2.pack_end(vsizebox);
  vsizebox.visibility_set(true);

  ::elm_radio rvfull(efl::eo::parent = parent);
  elm_object_text_set(rvfull._eo_ptr(), "Full height (vsize=full)"); // XXX
  rvfull.state_value_set(0);
  rvfull.value_pointer_set(&aid->vsize);
  vsizebox.pack_end(rvfull);
  rvfull.visibility_set(true);

  ::elm_radio rvascent(efl::eo::parent = parent);
  elm_object_text_set(rvascent._eo_ptr(), "Ascent only (vsize=ascent)"); // XXX
  rvascent.state_value_set(1);
  rvascent.value_pointer_set(&aid->vsize);
  rvascent.group_add(rvfull);
  vsizebox.pack_end(rvascent);
  rvascent.visibility_set(true);

  ::elm_frame fwidth(efl::eo::parent = parent);
  elm_object_text_set(fwidth._eo_ptr(), "Width"); // XXX
  fwidth.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
  fwidth.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box2.pack_end(fwidth);
  fwidth.visibility_set(true);

  snprintf(buf, sizeof(buf), "%d", aid->width);
  ::elm_entry ewidth(efl::eo::parent = parent);
  ewidth.single_line_set(true);
  ewidth.markup_filter_append(elm_entry_filter_accept_set,&accept_set);
  ewidth.markup_filter_append(elm_entry_filter_limit_size,&limit_size);
  elm_object_text_set(ewidth._eo_ptr(), buf); // XXX
  ewidth.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
  ewidth.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_object_content_set(fwidth._eo_ptr(), ewidth._eo_ptr()); // XXX
  ewidth.visibility_set(true);

  ewidth.callback_changed_add(&_width_changed_cb);

  ::elm_frame fheight(efl::eo::parent = parent);
  elm_object_text_set(fheight._eo_ptr(), "Height"); // XXX
  fheight.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
  fheight.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box2.pack_end(fheight);
  fheight.visibility_set(true);

  snprintf(buf, sizeof(buf), "%d", aid->height);
  ::elm_entry eheight(efl::eo::parent = parent);
  eheight.single_line_set(true);
  eheight.markup_filter_append(elm_entry_filter_accept_set,&accept_set);
  eheight.markup_filter_append(elm_entry_filter_limit_size,&limit_size);
  elm_object_text_set(eheight._eo_ptr(), buf); // XXX
  eheight.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
  eheight.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  elm_object_content_set(fheight._eo_ptr(), eheight._eo_ptr()); // XXX
  eheight.visibility_set(true);
   
  eheight.callback_changed_add(&_height_changed_cb);

  ::elm_button binsert(efl::eo::parent = parent);
  elm_object_text_set(binsert._eo_ptr(), "Insert"); // XXX
  box.pack_end(binsert);
  binsert.visibility_set(true);

  binsert.callback_clicked_add(&_btn_insert_cb);

  return box;
}

static void
_insert_cancel_cb(void *data, Evas_Object *obj, void *event)
{
  App_Inwin_Data *aid = data;

  evas_object_del(aid->inwin);
}

static void
_inwin_del_cb(void *data, Evas *e, Evas_Object *obj, void *event)
{
  free(data);
}

static void
_image_insert_cb(void *data, Evas_Object *obj, void *event)
{
  App_Data *ad = data;
  App_Inwin_Data *aid;
  Evas_Object *inwin, *box, *box2, *naviframe, *o;

  aid = calloc(1, sizeof(App_Inwin_Data));
  if (!aid) return;

  aid->ad = ad;
  aid->size = 1;
  aid->vsize = 1;
  aid->width = 64;
  aid->height = 64;

  inwin = elm_win_inwin_add(ad->win);
  inwin.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  inwin.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  inwin.visibility_set(true);

  inwin.event_callback_add(&_inwin_del_cb);

  ::elm_box box(efl::eo::parent = ad->win);
  box.size_hint_weight_set(EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
  box.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  inwin.inwin_content_set(box);
  box.visibility_set(true);

  ::elm_naviframe naviframe(efl::eo::parent = ad->win);
  naviframe.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  naviframe.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box.pack_end(naviframe);
  naviframe.visibility_set(true);

  o = _page_grid_add(ad->win, aid);
  naviframe.item_simple_push(o);
  aid->grid = o;

  o = _page_settings_add(ad->win, aid);
  naviframe.item_simple_push(o);
  aid->settings = o;

  naviframe.item_simple_promote(aid->grid);

  ::elm_box box2(efl::eo::parent = ad->win);
  box2.horizontal_set(true);
  box2.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
  box2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box.pack_end(box2);
  box2.visibility_set(true);
   
  ::elm_button bt(efl::eo::parent = ad->win);
  elm_object_text_set(bt._eo_ptr(), "Cancel"); // XXX
  bt.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box2.pack_end(bt);
  bt.visibility_set(true);

  bt.callback_clicked_add(&_insert_cancel_cb);

  aid->inwin = inwin;
  aid->naviframe = naviframe;
}

static void
_format_change_cb(void *data, Evas_Object *obj, void *event)
{
  App_Data *ad = data;
  char fmt_open[5], fmt_close[6];
  const char *sel;
  int cursor;
  char *s;
  const char *ptr, *what;
  Eina_Strbuf *buf = NULL;

  sel = elm_object_text_get(obj._eo_ptr()); // XXX
  snprintf(fmt_open, sizeof(fmt_open), "<%s>", sel);
  snprintf(fmt_close, sizeof(fmt_close), "</%s>", sel);

  buf = eina_strbuf_new();

  cursor = elm_entry_cursor_pos_get(ad->edit_buffer);
  elm_entry_cursor_begin_set(ad->edit_buffer);
  elm_entry_cursor_selection_begin(ad->edit_buffer);
  elm_entry_cursor_pos_set(ad->edit_buffer, cursor);
  elm_entry_cursor_selection_end(ad->edit_buffer);
  sel = elm_entry_selection_get(ad->edit_buffer);
  if (!sel || !sel[0])
    {
      eina_strbuf_append(buf, fmt_open);
      goto all_done;
    }
  what = fmt_open;
  ptr = sel;
  while ((s = strstr(ptr, what)))
    {
      ptr = s + strlen(what);
      if (what == fmt_open) what = fmt_close;
      else what = fmt_open;
    }
  eina_strbuf_append(buf, what);
  if (what == fmt_close)
    {
      elm_entry_cursor_selection_begin(ad->edit_buffer);
      elm_entry_cursor_end_set(ad->edit_buffer);
      elm_entry_cursor_selection_end(ad->edit_buffer);
      sel = elm_entry_selection_get(ad->edit_buffer);
      if (sel)
	{
	  Eina_Strbuf *buf2 = eina_strbuf_new();
	  eina_strbuf_append(buf2, sel);
	  eina_strbuf_replace_first(buf2, fmt_close, "");
	  elm_entry_entry_insert(ad->edit_buffer,
				 eina_strbuf_string_get(buf2));
	  eina_strbuf_free(buf2);
	}
    }
  elm_entry_select_none(ad->edit_buffer);
  elm_entry_cursor_pos_set(ad->edit_buffer, cursor);

 all_done:
  _edit_buffer_insert(ad->edit_buffer, eina_strbuf_string_get(buf));
  eina_strbuf_free(buf);
}

static void
_autosave_change_cb(void *data, Evas_Object *obj, void *event)
{
  App_Data *ad = data;
  Eina_Bool state = elm_check_state_get(obj);

  elm_entry_autosave_set(ad->edit_buffer, state);
  if (state) elm_entry_file_save(ad->edit_buffer);
}

static void
_edit_dblclick_cb(void *data, Evas_Object *obj, void *event)
{
  int current_cursor;

  current_cursor = elm_entry_cursor_pos_get(obj);

  while (elm_entry_cursor_prev(obj))
    {
      const char *content;
      if (obj.cursor_is_visible_format_get())
	break;
      content = obj.cursor_content_get();
      if (content && (content[0] == ' '))
	break;
    }

  if (current_cursor == obj.cursor_pos_get())
    return;

  obj.cursor_next();
  obj.cursor_selection_begin();
  obj.cursor_pos_set(current_cursor);
  while (obj.cursor_next())
    {
      const char *content;
      if (obj.cursor_is_visible_format_get())
	break;
      content = obj.cursor_content_get();
      if (content && (content[0] == ' '))
	break;
    }
  obj.cursor_selection_end();
}

static void
_edit_tplclick_cb(void *data, Evas_Object *obj, void *event)
{
  obj.cursor_line_begin_set();
  obj.cursor_selection_begin();
  obj.cursor_line_end_set(j);
  obj.cursor_selection_end();
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  App_Data app;

  memset(&app, 0, sizeof(app));

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("entry-example", "Emacs Lite"));
  win.autodel_set(true);

  ::elm_box box(efl::eo::parent = win);
  box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(box);
  box.visibility_set(true);

  ::elm_box tb(efl::eo::parent = win);
  tb.horizontal_set(true);
  tb.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
  tb.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx.pack_end(tb);
  tb.visibility_set(true);

  ::elm_check o(efl::eo::parent = win);
  o.state_set(false);
  elm_object_text_set(o._eo_ptr(), "Autosave"); // XXX
  tb.pack_end(o);
  o.visibility_set(true);

  o.callback_changed_add(&_autosave_change_cb);

  ::elm_button bt(efl::eo::parent = win);
  elm_object_text_set(bt._eo_ptr(), "b"); // XXX
  tb.pack_end(bt);
  bt.visibility_set(true);

  bt.callback_clicked_add(&_format_change_cb);

  ::elm_button bt2(efl::eo::parent = win);
  elm_object_text_set(bt2._eo_ptr(), "em"); // XXX
  tb.pack_end(bt3);
  bt3.visibility_set(true);

  bt2.callback_clicked_add(&_format_change_cb);

  ::elm_button bt3(efl::eo::parent = win);
  tb.pack_end(bt3);
  bt3.visibility_set(true);

  ::elm_layout icon(efl::eo::parent = win);

  if (!icon.theme_set("entry", "emoticon/haha", "default"))
    fprintf(stderr, "Failed to set layout");

  bt3.content_set("icon", icon); // XXX

  bt3.callback_clicked_add(_image_insert_cb);

  ::elm_entry en(efl::eo::parent = win);
  en.autosave_set(false);
  en.file_set("/tmp/da_test.txt", ELM_TEXT_FORMAT_MARKUP_UTF8);
  en.size_hint_weight_set( EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  en.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box.pack_end(en);
  en.visibility_set(true);

  app.win = win;
  app.edit_buffer = en;

  en.callback_clicked_double_add(&_edit_dblclick_cb);
  en.callback_clicked_triple_add(&_edit_tplclick_cb);

  App_Data aux = app.edit_buffer;
  aux.focus_set(true);

  win.evas::object::size_set(300, 780);

  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
