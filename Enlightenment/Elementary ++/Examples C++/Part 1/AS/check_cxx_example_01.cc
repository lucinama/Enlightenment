#include <iostream>

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
}

#include <elm_win.eo.hh>
#include <elm_check.eo.hh>

#include <Eina.hh>
#include <Evas.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

void
_print(void *data, ::elm_check obj, Eo_Event_Description const& desc, void* info)
{
  //  printf("check %smarked\n", *((Eina_Bool*)data) ? "" : "un");
  assert(!!data);
  bool is_checked = *static_cast<bool*>(data);
  std::cout << (is_checked ? "" : "un") << "marked" << std::endl;
}

namespace efl { namespace evas {
    using ::evas::canvas;
    using ::evas::rectangle;
  } }

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  
  Eina_Bool value;
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
 
  ::elm_win win(elm_win_util_standard_add("check", "Check"));
  win.autodel_set(true);

  ::elm_check cb(efl::eo::parent = win);
  cb.text_set("elm.text", "checkbox");
  cb.state_pointer_set(&value);
  // evas_object_smart_callback_add(cb, "changed", _print, &value);
  cb.callback_changed_add(&_print);
  cb.position_set(10, 10);
  cb.size_set(200, 30);
  cb.visibility_set(true);

  efl::evas::rectangle icon(efl::eo::parent = win);
  icon.color_set( 0, 255, 0, 255);
  icon.size_set(20, 20);
  icon.visibility_set(true);

  ::elm_check cb2(efl::eo::parent = win);
  cb2.text_set("elm.text", "another checkbox");
  cb2.state_set(true);
  cb2.content_set("icon", icon);   //XXXX
  cb2.position_set(10, 50);
  cb2.size_set(200, 30);
  cb2.visibility_set(true);
 
  win.size_set(200, 100);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();
 
  return 0;
  
}
ELM_MAIN()
