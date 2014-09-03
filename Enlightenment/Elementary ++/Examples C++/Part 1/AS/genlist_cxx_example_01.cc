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

#include <sstream>

#include <elm_win.eo.hh>
#include <elm_genlist.eo.hh>
#include <elm_label.eo.hh>

#include <Eina.hh>

#define N_ITEMS 30

static Elm_Genlist_Item_Class *_itc = NULL;

static char *
_item_label_get(void* data, ::elm_label obj, Eo_Event_Description const& desc, void* info)
{
   //char buf[256];
   //snprintf(buf, sizeof(buf), "Item # %i", (int)(long)data);
   //return strdup(buf);
std::stringstream ss;
  ss << "Item # " << (int)(long)data;
return strdup(ss.str());  //XXXX
}

static Evas_Object *
_item_content_get(void *data, Evas_Object *obj, const char *part)
{
Evas_Object *ic = elm_icon_add(obj);

if (!strcmp(part, "icon"))
  elm_icon_standard_set(ic, "clock");

evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
return ic;
}

static void
_item_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
printf("sel item data [%p] on genlist obj [%p], item pointer [%p]\n",
	 data, obj, event_info);
}


EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  int i;
   
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("genlist", "Genlist"));
  win.autodel_set(true);

  if (!_itc)
    {
      _itc = elm_genlist_item_class_new();
      _itc->item_style = "default";
      _itc->func.text_get = _item_label_get;
      _itc->func.content_get = _item_content_get;
      _itc->func.state_get = NULL;
      _itc->func.del = NULL;
    }

  ::elm_genlist list(efl::eo::parent = win);

  for (i = 0; i < N_ITEMS; i++)
    {
      list.item_append(_itc, (void *)(long)i, NULL, ELM_GENLIST_ITEM_NONE, _item_sel_cb, NULL);
    }

  list.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(list);
  list.visibility_set(true);

  win.evas::object::size_set(320, 320);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
  
}
ELM_MAIN()
