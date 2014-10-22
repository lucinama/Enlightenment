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
#include <elm_segment_control.eo.hh>
#include <elm_icon.eo.hh>

#include <Eina.hh>

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   	int count, idx;

   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  	::elm_win win(elm_win_util_standard_add("segment_control", "Segment Control Example"));
  	win.autodel_set(true);

  	::elm_segment_control sc(efl::eo::parent = win);
  	sc.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  	win.resize_object_add(sc);
  	sc.visibility_set(true);

	//	sc.item_add(NULL, "only text");    // XXX

	::elm_icon ic(efl::eo::parent = win);
   	ic.standard_set("close");
   	sc.item_add(ic, NULL);
   
	::elm_icon ic2(efl::eo::parent = win);
   	ic2.standard_set("home");
   	sc.item_add(ic2, "Home");

	::elm_icon ic3(efl::eo::parent = win);
   	ic3.standard_set("close");
   	sc.item_add(ic3, "");

   	count = sc.item_count_get();
   	//sc.item_insert_at(NULL , "Inserted at", count - 1);

	::elm_segment_control seg_it(efl::eo::parent = win);
   	//seg_it = sc.item_insert_at(NULL, "To be deleted", 2);
   	seg_it.del();

   	//sc.item_insert_at(NULL, "To be deleted", 2);
   	sc.item_del_at(2);

   	//seg_it = sc.item_get(0);
   	//elm_object_item_text_set(seg_it._eo_ptr(), "Only Text"); // XXX

   	count = sc.item_count_get();
   	//seg_it = sc.item_get(count / 2);
   	//seg_it.item_selected_set(true);
   	//seg_it = sc.item_selected_get();
   	//idx = seg_it.item_index_get();
   	std::cout << "Item selected: "<< idx << std::endl;

	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()
