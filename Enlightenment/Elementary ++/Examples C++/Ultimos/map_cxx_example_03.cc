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

#include <iostream>

typedef struct _Example_Data
{
   Evas_Object *map, *entry;
   Elm_Map_Route *route;
   double start_lon, start_lat, dest_lon, dest_lat;
   Elm_Map_Name *name;
   Elm_Map_Overlay *route_ovl;
} Example_Data;

static Example_Data example_data;

static void
_route_loaded(void *data, ::elm_map obj, void *ev)
{
   Example_Data *exam_data = data;

   exam_data->route_ovl = obj.overlay_route_add(exam_data->route);
   elm_map_overlay_color_set(exam_data->route_ovl, 0, 255, 0, 255);
}

static void
_name_loaded(void *data, ::elm_map map, void *ev)
{
   Example_Data *exam_data = data;
   Evas_Object *map = obj;

   if (exam_data->route)
     elm_map_route_del(exam_data->route);

   elm_map_name_region_get(exam_data->name, &(exam_data->dest_lon),
                           &(exam_data->dest_lat));

   exam_data->route = map.route_add(ELM_MAP_ROUTE_TYPE_FOOT,ELM_MAP_ROUTE_METHOD_SHORTEST,
                                        exam_data->start_lon, exam_data->start_lat,
                                        exam_data->dest_lon, exam_data->dest_lat,
                                        NULL, NULL);
}

static void
_bt_route(void *data, ::elm_map map, void *ev)
{
   Example_Data *exam_data = data;
   Evas_Object *map;
   char *address;

   map = exam_data->map;
   address = (char *)elm_object_text_get(exam_data->entry);

   exam_data->name = map.name_add(address, 0, 0, NULL, NULL);

   map.callback_name_loaded_add(&_name_loaded);
   map.callback_route_loaded_add(&_route_loaded);
}

static void
_bt_zoom_in(void *data, ::elm_map map, void *ev)
{
   int zoom;
   map.zoom_mode_set(ELM_MAP_ZOOM_MODE_MANUAL);
   zoom = data.zoom_get();
   map.zoom_set(zoom + 1);
}

static void
_bt_zoom_out(::elm_map data, void *ev)
{
   int zoom;
   data.zoom_mode_set(ELM_MAP_ZOOM_MODE_MANUAL);
   zoom = data.zoom_get();
   data.zoom_set(zoom - 1);
}

static void
_bt_zoom_fit(::elm_map data, Evas_Object *obj, void *event_info)
{
  data.zoom_mode_set(ELM_MAP_ZOOM_MODE_AUTO_FIT);
}

static void
_bt_zoom_fill(::elm_map data, Evas_Object *obj, void *event_info)
{
  data.zoom_mode_set(ELM_MAP_ZOOM_MODE_AUTO_FILL);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("map", "Map Route Example"));
  win.autodel_set(true);

  ::elm_map map(efl::eo::parent = win);
  map.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(map);
  map.visibility_set(true);

  ::elm_box box(efl::eo::parent = win);
  box.horizontal_set(true);
  box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(box);
  box.visibility_set(true);

  ::elm_button bt(efl::eo::parent = win);
  elm_object_text_set(bt._eo_ptr(), "+"); // XXX
  box.pack_end(bt);
  bt.visibility_set(true);
  bt.callback_clicked_add(&_bt_zoom_in);
  bt.size_hint_align_set(EVAS_HINT_FILL, 0);

  ::elm_button bt2(efl::eo::parent = win);
  elm_object_text_set(bt2._eo_ptr(), "-"); // XXX
  box.pack_end(bt2);
  bt2.visibility_set(true);
  bt2.callback_clicked_add(&_bt_zoom_out);
  bt2.size_hint_align_set(EVAS_HINT_FILL, 0);

  ::elm_button bt3(efl::eo::parent = win);
  elm_object_text_set(bt3._eo_ptr(), "X"); // XXX
  box.pack_end(bt3);
  bt3.visibility_set(true);
  bt3.callback_clicked_add(&_bt_zoom_fit);
  bt3.size_hint_align_set(EVAS_HINT_FILL, 0);

  ::elm_button bt4(efl::eo::parent = win);
  elm_object_text_set(bt4._eo_ptr(), "#"); // XXX
  box.pack_end(bt4);
  bt4.visibility_set(true);
  bt4.callback_clicked_add(&_bt_zoom_fill);
  bt4.size_hint_align_set(EVAS_HINT_FILL, 0);

  ::elm_entry entry(efl::eo::parent = win);
  entry.scrollable_set(true);
  entry.single_line_set(true);
  elm_object_text_set(entry._eo_ptr(), "Jockey Club Brasileiro"); // XXX
  entry.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  entry.size_hint_align_set(EVAS_HINT_FILL, 0);
  box.pack_end(entry);
  entry.visibility_set(true);

  ::elm_button bt5(efl::eo::parent = win);
  elm_object_text_set(bt5._eo_ptr(), "Route"); // XXX
  box.pack_end(bt5);
  bt5.visibility_set(true);
  bt5.callback_clicked_add(&_bt_route);
  bt5.size_hint_align_set(EVAS_HINT_FILL, 0);

  example_data.map = map;
  example_data.entry = entry;
  example_data.route = NULL;
  example_data.start_lon = -43.175;
  example_data.start_lat = -22.97;

  map.zoom_set(12);
  map.region_show(example_data.start_lon, example_data.start_lat);

  win.evas::object::size_set(512, 512);
  win.visibility_set(true);

  ecore_timer_add(0.5, _nasty_hack, win);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
