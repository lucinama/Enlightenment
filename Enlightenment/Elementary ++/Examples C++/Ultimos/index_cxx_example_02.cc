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

static const char *items[] =
{
   "Judith",
   "Paulina",
   "Cathy",
   "Vendella",
   "Naomi",
   "Ashley",
   "Stacey",
   "Gail"
};

static void
_index_changed(void        *data,
               Evas_Object *obj,
               void        *event_info)
{
   Elm_Object_Item *item = elm_object_item_data_get(event_info);
   elm_gengrid_item_bring_in(item, ELM_GENGRID_ITEM_SCROLLTO_IN);
}

static char *
_grid_label_get(void        *data,
                Evas_Object *obj,
                const char  *part)
{
   int idx = (int)(uintptr_t)data;
   return strdup(items[idx]);
}

Evas_Object *
_grid_content_get(void        *data,
                  Evas_Object *obj,
                  const char  *part)
{
   if (!strcmp(part, "elm.swallow.icon"))
     {
        char buf[PATH_MAX];
        snprintf(buf, sizeof(buf), "%s/images/%s", elm_app_data_dir_get(),
                 "sky_01.jpg");

        Evas_Object *icon = elm_bg_add(obj);
        elm_bg_file_set(icon, buf, NULL);
        evas_object_size_hint_aspect_set(icon, EVAS_ASPECT_CONTROL_VERTICAL, 1,
                                         1);
        evas_object_show(icon);
        return icon;
     }

   return NULL;
}

static int
_index_icmp(const void *data1, const void *data2)
{
   const char *label1, *label2;

   const Elm_Object_Item *index_it1 = data1;
   const Elm_Object_Item *index_it2 = data2;

   label1 = indexit1.item_letter_get();
   label2 = indexit2.item_letter_get();

   return strcasecmp(label1, label2);
}

EAPI_MAIN int
elm_main(int    argc,
         char **argv)
{
   Elm_Object_Item *gg_it;
   unsigned int i;

   Elm_Gengrid_Item_Class gic;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_app_info_set(elm_main, "elementary", "images");

	::elm_win win(elm_win_util_standard_add("index", "Index Example"));
	win.autodel_set(true);

	::elm_gengrid grid(efl::eo::parent = win);
     grid.item_size_set(150, 150);

   gic.item_style = "default";
   gic.func.text_get = _grid_label_get;
   gic.func.content_get = _grid_content_get;
   gic.func.state_get = NULL;
   gic.func.del = NULL;

   grid.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   win.resize_object_add(grid);
   grid.visibility_set(true);

	::elm_index idx(efl::eo::parent = win);
   idx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   win.resize_object_add(idx);
   idx.visibility_set(true);

   for (i = 0; i < (sizeof(items) / sizeof(items[0])); i++)
     {
        char buf[32];

        gg_it = elm_gengrid_item_append(grid, &gic, (void *)(uintptr_t)i, NULL, NULL);  // XXX

        snprintf(buf, sizeof(buf), "%c", items[i][0]);
        idx.item_sorted_insert(buf, NULL, gg_it, _index_icmp, NULL);  // XXX
     }

   idx.callback_delay_changed_add(&_index_changed);

   idx.autohide_disabled_set(EINA_FALSE);
   idx.level_go(0);

   win.evas::object::size_set(320, 300);
   win.visibility_set(true);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
