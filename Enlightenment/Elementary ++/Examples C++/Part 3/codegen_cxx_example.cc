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

extern "C"
{
#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"
#include "codegen_example_generated.h"
}

#include <elm_win.eo.hh>
#include <elm_button.eo.hh>
#include <elm_layout.eo.hh>

#include <Eina.hh>

#include <iostream>

#include <array>
#include <string>

#include <sstream>

static bool _btn_large = false;

static void
_swallow_btn_cb(::elm_button btn, Evas_Callback_Type type, void *info)
{
    if (_btn_large == false)
     {
        _btn_large = true;
        codegen_example_swallow_grow_emit(layout._eo_ptr()); // XXX
        elm_object_text_set(btn._eo_ptr(), "Reduce me!");  // XXX
        if (!layout.table_clear(true))
          fprintf(stderr, "Could not remove the items from the table!\n");
     }
   else
     {
        _btn_large = false;
        //layout.swallow_shrink_emit();
	codegen_example_swallow_shrink_emit(layout._eo_ptr()); // XXX
        elm_object_text_set(btn._eo_ptr(), "Enlarge me!"); // XXX
     }
}

static void
_size_changed_cb(::elm_layout layout, const char *emission, const char *source)
{
  Evas_Coord w, h;

   layout.sizing_eval();
   edje::object edje(layout.edje_get());
   edje.size_min_calc(&w, &h);
   std::cout << "Minimum size for this theme: "<< w << h << std::endl;
}

static Evas_Object *
_button_create(Evas_Object *parent, const char *label)
{
   Evas_Object *btn;
   btn = elm_button_add(parent);
   if (!btn) return NULL;

   elm_object_text_set(btn._eo_ptr(), label._eo_ptr()); // XXX
   btn.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   btn.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);

   return btn;
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
  Evas_Object *tbl_items[6];
  std::array<std::string, 6> labels = {"One", "Two", "Three", "Four", "Five", "Six"};
  
  elm_app_compile_data_dir_set("/home/luciana/Enlightenment/local/share/elementary/");
  elm_app_info_set(reinterpret_cast<void*>(elm_main), "elementary", "examples/codegen_example.edj");

 	::elm_win win(elm_win_util_standard_add("codegen", "Elementary CodeGen"));
  	win.autodel_set(true);

   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   	::elm_layout layout(efl::eo::parent = win);  
   	if (!layout)
    {
    	std::cout << "Could not create the layout" << std::endl;
        return -1;
    }

   layout.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   win.resize_object_add(layout);
   layout.visibility_set(true);

   layout.size_changed_callback_add(&_size_changed_cb);

   const char *title = layout.title_get();
   if (title)
     {
        win.title_set(title);
        layout.title_set(title);
     }

   btn = _button_create(win, "Enlarge me!");
   layout.custom_set(btn);
   btn.callback_clicked_add(&_swallow_btn_cb);

   for (i = 0; i < 6; i++)
     {
        tbl_items[i] = _button_create(win, labels[i]);
        if (i < 3)
          {
             if (!codegen_example_table_pack(layout, tbl_items[i], i, i, 1,1))
               fprintf(stderr, "Could not add the button to the table!\n");
          }
        else
          {
             if (!codegen_example_box_append(layout, tbl_items[i]))
               fprintf(stderr, "Could not add the button to the box!\n");
          }

       	tbl_items[i].visibility_set(true);
     }

   win.evas::object::size_set(500, 600);
   win.visibility_set(true);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
