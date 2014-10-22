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
#include <elm_layout.eo.hh>
#include <elm_button.eo.hh>
#include <elm_icon.eo.hh>

#include <Eina.hh>

#define TABLE "example/table"
#define BOX "example/box"
#define TITLE "example/title"
#define SWALLOW "example/custom"

static int _box_buttons = 0;

static void
_tbl_btn_cb(::elm_button btn, Eo_Event_Description const& desc, void* info)
{
   //Evas_Object *layout = data;

  	::elm_layout layout(efl::eo::parent = win);
   	layout.table_unpack(layout, TABLE, btn);
   	btn.del(btn);
}

static void
_box_btn_cb(::elm_button btn, Eo_Event_Description const& desc, void* info)
{
   // Evas_Object *layout = data;

   	snprintf(buf, sizeof(buf), "Button %02d", _box_buttons++);

  	::elm_box item(efl::eo::parent = layout);
   	//item = elm_button_add(elm_object_parent_widget_get(layout));
   	elm_object_text_set(item._eo_ptr(), buf); // XXX
   	item.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	item.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   	layout.box_insert_before(BOX, item, btn);
   	item.callback_clicked_add(&_box_btn_cb);
   	item.visibility_set(true);
}

static void
_swallow_btn_cb(::elm_button item, Eo_Event_Description const& desc, void* info)
{
   //Evas_Object *layout = data;
  
   layout.table_clear(TABLE, true);
   layout.box_remove_all(BOX, true);
   item = layout.content_unset(SWALLOW); // XXX
   item.del();
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   	Evas_Object *item;

   	elm_app_info_set(elm_main, "elementary", "examples/layout_example.edj");
   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	::elm_win win(elm_win_util_standard_add("layout", "Layout"));
  	win.autodel_set(true);

   	// Adding layout and filling it with widgets
   	::elm_layout layout(efl::eo::parent = win);
    layout.size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(layout);
   	snprintf(buf, sizeof(buf), "%s/examples/layout_example.edj", elm_app_data_dir_get());
   	layout.file_set(buf, "example/mylayout");
   	layout.visibility_set(true);

   	// Setting title
   	const char *title = layout.data_get("title");
   	if (title)
    {
        win.title_set(title);
    	elm_object_part_text_set(TITLE, title); // XXX
    }

   // Add icon, clock and button to the table
    ::elm_icon icon(efl::eo::parent = win);
	icon.standard_set("home");
   	icon.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	icon.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   	layout.table_pack(TABLE, icon, 0, 0, 1, 1);
   	icon.visibility_set(true);

  	::elm_icon icon2(efl::eo::parent = win);
	icon2.standard_set("close");
   	icon2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	icon2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   	layout.table_pack(TABLE, icon2, 1, 0, 1, 1);
   	icon2.visibility_set(true);

  	::elm_clock clk(efl::eo::parent = win);
   	clk.size_hint_weight_set(clk, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	clk.size_hint_align_set(clk, EVAS_HINT_FILL, EVAS_HINT_FILL);
   	layout.table_pack(TABLE, clk, 2, 0, 1, 1);
    clk.visibility_set(true);

    ::elm_button bt(efl::eo::parent = win);
	elm_object_text_set(bt._eo_ptr(), "Click me!"); // XXX
   	bt.size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	bt.size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   	layout.table_pack(layout, TABLE, bt, 0, 1, 3, 1);
   	bt.callback_clicked_add(&_tbl_btn_cb);
   	bt.visibility_set(true);

   	::elm_button item(efl::eo::parent = win);
   	elm_object_text_set(item._eo_ptr(), "Position 0"); // XXX
   	item.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	item.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   	layout.box_insert_at(BOX, item, 0);
   	item.callback_clicked_add(&_box_btn_cb);
   	item.visibility_set(true);

	::elm_button item2(efl::eo::parent = win);
   	elm_object_text_set(item2._eo_ptr(), "Prepended"); // XXX
   	item2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	item2.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   	layout.box_prepend(BOX, item2);
   	item.callback_clicked_add(&_box_btn_cb);
   	item.visibility_set(true);

    ::elm_button bt2(efl::eo::parent = win);
	elm_object_text_set(bt2._eo_ptr(),  "Delete All"); // XXX
 	layout.content_set(SWALLOW, bt2); // XXX
   	bt2.callback_clicked_add(&_swallow_btn_cb);
   	
  	win.evas::object::size_set(320, 320);
  	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()
