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

#define BIN_DIR  "/usr/bin"
#define LIB_DIR  "/usr/lib"
#define DATA_DIR "/usr/local/share/elementary"

#define WIDTH             300
#define HEIGHT            300

struct test_data
{
   Evas_Object *btn;
   Eina_Bool    btn_enabled;
   Eina_Bool    btn_gets_focus;
};

struct test_data d = {NULL, EINA_TRUE, EINA_TRUE};

static void
_btn_enabled_cb(void *data, Evas_Object *obj, void *event)
{
   elm_object_disabled_set(d.btn, !d.btn_enabled);
}

static void
_btn_focus_cb(void *data,Evas_Object *obj,void *event)
{
   elm_object_focus_set(d.btn, EINA_TRUE);
}

static void
_btn_unfocus_cb(void *data,Evas_Object *obj, void *event)
{
   elm_object_focus_set(d.btn, EINA_FALSE);
}

static void
_btn_focus_allow_cb(void *data,Evas_Object *obj,void *event)
{
   elm_object_focus_allow_set(d.btn, d.btn_gets_focus);
}

static void
_btn_scale_cb(void *data,Evas_Object *obj, void *event)
{
   elm_object_scale_set(d.btn, elm_slider_value_get(obj));
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   elm_app_compile_bin_dir_set(BIN_DIR);
   elm_app_compile_data_dir_set(DATA_DIR);
   elm_app_compile_lib_dir_set(LIB_DIR);
   elm_app_info_set(elm_main, "elementary", "images/logo.png");

   fprintf(stdout, "prefix was set to: %s\n", elm_app_prefix_dir_get());
   fprintf(stdout, "data directory is: %s\n", elm_app_data_dir_get());
   fprintf(stdout, "library directory is: %s\n", elm_app_lib_dir_get());
   fprintf(stdout, "locale directory is: %s\n", elm_app_locale_dir_get());

	::elm_win win(elm_win_util_standard_add("top-level-funcs-example",
                                   "Elementary Top-level Functions Example");

	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
	win.autodel_set(true);
	
 	::elm_box bx(efl::eo::parent = win);
	bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(bx);
   	bx.visibility_set(true);

 	::elm_frame frame(efl::eo::parent = win);
   elm_object_text_set(frame._eo_ptr(), "Button"); // XXX
   frame.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   frame.visibility_set(true);
   bx.pack_end(frame);

 	::elm_button dbtn(efl::eo::parent = win);
 	elm_object_text_set(dbtn._eo_ptr(), "Click me"); // XXX
 	 elm_object_content_set(frame._eo_ptr(), dbtn._eo_ptr(); // XXX
   fprintf(stdout, "Elementary's finger size is set to %d pixels\n.",
           elm_config_finger_size_get());
   	dbtn.visibility_set(true);

 	::elm_box b(efl::eo::parent = win);
 	b.horizontal_set(false);
	b.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	box.resize_object_add(b);
   	b.visibility_set(true);

 	::elm_check check(efl::eo::parent = win);
	check.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	check.size_hint_align_set(0.0, 0.0);
	elm_object_text_set(check._eo_ptr(), "Button enabled"); // XXX
	   check.state_pointer_set(&d.btn_enabled);
   check.callback_changed_add(&_btn_enabled_cb);
     	box.resize_object_add(check);
   	check.visibility_set(true);

	::elm_button bt(efl::eo::parent = win);
   bt.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      bt.size_hint_align_set(0.0, 0.0);
     elm_object_text_set(bt._eo_ptr(), "Focus top button"); // XXX
   bt.callback_clicked_add(&_btn_focus_cb);
   box.pack_end(bt);
   bt.visibility_set(true);

	::elm_button bt2(efl::eo::parent = win);
   bt2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      bt2.size_hint_align_set(0.0, 0.0);
     elm_object_text_set(bt2._eo_ptr(), "Unfocus top button"); // XXX
   bt2.callback_clicked_add(&_btn_unfocus_cb);
   box.pack_end(bt2);
   bt2.visibility_set(true);

 	::elm_check check2(efl::eo::parent = win);
	check2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	check2.size_hint_align_set(0.0, 0.0);
	elm_object_text_set(check2._eo_ptr(), "Button gets focus"); // XXX
	   check2.state_pointer_set(&d.btn_gets_focus);
   check2.callback_changed_add(&_btn_focus_allow_cb);
     	box.resize_object_add(check2);
   	check2.visibility_set(true);

	::elm_slider slider(efl::eo::parent = win);
   slider.min_max_set(0, 4);
   slider.unit_format_set("%1.1f");
   sliderindicator_format_set(slider, "%1.1f");
   slider.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   slider.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   slider.callback_changed_add(&_btn_scale_cb);
  box.pack_end(slider);
  slider.visibility_set(true);

   win.evas::object::size_set(WIDTH, HEIGHT);
   win.focus_highlight_enabled_set(true);
   win.visibility_set(true);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
