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
#include <elm_box.eo.hh>
#include <elm_button.eo.hh>
#include <elm_image.eo.hh>

#include <Eina.hh>

struct clean_ref
{
  clean_ref(efl::eo::base base)
    : _ref(base._eo_ptr())
  {}

  template <typename T>
  void operator()(T const&, Eo_Event_Description const&, void*) const
  {
    if(_ref)
      eo_unref(_ref);
  }

  Eo* _ref;
};

static void
on_click(::elm_button obj, Eo_Event_Description const* desc, void *info)
{
  elm_exit();
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   
  ::elm_win win(elm_win_util_standard_add("Greetings", "Hello, World!"));
  win.autodel_set(true);

  ::elm_button btn(efl::eo::parent = win);
  btn.text_set("elm.text","Good-Bye, World!");
  btn.callback_clicked_add(&on_click);
  btn.size_set(120, 30);
  btn.position_set(60, 15);
  btn.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  btn.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  btn.visibility_set(true);

  win.evas::object::size_set(240, 60);
  win.visibility_set(true);

  win.release();
  
  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
