#ifdef HAVE_CONFIG_H
# include <elementary_config.h>
#endif

extern "C"
{
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
#include <pthread.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_text.h"
#include "elm_interface_scrollable.h"
}

#include <Elementary.hh>
#include <Eina.hh>

#include <iostream>

#define N_ITEMS 30

static Elm_Genlist_Item_Class *_itc = NULL;

static char *
_item_label_get(void *data, Evas_Object *obj, const char *part)
{
  time_t t = (time_t)ecore_time_unix_get();
  char buf[256];
  int i = (int)(long)data;

  if (!strcmp(part, "elm.text"))
    snprintf(buf, sizeof(buf), "Item # %i", i);
  else
    {
      int n;
      snprintf(buf, sizeof(buf), "created at %s", ctime(&t));
      n = strlen(buf);
      buf[n - 1] = '\0';
    }

  return strdup(buf);
}

static Evas_Object *
_item_content_get(::elm_icon ic, Evas_Object *obj, const char *part)
{
  if (!strcmp(part, "icon"))
    elm_icon_standard_set(ic, "clock");

  return ic;
}

static void
_item_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
  printf("sel item data [%p] on genlist obj [%p], item pointer [%p]\n",
	 data, obj, event_info);
}

static Evas_Object *
_genlist_add(::elm_box box)
{
  ::elm_list list(efl::eo::parent = box.parent_widget_get());
  list.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  list.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  box.pack_end(list);
  list.visibility_set(true);

  return list;
}

static void
_genlist_fill(::elm_list list)
{
  int i;

  for (i = 0; i < N_ITEMS; i++)
    {
      list.item_append(_itc, (void *)(long)i, NULL, ELM_GENLIST_ITEM_NONE, _item_sel_cb, NULL);  // XXX
    }
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  ::elm_win win(elm_win_util_standard_add("genlist", "Genlist"));
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
  win.autodel_set(true);
		
  ::elm_box box(efl::eo::parent = win);
  box.horizontal_set(true);
  box.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(box);
  box.visibility_set(true);

  if (!_itc)
    {
      _itc = elm_genlist_item_class_new();
      _itc->item_style = "double_label";
      _itc->func.text_get = _item_label_get;
      _itc->func.content_get = _item_content_get;
      _itc->func.state_get = NULL;
      _itc->func.del = NULL;
    }

  ::elm_list list;

  list = _genlist_add(box);
  _genlist_fill(list);

  list = _genlist_add(box);
  list.mode_set(ELM_LIST_LIMIT);
  _genlist_fill();

  list = _genlist_add(box);
  list.mode_set(ELM_LIST_COMPRESS);
  list._genlist_fill(list);

  win.evas::object::size_set(800, 320);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()

