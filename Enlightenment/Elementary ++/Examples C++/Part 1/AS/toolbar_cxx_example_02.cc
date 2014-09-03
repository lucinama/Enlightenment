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
#include "elm_interface_scrollable.h"

#include <elm_win.eo.hh>
#include <elm_toolbar.eo.hh>
#include <elm_box.eo.hh>
#include <elm_button.eo.hh>

#include <Eina.hh>

static void
_item_pressed(::elm_toolbar tb_it, Eo_Event_Description const& desc EINA_UNUSED, void* info)
{  
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
  bt.text_set("elm.text", "Button");
  bt.visibility_set(true);

  ::elm_toolbar tb(efl::eo::parent = win);
  tb.shrink_mode_set(ELM_TOOLBAR_SHRINK_SCROLL);
  tb.size_hint_weight_set(0.0, 0.0);
  tb.size_hint_align_set(EVAS_HINT_FILL, 0.0);
  tb.visibility_set(true);

  tb.item_append("document-print", "Print", NULL, NULL);
  tb.item_append("folder-new", "Folder", NULL, NULL);
  tb.item_append("clock", "Clock", NULL, NULL);
  tb.item_append("refresh", "Update", NULL, NULL);

  ::elm_toolbar tb_it(tb.item_append("mail-send", "Send Mail", _item_pressed, NULL));
  tb_it.item_state_add("emptytrash", "Empty Trash", _item_pressed, NULL);
  tb_it.item_state_add("trashcan_full", "Full Trash", _item_pressed, NULL);

  tb_it.standard_priority_set(10);
  
  bx.pack_end(tb);
  bx.pack_end(bt);
  
  win.evas::object::size_set(230, 200);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
  
}
ELM_MAIN()
