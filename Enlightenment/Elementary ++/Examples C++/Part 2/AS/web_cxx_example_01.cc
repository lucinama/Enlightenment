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
#include <elm_web.eo.hh>

#include <Eina.hh>

#include <iostream>


#define _GNU_SOURCE
#ifdef HAVE_ELEMENTARY_WEB
#include <EWebKit.h>
#endif

#define URL "http://www.enlightenment.org"

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
   	/* The program will proceed only if Ewebkit library is available. */
   	if (elm_need_web() == false)
     	return -1;

   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

 	::elm_win win(elm_win_add("Elementary Webkit Widget", ELM_WIN_BASIC);
  	win.autodel_set(true);
   	
   	::elm_web web(efl::eo::parent = win);   	
   	web.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	web.window_create_hook_set();
   	win.resize_object_add(web);
   	web.history_enabled_set(false);

   	if (!elm_web_url_set(web, URL))
    {
        std::cout << "URL NOT LOADED";
        return -1;
    }
   	web.visibility_set(true);

  	win.evas::object::size_set(720, 600);
   	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()

