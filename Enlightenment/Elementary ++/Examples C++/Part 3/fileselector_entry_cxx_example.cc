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
#include <elm_check.eo.hh>
#include <elm_icon.eo.hh>
#include <elm_separator.eo.hh>
#include <elc_fileselector_entry.eo.hh>

#include <Eina.hh>

#include <iostream>

// static void
// _file_chosen(Eo_Event_Description const& desc, void *info)
// {
//   //const char *file = info;

//    if (file)
//      std::cout << "File chosen: " << file << std::endl;
//    else
//      std::cout << "File selection canceled." << std::endl;
// }

// static void
// _inwin_mode_toggle(::elm_fileselector_entry fs_entry, Eo_Event_Description const& desc, void *info)
// {
//    Evas_Object *fs_entry = data;
//    bool old_val = fs_entry.inwin_mode_get();
   
//    bool val = old_val ? "false" : "true";

//    fs_entry.inwin_mode_set(!old_val);
//    std::cout << "Inwin mode set to: " << val << std::endl;
// }

// static void
// _current_sel_toggle(::elm_fileselector_entry fs_entry, Eo_Event_Description const& desc, void *info)
// {
//    Evas_Object *fs_entry = data;
//    bool old_val = fs_entry.is_save_get(fs_entry);
//    fs_entry.is_save_set(!old_val);
   
//    bool val = old_val ? "Disabling" : "Enabling";

//    std::cout << val << " text entry with selected item's name" << std::endl;  
// }

// static void
// _folder_only_toggle(::elm_fileselector_entry fs_entry, Eo_Event_Description const& desc, void *info)
// {
//    Evas_Object *fs_entry = data;
//    bool old_val = fs_entry.folder_only_get();
//    fs_entry.folder_only_set(!old_val);
   
//    bool val = old_val ? "false" : "true";

//    std::cout << "Folder only mode set to: " << val << std::endl;
// }

// static void
// _expandable_toggle(::elm_fileselector_entry fs_entry, Eo_Event_Description const& desc, void *info)
// {
//    Evas_Object *fs_entry = data;
//    bool old_val = fs_entry.expandable_get(fs_entry);
//    fs_entry.expandable_set(!old_val);
   
//    bool val = old_val ? "false" : "true";

//    std::cout << "Expandable folders mode set to: " << val << std::endl;
// }

EAPI_MAIN int
elm_main (int argc, char *argv[])
{	
	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	::elm_win win(elm_win_util_standard_add("fileselector-entry", "File Selector Entry Example"));
  	win.autodel_set(true);

 	::elm_box vbox(efl::eo::parent = win);
	vbox.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(vbox);
   	vbox.visibility_set(true);

 	::elm_icon ic(efl::eo::parent = win);
 	ic.standard_set("file");
 	ic.size_hint_aspect_set(EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);

 	::elm_fileselector_entry fs_entry(efl::eo::parent = win);
   	fs_entry.path_set("/tmp");
   	elm_object_text_set(fs_entry._eo_ptr(), "Select a file"); // XXX
   	fs_entry.content_set("button icon", ic);		// XXX
   	
   	vbox.pack_end(fs_entry);
   	fs_entry.visibility_set(true);
   	ic.visibility_set(true);
   	
   	::elm_separator sep(efl::eo::parent = win);
   	sep.horizontal_set(true);
  	vbox.pack_end(sep);
	sep.visibility_set(true);

 	::elm_box hbox(efl::eo::parent = win);
	hbox.horizontal_set(true);
   	vbox.pack_end(hbox);
   	hbox.visibility_set(true);

	::elm_check ck(efl::eo::parent = win);
   	elm_object_text_set(ck._eo_ptr(), "editable selection"); 	// XXX
   	ck.state_set(fs_entry.is_save_get());
   	//ck.callback_changed_add(&_current_sel_toggle);
   	hbox.pack_end(ck);
   	ck.visibility_set(true);

	::elm_check ck2(efl::eo::parent = win);
   	elm_object_text_set(ck2._eo_ptr(), "\"inwin\" mode"); 	// XXX
   	ck2.state_set(fs_entry.inwin_mode_get());
   	//ck2.callback_changed_add(&_inwin_mode_toggle);
   	hbox.pack_end(ck2);
   	ck2.visibility_set(true);

	::elm_check ck3(efl::eo::parent = win);
   	elm_object_text_set(ck3._eo_ptr(),"folders only"); 	// XXX
   	ck3.state_set(fs_entry.folder_only_get());
   	//ck3.callback_changed_add(&_folder_only_toggle);
   	hbox.pack_end(ck3);
   	ck3.visibility_set(true);

	::elm_check ck4(efl::eo::parent = win);
   	elm_object_text_set(ck4._eo_ptr(),"expandable"); 	// XXX
   	ck4.state_set(fs_entry.expandable_get());
   	//ck4.callback_changed_add(&_expandable_toggle);
   	hbox.pack_end(ck4);
   	ck4.visibility_set(true);
   	
   	//fs_entry.callback_file_chosen_add(&_file_chosen);

   	win.evas::object::size_set(400, 400);
   	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()
