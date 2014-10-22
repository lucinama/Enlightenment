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
#include <elm_icon.eo.hh>
#include <elm_check.eo.hh>
#include <elm_separator.eo.hh>
#include <elc_fileselector.eo.hh>

#include <Eina.hh>

#include <iostream>

static void
_fs_done(::elm_fileselector fs, Eo_Event_Description const& desc, void *info)
{
   const char *selected = info;
   
   const char *sel = selected ? selected : "*none!*";

   std::cout << "We're done! Selected file is: " << sel << std::endl;

   elm_exit();
}

static void
_fs_selected(::elm_fileselector fs, Eo_Event_Description const& desc, void *info)
{
   const char *selected = info;

   std::cout << "There's been a selection: " << selected << std::endl;
}

static void
_is_save_clicked(::elm_fileselector fs, Eo_Event_Description const& desc, void *info)
{
  //Evas_Object *fs = data;
   bool old_val = fs.is_save_get();

	bool val = old_val ? "Disabling" : "Enabling";

   std::cout << val << " text entry with selected item's name" << std::endl;

   fs.is_save_set(!old_val);
}

static void
_folder_only_clicked(::elm_fileselector fs, Eo_Event_Description const& desc, void *info)
{
  //Evas_Object *fs = data;
   bool old_val = fs.folder_only_get();

	bool val = old_val ? "Disabling" : "Enabling";

   std::cout << val << " folder-only mode" << std::endl;
          
   fs.folder_only_set(!old_val);
}

static void
_expandable_clicked(::elm_fileselector fs, Eo_Event_Description const& desc, void *info)
{
  //Evas_Object *fs = data;
   bool old_val = fs.expandable_get();

	bool val = old_val ? "Disabling" : "Enabling";

   std::cout << val << " tree-view mode" << std::endl;
          
	fs.expandable_set(!old_val);
}

static void
_sel_get_clicked(::elm_fileselector fs, Eo_Event_Description const& desc, void *info)
{
  //Evas_Object *fs = data;
   std::cout << "Current selection is: " << fs.selected_get() << std::endl;
}

static void
_path_get_clicked(::elm_fileselector fs, Eo_Event_Description const& desc, void *info)
{
  //Evas_Object *fs = data;
   std::cout << "Current selection's directory path is: "<< fs.path_get()<< std::endl;
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   setlocale(LC_ALL, "");

   elm_need_ethumb();
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	::elm_win win(elm_win_util_standard_add("fileselector", "File Selector Example"));
  	win.autodel_set(true);

 	::elm_box bx(efl::eo::parent = win);
 	bx.horizontal_set(true);
	bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(bx);
   	bx.visibility_set(true);

 	::elm_box vbox(efl::eo::parent = win);
	vbox.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	vbox.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   	vbox.visibility_set(true);
	bx.pack_end(vbox);

	::elm_fileselector fs(efl::eo::parent = win);
	fs.is_save_set(true);
	fs.expandable_set(false);
   	fs.path_set("/tmp");
   	fs.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	fs.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
	vbox.pack_end(fs);
	fs.visibility_set(true);

   	fs.callback_done_add(&_fs_done);
   	fs.callback_selected_add(&_fs_selected);

   	::elm_separator sep(efl::eo::parent = win);
   	sep.horizontal_set(true);
  	vbox.pack_end(sep);
	sep.visibility_set(true);

 	::elm_box buttons_bx(efl::eo::parent = win);
	buttons_bx.horizontal_set(true);
   	vbox.pack_end(buttons_bx);
   	buttons_bx.visibility_set(true);
   	
   	::elm_check ck(efl::eo::parent = win);
   	elm_object_text_set(ck._eo_ptr(), "editable selection"); 	// XXX
   	ck.state_set(fs.is_save_get());
   	ck.callback_changed_add(&_is_save_clicked);
   	buttons_bx.pack_end(ck);
   	ck.visibility_set(true);
   	
   	::elm_check ck2(efl::eo::parent = win);
   	elm_object_text_set(ck2._eo_ptr(), "folders only"); 	// XXX
   	ck2.state_set(fs.folder_only_get());
   	ck2.callback_changed_add(&_folder_only_clicked);
   	buttons_bx.pack_end(ck2);
   	ck2.visibility_set(true);
   	
   	::elm_check ck3(efl::eo::parent = win);
   	elm_object_text_set(ck3._eo_ptr(), "expandable"); 	// XXX
	ck3.state_set(fs.expandable_get());
   	ck3.callback_changed_add(&_expandable_clicked);
   	buttons_bx.pack_end(ck3);
   	ck3.visibility_set(true);
   	
  	::elm_box buttons_bx2(efl::eo::parent = win);
	buttons_bx2.horizontal_set(true);
   	vbox.pack_end(buttons_bx2);
   	buttons_bx2.visibility_set(true);
	      	
 	::elm_button bt(efl::eo::parent = win);
   	elm_object_text_set(bt._eo_ptr(), "Print selection"); 	// XXX
   	bt.callback_clicked_add(&_sel_get_clicked);
   	buttons_bx2.pack_end(bt);
   	bt.visibility_set(true);
   	
   	::elm_button bt2(efl::eo::parent = win);
   	elm_object_text_set(bt2._eo_ptr(), "Print path"); 	// XXX
   	bt2.callback_clicked_add(&_path_get_clicked);
   	buttons_bx2.pack_end(bt2);
   	bt2.visibility_set(true);
   	
   	::elm_separator sep2(efl::eo::parent = win);
   	sep2.horizontal_set(false);
  	bx.pack_end(sep2);
	sep2.visibility_set(true);

	::elm_fileselector fs2(efl::eo::parent = win);
	fs2.is_save_set(true);
	fs2.mode_set(ELM_FILESELECTOR_GRID);
	fs2.buttons_ok_cancel_set(false);
   	fs2.path_set("/tmp");
   	
   	fs2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	fs2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
	bx.pack_end(fs2);
	fs2.visibility_set(true);

   	win.evas::object::size_set(800, 600);
   	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()
