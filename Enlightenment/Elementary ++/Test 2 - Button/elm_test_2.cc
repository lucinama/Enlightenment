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

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  { 
    Evas_Object_Box_Layout last_layout;
    ::elm_win window(elm_win_util_standard_add("bg-plain", "My Background"));
    window.autodel_set(true);

    ::elm_box outer_box(efl::eo::parent = window);
    outer_box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    window.resize_object_add(outer_box);
    outer_box.visibility_set(true);
    window.callback_del_add(clean_ref(outer_box));

    ::elm_box small_box(efl::eo::parent = window);
    small_box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    small_box.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
    window.resize_object_add(small_box);
    outer_box.pack_end(small_box);
    small_box.visibility_set(true);
    window.callback_del_add(clean_ref(small_box));

    ::elm_image cute(efl::eo::parent = window);
    cute.fill_inside_set(true);
    cute.file_set("/home/luciana/Public/Enlightenment/cute_cat.jpeg", "image");
    cute.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    cute.size_hint_align_set(0.2,0.2);
    window.resize_object_add(cute);
    small_box.pack_end(cute);
    cute.visibility_set(true);
    window.callback_del_add(clean_ref(cute));
  
    ::elm_box buttons_box(efl::eo::parent = window);
    buttons_box.horizontal_set(true);
    buttons_box.size_hint_weight_set(0.2,0.2);
    buttons_box.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
    outer_box.pack_end(buttons_box);
    buttons_box.visibility_set(true);
    window.callback_del_add(clean_ref(buttons_box));

    ::elm_button button_1(efl::eo::parent = window);
    button_1.text_set("elm_text", "Button 1");
    button_1.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    button_1.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
    buttons_box.pack_end(button_1);
    button_1.visibility_set(true);
    window.callback_del_add(clean_ref(button_1));

    ::elm_button button_2(efl::eo::parent = window);
    button_2.text_set("elm_text", "Button 2");
    button_2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    button_2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
    buttons_box.pack_end(button_2);
    button_2.visibility_set(true);
    window.callback_del_add(clean_ref(button_2));

    window.size_set(1000,1000);
    window.visibility_set(true);

    window._release();
  }

  elm_run();
  elm_shutdown();

  return 0;

}
ELM_MAIN();
