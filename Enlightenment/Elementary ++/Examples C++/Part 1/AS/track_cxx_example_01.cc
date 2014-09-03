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

#include <Eo.h>
#include <Evas.h>
#include <Elementary.h>
#include <elm_widget.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"

#include <elm_win.eo.hh>
#include <elm_list.eo.hh>

void
item_select_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Coord x, y, w, h;
   Eina_Bool visible;
   Elm_Object_Item *it = event_info;
   Evas_Object *track = elm_object_item_track(it);
   evas_object_geometry_get(track, &x, &y, &w, &h);

   visible = evas_object_visible_get(track);
   printf("track geometry = (%d %d %d %d) visible(%d)\n",
          x, y, w, h, visible);

   elm_object_item_untrack(it);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{

  unsigned int i;
  static const char *lbl[] =
    {
      "Sunday",
      "Monday",
      "Tuesday",
      "Wednesday",
      "Thursday",
      "Friday",
      "Saturday"
    };

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("track-example", "Track Example"));
  win.autodel_set(true);

  ::elm_list li(efl::eo::parent = win);
  li.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(li);

  for (i = 0; i < sizeof(lbl) / sizeof(lbl[0]); i++)
    li.item_append(lbl[i], NULL, NULL, item_select_cb, NULL);

  li.visibility_set(true);
  li.go();
 
  win.size_set(320, 240);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
  
}
ELM_MAIN()
