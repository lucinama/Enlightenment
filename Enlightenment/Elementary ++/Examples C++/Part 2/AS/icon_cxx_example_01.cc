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
#include <elm_icon.eo.hh>

#include <Eina.hh>

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   	const char *path, *group, *name;

   	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	::elm_win win(elm_win_util_standard_add("icon", "Icon"));
	win.autodel_set(true);

 	::elm_icon icon(efl::eo::parent = win);
   	icon.order_lookup_set(ELM_ICON_LOOKUP_THEME_FDO);
   	icon.standard_set("home");
 	
   	icon.file_get();
   	name = icon.standard_get(&path, &group);
   	std::cout << "path = " << ", group = " ", name = " << path << group << name << std::endl;

   	icon.no_scale_set(true);
   	icon.resizable_set(false, true);
   	icon.smooth_set(false);
   	icon.fill_outside_set(true);

   	icon.size_hint_weight_set(icon, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   	win.resize_object_add(icon);
   	icon.visibility_set(true);

   	win.evas::object::size_set(320, 320);
   	win.visibility_set(true);

   	elm_run();
   	elm_shutdown();

   	return 0;
}
ELM_MAIN()
