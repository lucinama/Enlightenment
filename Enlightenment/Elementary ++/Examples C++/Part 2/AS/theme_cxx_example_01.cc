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
#include <elm_theme.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_text.h"
#include "elm_interface_scrollable.h"
}

#include <Elementary.hh>

#include <elm_win.eo.hh>
#include <elm_box.eo.hh>
#include <elm_button.eo.hh>

#include <Eina.hh>

static void
btn_extension_click_cb(::elm_button btn, Eo_Event_Description const& desc, void* info)
{
    const char *lbl = btn.text_get();   // XXX

   if (!strncmp(lbl, "Load", 4))
     {
       elm_theme_extension_add("./theme_example.edj");
       elm_object_text_set(btn._eo_ptr(), "Unload extension"); // XXX
     }
   else if (!strncmp(lbl, "Unload", 6))
     {
       elm_theme_extension_del("./theme_example.edj");
       elm_object_text_set(btn._eo_ptr(), "Load extension"); // XXX
     }
}

static void
btn_style_click_cb(::elm_button btn, Eo_Event_Description const& desc, void* info)
{
   const char *styles[] = {
        "chucknorris",
        "default",
        "anchor"
   };
   static int sel_style = 0;

   sel_style = (sel_style + 1) % 3;
   btn.style_set(styles[sel_style]);
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   	elm_theme_extension_add("./theme_example.edj");

 	::elm_win win(elm_win_util_standard_add("theme", "Theme example"));
  	win.autodel_set(true);

  	::elm_box box(efl::eo::parent = win);
  	box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  	win.resize_object_add(box);
  	box.visibility_set(true);

  	::elm_button btn(efl::eo::parent = win);
   	elm_object_text_set(btn._eo_ptr(), "Unload extension"); // XXX
   	box.pack_end(btn);
   	btn.visibility_set(true);
   	btn.callback_clicked_add(&btn_extension_click_cb);

  	::elm_button btn2(efl::eo::parent = win);
   	elm_object_text_set(btn2._eo_ptr(), "Switch style"); // XXX
   	btn2.style_set("chucknorris");
   	box.pack_end(btn2);
   	btn2.visibility_set(true);
   	btn2.callback_clicked_add(&btn_style_click_cb);

   	win.evas::object::size_set(300, 320);
   	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()
