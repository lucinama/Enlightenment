#include <stdio.h>
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <Eo.h>
#include "simple.eo.h"

typedef struct
{
  int cb_count;
} Simple_Public_Data;

typedef struct
{
  int x;
} Private_Data;

#define MY_CLASS SIMPLE_CLASS

static void
_simple_x_set(Eo *obj, Private_Data *pd, int x)
{
  pd->x = x;
  printf("%s %s %d\n", eo_class_name_get(MY_CLASS), __func__, pd->x);

  eo_do(obj, eo_event_callback_call(SIMPLE_EVENT_X_CHANGED, &pd->x));
}

Eina_Bool
_cb_added(void *data, Eo *obj, const Eo_Event_Description *_simple_event_desc, void *event_info)
{
  Simple_Public_Data *pd = eo_data_scope_get(obj, MY_CLASS);
  Eo_Callback_Array_Item *callback_array = event_info;
  (void) data;
  (void) _simple_event_desc;
  
  if (callback_array->desc != SIMPLE_EVENT_X_CHANGED)
    return EINA_TRUE;

  pd-> cb_count++;

  printf("Added SIMPLE_EVENT_X_CHANGED callback to %p. Count: %d\n", obj, pd->cb_count);
  return EO_CALLBACK_CONTINUE;
}

Eina_Bool
_cb_deled(void *data, Eo *obj, const Eo_Event_Description *_simple_event_desc, void *event_info)
{
  Simple_Public_Data *pd = eo_data_scope_get(obj, MY_CLASS);
  const Eo_Callback_Array_Item *callback_array = event_info;
  (void) data;
  (void) _simple_event_desc;
  
  if (callback_array->desc != SIMPLE_EVENT_X_CHANGED)
    return EINA_TRUE;

  pd->cb_count--;

  printf("Removed SIMPLE_EVENT_X_CHANGED callback from %p. Count: %d\n", obj,pd->cb_count);
  return EO_CALLBACK_CONTINUE;
}

static void
_simple_eo_base_constructor(Eo *obj, Private_Data *pd)
{
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  eo_do_super(obj, MY_CLASS, eo_constructor());

  eo_do(obj, eo_event_callback_add(EO_BASE_EVENT_CALLBACK_ADD, _cb_added, NULL));
  eo_do(obj, eo_event_callback_add(EO_BASE_EVENT_CALLBACK_DEL, _cb_deled, NULL));

  eo_do(obj, eo_key_data_set("cb_count",(intptr_t) 0, NULL));
}

#include "simple.eo.c"

