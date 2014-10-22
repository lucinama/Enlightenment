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
#include <elm_win.eo.hh>
#include <elm_layout.eo.hh>
#include <elm_button.eo.hh>

#include <iostream>

#define TITLE "example/title"
#define SWALLOW "example/custom"

static bool _btn_large = false;

static void
_swallow_btn_cb(::elm_layout layout, Eo_Event_Description const& desc, void* info)
{
   // Evas_Object *layout = data;

   if (_btn_large == false)
     {
        _btn_large = true;
        layout.signal_emit("button,enlarge", "");
        elm_object_text_set(btn._eo_ptr(), "Reduce me!"); // XXX
     }
   else
     {
        _btn_large = false;
        layout.signal_emit("button,reduce", "");
        elm_object_text_set(btn._eo_ptr(), "Enlarge me!"); // XXX
     }
}

static void
_size_changed_cb(::elm_layout layout, Eo_Event_Description const& desc, void* info)
{
   Evas_Coord w, h;

   layout.sizing_eval();
   edje = layou.edje_get();
   edje.size_min_calc(&w, &h);
   std::cout << "Minimum size for this theme: " << w << " x " << h << std::endl;
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   elm_app_info_set(elm_main, "elementary", "examples/layout_example.edj");
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   ::elm_win win(elm_win_util_standard_add("layout", "Layout Example"));
  	win.autodel_set(true);

   	// Adding layout
    ::elm_layout layout(efl::eo::parent = win);
    layout.size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(layout);
   	snprintf(buf, sizeof(buf), "%s/examples/layout_example.edj", elm_app_data_dir_get());
   	layout.file_set(buf, "example/mylayout3");
   	layout.visibility_set(true);

   	layout.signal_callback_size_changed_add(&_size_changed_cb);

   	// Setting title
   	const char *title = layout.data_get("title");
   	if (title)
     {
        win.title_set(title);
        layout.text_set(TITLE, title);
     }

    ::elm_icon btn(efl::eo::parent = win);
   	elm_object_text_set(btn._eo_ptr(), "Enlarge me!"); // XXX
   	btn.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	btn.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   	layout.content_set(SWALLOW, btn);
   	btn.callback_clicked_add(&_swallow_btn_cb);

   	win.evas::object::size_set(160, 160);
  	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()
