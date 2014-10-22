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
#include <elm_flipselector.eo.hh>

#include <Eina.hh>

#include <array>
#include <string>

 static const char *commands = \
                              "commands are:\n"
                              "\tn - flip to next item\n"
                              "\tp - flip to previous item\n"
                              "\tf - print first item's label\n"
                              "\tl - print last item's label\n"
                              "\ts - print selected item's label\n"
                              "\th - print help\n";

// void /* unselect the item shown in the flip selector */
// _unsel_cb(void        *data,
//           Evas_Object *obj,
//           void        *event_info)
// {
//    Elm_Object_Item *it;
//    Evas_Object *fp = data;

//    it = elm_flipselector_selected_item_get(fp);
//    elm_flipselector_item_selected_set(it, EINA_FALSE);
// }

// void /* delete the item shown in the flip selector */
// _del_cb(void        *data,
//         Evas_Object *obj,
//         void        *event_info)
// {
//    Elm_Object_Item *it;
//    Evas_Object *fp = data;

//    it = elm_flipselector_selected_item_get(fp);
//    if (it) elm_object_item_del(it);
// }

// void /* underflow callback */
// _underflow_cb(void        *data,
//               Evas_Object *obj,
//               void        *event_info)
// {
//    fprintf(stdout, "Underflow!\n");
// }

// void /* overflow callback */
// _overflow_cb(void        *data,
//              Evas_Object *obj,
//              void        *event_info)
// {
//    fprintf(stdout, "Overflow!\n");
// }

// static Eina_Bool
// _on_keydown(Evas_Object *object, Evas_Object *src, Evas_Callback_Type type, void *event_info)
// {
//    Evas_Object *fs = data;
//    Evas_Event_Key_Down *ev = event_info;

//    if (type != EVAS_CALLBACK_KEY_DOWN) return EINA_FALSE;

//    if (strcmp(ev->keyname, "h") == 0) /* print help */
//      {
//         fprintf(stdout, "%s", commands);
//      }
//    else if (strcmp(ev->keyname, "n") == 0) /* flip to next item */
//      {
//         elm_flipselector_flip_next(fs);

//         fprintf(stdout, "Flipping to next item\n");
//      }
//    else if (strcmp(ev->keyname, "p") == 0) /* flip to previous item */
//      {
//         elm_flipselector_flip_prev(fs);

//         fprintf(stdout, "Flipping to previous item\n");
//      }
//    else if (strcmp(ev->keyname, "f") == 0) /* print first item's label */
//      {
//         Elm_Object_Item *it;

//         it = elm_flipselector_first_item_get(fs);

//         fprintf(stdout, "Flip selector's first item is: %s\n", it ?
//                 elm_object_item_text_get(it) : "none");
//      }
//    else if (strcmp(ev->keyname, "l") == 0) /* print last item's label */
//      {
//         Elm_Object_Item *it;

//         it = elm_flipselector_last_item_get(fs);

//         fprintf(stdout, "Flip selector's last item is: %s\n", it ?
//                 elm_object_item_text_get(it) : "none");
//      }
//    else if (strcmp(ev->keyname, "s") == 0) /* print selected item's label */
//      {
//         Elm_Object_Item *it;

//         it = elm_flipselector_selected_item_get(fs);

//         fprintf(stdout, "Flip selector's selected item is: %s\n", it ?
//                 elm_object_item_text_get(it) : "none");
//      }
//    else
//      return EINA_FALSE;

//    ev->event_flags |= EVAS_EVENT_FLAG_ON_HOLD;
//    return EINA_TRUE;
// }

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   unsigned int i;
 	std::array<std::string, 8> labels =
    {
        "Elementary",
        "Evas",
        "Eina",
        "Edje",
        "Eet",
        "Ecore",
        "Efreet",
        "Eldbus"
     };

   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	::elm_win win(elm_win_util_standard_add("flipselector", "Flip Selector Example"));
  	win.autodel_set(true);

 	::elm_box bx(efl::eo::parent = win);
	bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(bx);
   	bx.visibility_set(true);

	::elm_flipselector fp(efl::eo::parent = win);
   	fp.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	//fp.callback_underflowed_add(&_overflow_cb);
   	//fp.callback_overflowed_add(&_underflow_cb);
   	for (std::string s : labels)
	  fp.item_append(s, NULL, NULL); // XXX
	bx.pack_end(fp);
	fp.visibility_set(true);

 	::elm_button bt(efl::eo::parent = win);
   	elm_object_text_set(bt._eo_ptr(), "Unselect item"); 	// XXX
   	//bt.callback_clicked_add(&_unsel_cb);
   	bx.pack_end(bt);
   	bt.visibility_set(true);

 	::elm_button bt2(efl::eo::parent = win);
   	elm_object_text_set(bt2._eo_ptr(), "Delete item");  	// XXX
   	//bt2.callback_clicked_add(&_del_cb);
   	bx.pack_end(bt2);
   	bt2.visibility_set(true);
   
   	//win.callback_clicked_add(&_on_keydown);
   	
  	win.visibility_set(true);

   	fprintf(stdout, "%s", commands);
   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()

