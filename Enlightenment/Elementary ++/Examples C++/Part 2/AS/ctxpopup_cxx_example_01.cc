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
}

#include <elm_win.eo.hh>
#include <elm_list.eo.hh>
#include <elm_ctxpopup.eo.hh>
#include <elm_image.eo.hh>
#include <elm_icon.eo.hh>

#include <istream>

static int list_mouse_down = 0;

static void
_dismissed_cb(::elm_ctxpopup obj, Eo_Event_Description const& desc, void* info)
{
   obj.del();
}

static void
_ctxpopup_item_cb(::elm_ctxpopup obj, Eo_Event_Description const& desc, void* info)
{
   std::cout << "ctxpopup item selected: " << elm_object_item_text_get(info) << std::endl;
}

Elm_Object_Item *item_new(Evas_Object *ctxpopup, const char * label, const char *icon)
{
   Evas_Object *ic = elm_icon_add(ctxpopup);
   elm_icon_standard_set(ic, icon);
   elm_image_resizable_set(ic, EINA_FALSE, EINA_FALSE);
   return elm_ctxpopup_item_append(ctxpopup, label, ic, _ctxpopup_item_cb, NULL);
}

static void
_list_item_cb(::elm_ctxpopup obj, Eo_Event_Description const& desc, void* info)
{
   Evas_Object *ctxpopup;
   Elm_Object_Item *it;
   Evas_Coord x,y;

   if (list_mouse_down > 0) return;

   ctxpopup = elm_ctxpopup_add(obj);
   evas_object_smart_callback_add(ctxpopup, "dismissed", _dismissed_cb, NULL);

   item_new(ctxpopup, "Go to home folder", "home");
   item_new(ctxpopup, "Save file", "file");
   item_new(ctxpopup, "Delete file", "delete");
   it = item_new(ctxpopup, "Navigate to folder", "folder");
   elm_object_item_disabled_set(it, EINA_TRUE);
   item_new(ctxpopup, "Edit entry", "edit");
   it = item_new(ctxpopup, "Set date and time", "clock");
   elm_object_item_disabled_set(it, EINA_TRUE);

   evas_pointer_canvas_xy_get(evas_object_evas_get(obj), &x, &y);
   evas_object_move(ctxpopup, x, y);
   evas_object_show(ctxpopup);

   elm_list_item_selected_set(event_info, EINA_FALSE);
}

static void
_list_item_cb2(::elm_list obj, Eo_Event_Description const& desc, void* info)
{
	Elm_Object_Item *it;
   	Evas_Coord x,y;

   if (list_mouse_down > 0) return;

   ctxpopup = elm_ctxpopup_add(obj);
   evas_object_smart_callback_add(ctxpopup, "dismissed", _dismissed_cb, NULL);
   elm_ctxpopup_horizontal_set(ctxpopup, EINA_TRUE);

   item_new(ctxpopup, NULL, "home");
   item_new(ctxpopup, NULL, "file");
   item_new(ctxpopup, NULL, "delete");
   item_new(ctxpopup, NULL, "folder");
   it = item_new(ctxpopup, NULL, "edit");
   elm_object_item_disabled_set(it, EINA_TRUE);
   item_new(ctxpopup, NULL, "clock");

   evas_pointer_canvas_xy_get(evas_object_evas_get(obj), &x, &y);
   evas_object_move(ctxpopup, x, y);
   evas_object_show(ctxpopup);

   list.item_selected_set(info, false);
}

static void
_list_mouse_down(::elm_list obj EINA_UNUSED, Eo_Event_Description const& desc EINA_UNUSED, void* info EINA_UNUSED)
{
   list_mouse_down++;
}

static void
_list_mouse_up(::elm_list obj EINA_UNUSED, Eo_Event_Description const& desc EINA_UNUSED, void* info EINA_UNUSED)
{
   list_mouse_down--;
}

static void
_win_del(::elm_list obj EINA_UNUSED, Eo_Event_Description const& desc EINA_UNUSED, void* info EINA_UNUSED)
{
   list_mouse_down = 0;
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
 
	::elm_win win(elm_win_util_standard_add("Contextual Popup", "Contextual Popup"));
	win.callback_delete_request_add(&_win_del);
	win.autodel_set(true);

 	::elm_list list(efl::eo::parent = win);
   	list.callback_mouse_down_add(&_list_mouse_down);
   	list.callback_mouse_up_add(&_list_mouse_up);,
	list.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(list);
  	list.mode_set(ELM_LIST_COMPRESS);

   	list.item_append("Ctxpopup with icons and labels", NULL, NULL,_list_item_cb, NULL); //XXXX
   	list.item_append("Ctxpopup with icons only", NULL, NULL,_list_item_cb2, NULL); 	//XXXX
   	list.visibility_set(true);
   	list.go();

   	evas::object::size(400, 400);
	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()
