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

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

namespace efl { namespace evas {
using ::evas::canvas;
using ::evas::rectangle;
} }

static void
_del_it(void *data, Evas_Object *obj, void *event_info)
{
   const Eina_List *l;
   Elm_Object_Item *menu_it = elm_menu_first_item_get(data);
   menu_it = elm_menu_item_next_get(menu_it);
l = elm_menu_item_subitems_get(menu_it);
elm_object_item_del(eina_list_data_get(l));
}

static void
_show(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
Evas_Event_Mouse_Down *ev = event_info;
elm_menu_move(data, ev->canvas.x, ev->canvas.y);
evas_object_show(data);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{

::elm_win win(elm_win_util_standard_add("menu", "Menu"));
win.autodel_set(true);
elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

efl::evas::rectangle rect(efl::eo::parent = win);
win.resize_object_add(rect);
rect.color_set( 0, 0, 0, 0);
rect.visibility_set(true);

::elm_menu menu(efl::eo::parent = win);
menu.item_add(NULL, NULL, "first item", NULL, NULL);
menu_it = menu.item_add( NULL, "mail-reply-all", "second item", NULL, NULL);

  menu.item_add(menu_it, "object-rotate-left", "menu 1", NULL, NULL);
::elm_button button(efl::eo::parent = win);
elm_object_text_set(button._eo_ptr(), "button - delete items");  // XXX
  menu_it1 = menu.item_add(menu_it, NULL, NULL, NULL, NULL);
elm_object_item_content_set(menu_it1._eo_ptr(), button._eo_ptr());    // XXX
   button.callback_clicked_add(&_del_it);
   menu.item_separator_add(menu_it);
   menu.item_add( menu_it, NULL, "third item", NULL, NULL);
   menu.item_add(menu_it, NULL, "fourth item", NULL, NULL);
   menu.item_add(menu_it, "window-new", "sub menu", NULL, NULL);

   menu_it = menu.item_add(NULL, NULL, "third item", NULL, NULL);
elm_object_item_disabled_set(menu_it, EINA_TRUE);   // XXX

   rect.event_callback_add(EVAS_CALLBACK_MOUSE_DOWN, _show, menu);
menu.visibility_set(true);

win.evas::object::size_set(250, 350);
win.visibility_set(true);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
