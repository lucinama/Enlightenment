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

#include <Eina.hh>

#include <elm_win.eo.hh>
#include <elm_map.eo.hh>
#include <elm_box.eo.hh>
#include <elm_button.eo.hh>

void
_bt_zoom_in(void* data, ::elm_map map, Eo_Event_Description const& desc EINA_UNUSED, void* info EINA_UNUSED)
{
  int zoom;
  map.zoom_mode_set(ELM_MAP_ZOOM_MODE_MANUAL);
  zoom = map.zoom_get();
  map.zoom_set(zoom + 1);
}

static void
_bt_zoom_out(void *data, ::elm_map map, Eo_Event_Description const& desc EINA_UNUSED, void *info EINA_UNUSED)
{
  int zoom;
  map.zoom_mode_set(ELM_MAP_ZOOM_MODE_MANUAL);
  zoom = map.zoom_get();
  map.zoom_set(zoom - 1);
}

void
_bt_zoom_fit(void *data, ::elm_map map, Eo_Event_Description const& desc EINA_UNUSED, void *info EINA_UNUSED)
{
  map.zoom_mode_set(ELM_MAP_ZOOM_MODE_AUTO_FIT);
}

void
_bt_zoom_fill(void *data, ::elm_map map, Eo_Event_Description const& desc EINA_UNUSED, void *info EINA_UNUSED)
{
  map.zoom_mode_set(ELM_MAP_ZOOM_MODE_AUTO_FILL);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{

  Eina_Bool value;
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("map", "Map Creation Example"));
  win.autodel_set(true);

  ::elm_map map(efl::eo::parent = win);
  map.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(map);
  map.visibility_set(true);

  ::elm_box box(efl::eo::parent = win);
  box.visibility_set(true);

  ::elm_button bt(efl::eo::parent = win);
  bt.text_set("elm.text", "+");
  box.pack_end(bt);
  bt.visibility_set(true);
  bt.callback_clicked_add(&_bt_zoom_in);

  ::elm_button bt2(efl::eo::parent = win);
  bt2.text_set("elm.text", "-");
  box.pack_end(bt2);
  bt2.visibility_set(true);
  bt2.callback_clicked_add(&_bt_zoom_out);

  ::elm_button bt3(efl::eo::parent = win);
  bt3.text_set("elm.text", "X");
  box.pack_end(bt3);
  bt3.visibility_set(true);
  bt3.callback_clicked_add(&_bt_zoom_fit);


  ::elm_button bt4(efl::eo::parent = win);
  bt4.text_set("elm.text", "#");
  box.pack_end(bt4);
  bt4.visibility_set(true);
  bt4.callback_clicked_add(&_bt_zoom_fill);

  map.zoom_set(12);
  map.region_show(-43.2, -22.9);
  
  win.evas::object::size_set(512, 512);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
