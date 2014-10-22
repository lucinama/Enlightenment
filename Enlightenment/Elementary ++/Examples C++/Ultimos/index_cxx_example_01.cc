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

#include <assert.h>

static const char *dict[] = \
{
#include "dict.txt"
};

static void
_index_item_del(void *data, Evas_Object *obj, void *event_info)
{
   fprintf(stdout, "Deleting index node (%s). Comparing index "
           "item data reported via callback with the one returned by "
           "index's API on items: %s.\n",
           elm_index_item_letter_get(event_info),
           data == elm_object_item_data_get(event_info) ? "OK" :
           "FAIL, something went wrong");
}

static void
_item_del(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *it = data.selected_item_get(0);

   if (!it) return;

   fprintf(stdout, "Deleting last selected index item, which had letter"
           " %s (pointing to %p)\n", elm_index_item_letter_get(it),
           elm_object_item_data_get(it));

   it.item_del();
   data.level_go(0);
}

static void
_item_del_all(void *data, Evas_Object *obj, void *event_info)
{
   data.item_clear(data);
   data.level_go(data, 0);
}

static void
_active_set(void *data, Evas_Object *obj, void *event_info)
{
   Eina_Bool disabled = data.autohide_disabled_get();
   data.autohide_disabled_set(!disabled);

   fprintf(stdout, "Toggling index programmatically to %s.\n",
           !disabled ? "On" : "Off");
}

static void
_index_changed(void *data, Evas_Object *obj, void *event_info)
{
   elm_list_item_bring_in(elm_object_item_data_get(event_info));
}

static void
_index_selected(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *lit = event_info;

   fprintf(stdout, "New index item selected. Comparing item reported"
           " via callback with the selection returned by the API: "
           "%s.\n", lit == elm_index_selected_item_get(obj, 0) ? "OK" :
           "FAIL, something went wrong");
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   Elm_Object_Item *lit;
   unsigned int i;
   char curr = 0;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	::elm_win win(elm_win_util_standard_add("index", "Index Example"));
	win.autodel_set(true);

	::elm_box vbox(efl::eo::parent = win);
   vbox.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
 win.resize_object_add(vbox);
   vbox.visibility_set(true);

	::elm_list list(efl::eo::parent = win);
   list.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   list.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   list.visibility_set(true);
   vbox.pack_end(list);

	::elm_index id(efl::eo::parent = win);
   id.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   win.resize_object_add(id);
   id.visibility_set(true);

   for (i = 0; i < (sizeof(dict) / sizeof(dict[0])); i++)
     {
        lit = elm_list_item_append(list, dict[i], NULL, NULL, NULL, NULL); // XXX

        if (curr != dict[i][0])
          {
             Elm_Object_Item *index_it;
             char buf[32];

             curr = dict[i][0];
             /* indexing by first letters */

             snprintf(buf, sizeof(buf), "%c", curr);
             index_it = elm_index_item_append(id, buf, NULL, lit);

             /* this is here just to demostrate the API call */
             (void)elm_index_item_find(id, lit);
             assert(elm_index_item_find(id, lit) == index_it);

             elm_object_item_del_cb_set(index_it, _index_item_del);
          }
     }

   id.callback_delay_changed_add(&_index_changed);
   id.callback_selected_add(&_index_selected);
   id.level_go(0);

	::elm_sepatator sep(efl::eo::parent = win);
   sep.horizontal_set(true);
   vbox.pack_end(sep);
   sep.visibility_set(true);

	::elm_box hbox(efl::eo::parent = win);
	hbox.horizontal_set(true);
   hbox.size_hint_weight_set(EVAS_HINT_EXPAND, 0);
   hbox.size_hint_fill_set(hbox, EVAS_HINT_FILL, EVAS_HINT_FILL);
 vbox.pack_end(hbox);
   hbox.visibility_set(true);

	::elm_button bt(efl::eo::parent = win);
    elm_object_text_set(bt._eo_prt(), "bring in index"); // XXX
   bt.callback_clicked_add(&_active_set);
   hbox.pack_end(bt);
  bt.visibility_set(true);

	::elm_button bt2(efl::eo::parent = win);
   elm_object_text_set(bt2._eo_prt(), "delete last selected item"); // XXX
   bt2.callback_clikced_add(&_item_del);
   hbox.pack_end(bt2);
   bt2.visibility_set(true);

	::elm_button bt3(efl::eo::parent = win);
   elm_object_text_set(bt3._eo_prt(), "delete all items"); // XXX
   bt3.callback_clicked_add(&_item_del_all);
   hbox.pack_end(bt3);
  bt3.visibility_set(true);

   win.evas::object::size_set(320, 600);
   win.visibility_set(true);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
