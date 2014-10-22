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
#include <elm_icon.eo.hh>

#include <iostream>

#include <Eina.hh>

#define TABLE "example/table"
#define BOX "example/box"
#define TITLE "example/title"
#define SWALLOW "example/custom"

static const char *images[] = { "home", "close", "arrow_up", "arrow_down", NULL };

struct _App {
     int current;
};

static void
_signal_cb(::elm_layout o, Eo_Event_Description const& desc, void* info)
{
   struct _App *app = data;
   Evas_Object *icon = o.content_get("elm.swallow.content");

   std::cout << "signal received" << std::endl;

   if (!strcmp("elm,action,back", emission))
     app->current--;
   else if (!strcmp("elm,action,next", emission))
     app->current++;

   if (app->current < 0)
     app->current = (sizeof(images) / sizeof(images[0])) - 2;
   else if (images[app->current] == NULL)
     app->current = 0;

   elm_icon_standard_set(icon, images[app->current]);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   struct _App app;

   app.current = 0;

   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	::elm_win win(elm_win_util_standard_add("layout", "Layout"));
  	win.autodel_set(true);

  	// Adding layout and filling it with widgets
   	::elm_layout layout(efl::eo::parent = win);
    layout.size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(layout);
  	if (!layout.theme_set("layout", "application", "content-back-next"))
		fprintf(stderr, "Failed to set layout");
   	layout.visibility_set(true);
   
   	
   	::elm_icon icon(efl::eo::parent = win);
	icon.standard_set()images[app.current]);
   	icon.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  	layout.content_set("elm.swallow.content", icon);
	 
   	layout.signal_callback_elm_action_back_add(&_signal_cb);
   	layout.signal_callback_elm_action_next_add(&_signal_cb);
  	
  	win.evas::object::size_set(320, 320);
  	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()
