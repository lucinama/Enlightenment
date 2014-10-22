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
#include <Evas.hh>

#ifdef HAVE_ELEMENTARY_WEB
#include <EWebKit.h>
#endif

typedef struct _Tab_Data Tab_Data;

typedef struct
{
   Evas_Object *win;
   Evas_Object *main_box;
   Evas_Object *naviframe;
   Evas_Object *url_entry;
   Evas_Object *default_web;
   Evas_Object *tabs;
   Evas_Object *close_tab;
   Evas_Object *search_box;
   Evas_Object *search_entry;

   struct {
        Evas_Object *back;
        Evas_Object *fwd;
        Evas_Object *refresh;
   } nav;

   Tab_Data *current_tab;

   Eina_Bool exiting : 1;
} App_Data;

struct _Tab_Data
{
   Evas_Object *web;
   App_Data *app;
   Elm_Object_Item *tab;
};

static Evas_Object * _web_create_window_cb(void *data, Evas_Object *obj, Eina_Bool js, const Elm_Web_Window_Features *wf);

static void
nav_button_update(App_Data *ad)
{
   Eina_Bool back, fwd;

   back = !elm_web_back_possible_get(ad->current_tab->web);
   fwd = !elm_web_forward_possible_get(ad->current_tab->web);

   elm_object_disabled_set(ad->nav.back, back);
   elm_object_disabled_set(ad->nav.fwd, fwd);
}

static void
tab_current_set(Tab_Data *td)
{
   const char *url;

   if (td == td->app->current_tab)
     return;

   td->app->current_tab = td;

   url = elm_web_url_get(td->web);
   elm_object_text_set(td->app->url_entry, url);

   nav_button_update(td->app);
   elm_entry_icon_visible_set(td->app->url_entry, EINA_TRUE);

   elm_naviframe_item_simple_promote(td->app->naviframe, td->web);
}

static void
_tab_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
   Tab_Data *td = data;

   if (!td->tab)
     td->tab = event_info;
   tab_current_set(td);
}

static void
_title_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
   Tab_Data *td = data;
   const char *title = event_info;
   char buf[20] = "";

   if (title)
     strncpy(buf, title, sizeof(buf) - 1);
   elm_object_item_text_set(td->tab, buf);
}

static void
_url_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
   Tab_Data *td = data;
   const char *url = event_info;

   if (td != td->app->current_tab)
     return;

   nav_button_update(td->app);
   elm_object_text_set(td->app->url_entry, url);
}

static void
_web_free_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
   Tab_Data *td = data;

   if (td->tab)
     elm_object_item_del(td->tab);

   free(td);
}

static void
_tb_item_del_cb(void *data, Evas_Object *obj, void *event_info)
{
   Tab_Data *td = data;
   if (!td->app->exiting && !elm_toolbar_selected_item_get(obj))
     {
        td->app->current_tab = NULL;
        elm_entry_icon_visible_set(td->app->url_entry, EINA_FALSE);
        if (td->app->search_box)
          evas_object_del(td->app->search_box);
     }
   td->tab = NULL;
}

Tab_Data *
tab_add(App_Data *ad)
{
   Tab_Data *td;

   td = calloc(1, sizeof(Tab_Data));
   if (!td) return NULL;

::elm_web td->web(efl::eo::parent = ad->win);
   td->web.window_create_hook_set(_web_create_window_cb, ad);
   td->web.inwin_mode_set(EINA_TRUE);
   td->web.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   td->web.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_naviframe_item_simple_push(ad->naviframe, td->web);

   td->app = ad;
   td->tab = elm_toolbar_item_append(td->app->tabs, NULL, "New tab",
                                     _tab_clicked_cb, td);
   elm_object_item_del_cb_set(td->tab, _tb_item_del_cb);

   evas_object_data_set(td->web, "tab_data", td);

   evas_object_smart_callback_add(td->web, "title,changed", _title_changed_cb,
                                  td);
   evas_object_smart_callback_add(td->web, "url,changed", _url_changed_cb, td);
   evas_object_event_callback_add(td->web, EVAS_CALLBACK_FREE, _web_free_cb,
                                  td);

   elm_toolbar_item_selected_set(td->tab, EINA_TRUE);
   return td;
}

static char *
url_sanitize(const char *url)
{
   char *fixed_url;
   char *schema;
   char *tmp;

   if (!url || !*url) return NULL;

   tmp = strstr(url, "://");
   if (!tmp || (tmp == url) || (tmp > (url + 15)))
     {
        char *new_url = NULL;
        if (ecore_file_exists(url))
          {
             schema = "file";
             new_url = ecore_file_realpath(url);
          }
        else
          schema = "http";

        if (asprintf(&fixed_url, "%s://%s", schema, new_url ? new_url : url) >
            0)
          {
             free(new_url);
             return fixed_url;
          }
        free(new_url);
     }
   else
     return strdup(url);

   return NULL;
}

static void
tab_url_set(Tab_Data *td, const char *url)
{
   char *sane_url = url_sanitize(url);
   elm_web_url_set(td->web, sane_url);
   free(sane_url);
}

static void
_url_entry_activated_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;
   Tab_Data *td;
   const char *url = eina_stringshare_ref(elm_object_text_get(obj));

   if (!ad->current_tab)
     td = tab_add(ad);
   else
     td = ad->current_tab;
   tab_url_set(td, url);
   eina_stringshare_del(url);
}

static void
_nav_back_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;

   elm_web_back(ad->current_tab->web);
}

static void
_nav_refresh_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;
   const Evas_Modifier *mods = evas_key_modifier_get(evas_object_evas_get(obj));

   if (evas_key_modifier_is_set(mods, "Shift"))
     elm_web_reload_full(ad->current_tab->web);
   else
     elm_web_reload(ad->current_tab->web);
}

static void
_nav_fwd_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;

   elm_web_forward(ad->current_tab->web);
}

static void
_close_tab_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;

   if (!ad->current_tab)
     return;
   evas_object_del(ad->current_tab->web);
}

static void
_add_tab_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;
   tab_add(ad);
   elm_object_focus_set(ad->url_entry, EINA_TRUE);
}

static Evas_Object *
_web_create_window_cb(void *data, Evas_Object *obj, Eina_Bool js, const Elm_Web_Window_Features *wf)
{
   App_Data *ad = data;
   Tab_Data *td;

   td = tab_add(ad);
   return td->web;
}

static void
_win_del_request_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;
   ad->exiting = EINA_TRUE;
}

static void
_win_free_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
   free(data);
}

static void
_search_entry_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;
   const char *text;

   text = elm_object_text_get(obj);
   elm_web_text_search(ad->current_tab->web, text, EINA_FALSE, EINA_TRUE,
                       EINA_TRUE);
   elm_web_text_matches_unmark_all(ad->current_tab->web);
   elm_web_text_matches_mark(ad->current_tab->web, text, EINA_FALSE, EINA_TRUE,
                             0);
}

static void
_search_entry_activate_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;
   const char *text;

   text = elm_object_text_get(obj);
   elm_web_text_search(ad->current_tab->web, text, EINA_FALSE, EINA_TRUE,
                       EINA_TRUE);
}

static void
_search_next_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;
   const char *text;

   text = elm_object_text_get(ad->search_entry);
   elm_web_text_search(ad->current_tab->web, text, EINA_FALSE, EINA_TRUE,
                       EINA_TRUE);
}

static void
_search_prev_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;
   const char *text;

   text = elm_object_text_get(ad->search_entry);
   elm_web_text_search(ad->current_tab->web, text, EINA_FALSE, EINA_FALSE,
                       EINA_TRUE);
}

static void
_search_close_cb(void *data, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;
   evas_object_del(ad->search_box);
}

static void
_search_box_del_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
   App_Data *ad = data;
   ad->search_box = NULL;
   ad->search_entry = NULL;
}

static void
_win_search_trigger_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
   Evas_Event_Key_Down *ev = event_info;
   App_Data *ad = data;
  
   if (strcmp(ev->keyname, "f") ||
       !evas_key_modifier_is_set(ev->modifiers, "Control"))
     return;
   if (ad->search_box || !ad->current_tab)
     return;

   box = elm_box_add(ad->win);
   elm_box_horizontal_set(box, EINA_TRUE);
   evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_after(ad->main_box, box, ad->url_entry);
   evas_object_show(box);

   evas_object_event_callback_add(box, EVAS_CALLBACK_DEL, _search_box_del_cb,
                                  ad);

   entry = elm_entry_add(ad->win);
   elm_entry_single_line_set(entry, EINA_TRUE);
   elm_entry_scrollable_set(entry, EINA_TRUE);
   evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, entry);
   evas_object_show(entry);

   evas_object_smart_callback_add(entry, "changed", _search_entry_changed_cb,
                                  ad);
   evas_object_smart_callback_add(entry, "activated", _search_entry_activate_cb,
                                  ad);

   box2 = elm_box_add(ad->win);
   elm_box_horizontal_set(box2, EINA_TRUE);
   elm_object_part_content_set(entry, "end", box2);

   btn = elm_button_add(ad->win);
   elm_box_pack_end(box2, btn);
   evas_object_show(btn);

   ic = elm_icon_add(ad->win);
   elm_icon_standard_set(ic, "arrow_up");
   elm_object_part_content_set(btn, "icon", ic);

   evas_object_smart_callback_add(btn, "clicked", _search_prev_cb, ad);

   btn = elm_button_add(ad->win);
   elm_box_pack_end(box2, btn);
   evas_object_show(btn);

   ic = elm_icon_add(ad->win);
   elm_icon_standard_set(ic, "arrow_down");
   elm_object_part_content_set(btn, "icon", ic);

   evas_object_smart_callback_add(btn, "clicked", _search_next_cb, ad);

   btn = elm_button_add(ad->win);
   elm_box_pack_end(box, btn);
   evas_object_show(btn);

   ic = elm_icon_add(ad->win);
   elm_icon_standard_set(ic, "close");
   elm_object_part_content_set(btn, "icon", ic);

   evas_object_smart_callback_add(btn, "clicked", _search_close_cb, ad);

   ad->search_box = box;
   ad->search_entry = entry;

   elm_object_focus_set(entry, EINA_TRUE);
}

static void
default_content_set(Evas_Object *web)
{
#ifdef HAVE_ELEMENTARY_WEB
   Evas_Object *view, *frame;
   const char contents[] = ""
      "<html>\n"
      "  <head>\n"
      "    <title>Nothing to see here, move along</title>\n"
      "  </head>\n"
      "  <body>\n"
      "    <a href=\"http://www.enlightenment.org\" target=\"_blank\">E</a>\n"
      "    <br />\n"
      "    <a href=\"http://www.google.com\" target=\"_blank\">Google</a>\n"
      "    <br />\n"
      "  </body>\n"
      "</html>\n";

   view = elm_web_webkit_view_get(web);
   frame = ewk_view_frame_main_get(view);
   ewk_frame_contents_set(frame, contents, sizeof(contents) - 1, "text/html",
                          "UTF-8", NULL);
#else
   (void) web;
#endif
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
  Evas *e;
   Evas_Modifier_Mask ctrl_mask;
   App_Data *ad;

   if (!elm_need_web())
     return -1;

   ad = calloc(1, sizeof(App_Data));
   if (!ad) return -1;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   ::elm_win win(elm_win_util_standard_add("example-web", "Web Example"));
   win.autodel_set(EINA_TRUE);

   e = win.evas_get();
   ctrl_mask = evas_key_modifier_mask_get(e, "Control");
   if (!evas_object_key_grab(win, "f", ctrl_mask, 0, EINA_TRUE))
     fprintf(stderr, "Could not grab trigger for search dialog\n");

   win.callback_delete_request_add(&_win_del_request_cb);
   win.event_callback_add(EVAS_CALLBACK_KEY_DOWN, _win_search_trigger_cb, ad);
   win.event_callback_add(EVAS_CALLBACK_FREE, _win_free_cb, ad);

   ::elm_box box(efl::eo::parent = win);
   box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   win.resize_object_add(box);
   box.visibility_set(EINA_TRUE);
     
   ::elm_entry url_bar(efl::eo::parent = win);
   url_bar.single_line_set(EINA_TRUE);
   url_bar.scrollable_set(EINA_TRUE);
   url_bar.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
   url_bar.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   box.pack_end(url_bar);
   url_bar.visibility_set(EINA_TRUE);

   url_bar.callback_activated_add(&_url_entry_activated_cb);

   ::elm_box box2(efl::eo::parent = win);
   box2.horizontal_set(EINA_TRUE);
   url_bar.content_set("icon", box2);
   url_bar.icon_visible_set(EINA_FALSE);

   ::elm_button btn(efl::eo::parent = win);
   box2.pack_end(btn);
   btn.visibility_set(EINA_TRUE);

   ad->nav.back = btn;

   ::elm_icon ic(efl::eo::parent = win);
   ic.standard_set("arrow_left");
   btn.content_set("icon", ic);

   btn.callback_clicked_add(&_nav_back_cb);

   ::elm_button btn2(efl::eo::parent = win);
   box2.pack_end(btn2);
   btn2.visibility_set(EINA_TRUE);

   ad->nav.refresh = btn2;

   ::elm_icon ic2(efl::eo::parent = win);
   ic2.standard_set("refresh");
   btn2.content_set("icon", ic2);

   btn2.callback_clicked_add(&_nav_refresh_cb);

   ::elm_button btn3(efl::eo::parent = win);
   box2.pack_end(btn3);
   btn3.visibility_set(EINA_TRUE);

   ad->nav.fwd = btn3;

   ::elm_icon ic3(efl::eo::parent = win);
   ic3.standard_set("arrow_right");
   btn3.content_set("icon", ic3);
   
   btn3.callback_clicked_add(&_nav_fwd_cb);

   ::elm_box box3(efl::eo::parent = win);
   box3.horizontal_set(EINA_TRUE);
   box3.size_hint_weight_set(EVAS_HINT_EXPAND, 0.0);
   box3.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   box.pack_end(box3);
   box3.visibility_set(EINA_TRUE);

   ::elm_button btn4(efl::eo::parent = win);
   box3.pack_end(btn4);
   btn4.visibility_set(EINA_TRUE);

   ::elm_icon ic4(efl::eo::parent = win);
   ic4.standard_set("file");
   btn4.content_set("icon", ic4);

   btn4.callback_clicked_add(&_add_tab_cb);

   ::elm_toolbar tabs(efl::eo::parent = win);
   tabs.align_set(0.0);
   tabs.select_mode_set(ELM_OBJECT_SELECT_MODE_ALWAYS);
   tabs.homogeneous_set(EINA_FALSE);
   tabs.shrink_mode_set(ELM_TOOLBAR_SHRINK_MENU);
   tabs.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   tabs.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   box3.pack_end(tabs);
   tabs.visibility_set(EINA_TRUE);
 
   ::elm_button btn5(efl::eo::parent = win);
   box3.pack_end(btn5);
   btn5.visibility_set(EINA_TRUE);

   btn5.callback_clicked_add(&_close_tab_cb);

   ::elm_icon ic5(efl::eo::parent = win);
   ic5.standard_set("close");
   btn5.content_set("icon", ic5);

   ::elm_naviframe naviframe(efl::eo::parent = win);
   naviframe.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   naviframe.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   box.pack_end(naviframe);
   naviframe.visibility_set(EINA_TRUE);

   tabs.menu_parent_set(naviframe);

   ::elm_web web(efl::eo::parent = win);
   web.window_create_hook_set(_web_create_window_cb, ad);
   web.history_enabled_set(EINA_FALSE);
   web.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   web.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   naviframe.item_simple_push(web);

   default_content_set(web);

   ad->win = win;
   ad->main_box = box;
   ad->naviframe = naviframe;
   ad->url_entry = url_bar;
   ad->default_web = web;
   ad->tabs = tabs;
   ad->close_tab = btn5;

   win.evas::object::size_set(480, 640);
   win.visibility_set(EINA_TRUE);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
