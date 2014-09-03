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

void
_item_1_pressed(::elm_button bt, Eo_Event_Description const& desc EINA_UNUSED, void *info)
{
  bt.text_set("elm.text", "Print Document");
}

void
_item_2_pressed(::elm_button bt, Eo_Event_Description const& desc EINA_UNUSED, void *info)
{
  bt.text_set("elm.text", "Create new folder");
}

void
_item_3_pressed(::elm_button bt, Eo_Event_Description const& desc EINA_UNUSED, void *info)
{
   /* This function won't be called because we disabled item that call it */
  bt.text_set("elm.text", "Create and send email");
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
  tb.shrink_mode_set(ELM_TOOLBAR_SHRINK_SCROLL);
  tb.size_hint_weight_set(0.0, 0.0);
  tb.size_hint_align_set(EVAS_HINT_FILL, 0.0);
  tb.visibility_set(true);
 
  // elm_toolbar_item_append(tb, "document-print", "Print", _item_1_pressed, bt);
  //  elm_toolbar_item_append(tb, "folder-new", "New Folder", _item_2_pressed, bt);

  tb.item_append("document-print", "label.Print", _item_1_pressed, bt);
  tb.item_append("icon.folder-new",  "label.New Folder", _item_2_pressed, bt);

  //  tb_it = elm_toolbar_item_append(tb, "mail-send", "Create and send email", _item_3_pressed, bt);
  tb_it = tb.item_append("icon.mail-send", "label.Create and send email", _item_3_pressed, bt);
  tb_it.disabled_set(true);
  tb.homogeneous_set(true);
  
  bx.pack_end(tb);
  bx.pack_end(bt);
  
  win.evas::object::size_set(200, 200);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
  
}
ELM_MAIN()




