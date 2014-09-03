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
#include "elm_interface_atspi_accessible.eo.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_widget_action.eo.h"

#include <elm_win.eo.hh>
#include <elm_toolbar.eo.hh>
#include <elm_box.eo.hh>
#include <elm_button.eo.hh>
#include <elm_menu.eo.hh>


static void
_item_pressed(void *data, Evas_Object *obj, void *event_info)
{
  ::elm_win win(elm_win_util_standard_add("toolbar", "Toolbar Example"));
  ::elm_toolbar tb_it(efl::eo::parent = win);
  tb_it.item_state_set(tb_it.item_state_next());
  tb_it.item_selected_set(false);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("toolbar", "Toolbar Example"));
  win.autodel_set(true);

  ::elm_box bx(efl::eo::parent = win);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);

  ::elm_button bt(efl::eo::parent = win);
  bt.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt.text_set("text", "Button");
  bt.visibility_set(true);

  ::elm_toolbar tb(efl::eo::parent = win);
  tb.size_hint_weight_set(0.0, 0.0);
  tb.size_hint_align_set(EVAS_HINT_FILL, 0.0);
  tb.visibility_set(true);

  tb.item_append("document-print", "Print", NULL, NULL);
  tb.item_append("folder-new", "Folder", NULL, NULL);
  tb.item_append("clock", "Clock", NULL, NULL);
  tb.item_append("refresh", "Update", NULL, NULL);

  tb.menu_parent_set(win);

::elm_toolbar tb_it(tb.item_append("mail-send", "Send Mail", NULL, NULL));
tb_it.item_menu_set(true);

 ::elm_menu menu(elm_toolbar_item_menu_get(tb_it));
menu.item_add(NULL, "emptytrash", "Empty Trash", NULL, NULL);
menu.item_add(NULL, "trashcan_full", "Full Trash", NULL, NULL);

  tb_it.standard_priority_set(10);
  
  bx.pack_end(tb);
  bx.pack_end(bt);
  
  win.size_set(230, 200);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
  
}
ELM_MAIN()
