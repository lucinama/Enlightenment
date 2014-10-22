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

#include <Evas.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

namespace efl { namespace evas {
    using ::evas::canvas;
    using ::evas::rectangle;
  } }

static void _print_items(void *data, Evas_Object *obj, void *event_info);
static void _free(void *data, Evas_Object *obj, void *event_info);
static void _add_item(void *data, Evas_Object *obj, void *event_info);

static void
_clear_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
  if (!data) return;
  elm_hoversel_clear((Evas_Object *)data);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("hoversel", "Hoversel"));
  win.autodel_set(true);

  efl::evas::rectangle rect(efl::eo::parent = win);
  rect.color_set( 255, 0, 0, 255);
  rect.visibility_set(true);

  ::elm_hoversel hoversel(efl::eo::parent = win);
  hoversel.horizontal_set(EINA_FALSE);
  elm_object_text_set(hoversel._eo_ptr(), "Add an item to Hoversel"); // XXX
  hoversel.content_set("icon", rect);  // XXX
  hoversel.item_add("Print items", NULL, ELM_ICON_NONE, _print_items, NULL);
  hoversel.item_add( "Option 2", "home", ELM_ICON_STANDARD, NULL,NULL);
  hoversel.callback_clicked_add(&_add_item);

  hoversel.evas::object::size_set(180, 30);
  hoversel.position_set( 10, 10);
  hoversel.visibility_set(true);

  ::elm_button btn(efl::eo::parent = win);		
  elm_object_text_set(btn._eo_ptr(), "Clear all Items"); // XXX
  btn.callback_clicked_add(&_clear_btn_clicked_cb);
  btn.evas::object::size_set(180, 30);
  btn.position_set(10, 50);
  btn.visibility_set(true);

  win.evas::object::size_set(200, 300);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()

static void
_print_items(void *data, Evas_Object *obj, void *event_info)
{
  const Eina_List *items = elm_hoversel_items_get(obj);
  const Eina_List *l;
  Elm_Object_Item *hoversel_it;

  EINA_LIST_FOREACH(items, l, hoversel_it)
    printf("%s\n", elm_object_item_text_get(hoversel_it));
}

static void
_add_item(void *data, Evas_Object *obj, void *event_info)
{
  static int num = 0;
  char *str = malloc(sizeof(char) * 10);
  Elm_Object_Item *hoversel_it;

  snprintf(str, 10, "item %d", ++num);

  hoversel_it = elm_hoversel_item_add(obj, str, NULL, ELM_ICON_NONE, NULL,
				      str);
  elm_object_item_del_cb_set(hoversel_it, _free);
}

static void
_free(void *data, Evas_Object *obj, void *event_info)
{
  free(data);
}
