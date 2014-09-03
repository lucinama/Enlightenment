#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define EFL_BETA_API_SUPPORT 1

#include <Eo.h>
#include "simple.eo.h"

typedef struct
{
  int x;
} Private_Data;

static int cb_count = 0;

static Eina_Bool
_null_cb(void *data, Eo *obj, const Eo_Event_Description *_simple_event_desc, void *event_info)
{
  (void) _simple_event_desc;
  (void) obj;
  (void) data;
  (void) event_info;
  return EO_CALLBACK_CONTINUE;
}

static Eina_Bool
_x_changed_cb(void *data, Eo *obj, const Eo_Event_Description *_simple_event_desc, void *event_info)
{
  (void) _simple_event_desc;
  (void) obj;
  int x = *((int*) event_info);
  printf("%s event_info: '%d' data:'%d'\n", __func__, x, (int) (intptr_t) data);
  
  cb_count++;

  eo_do(obj, eo_event_callback_priority_add(SIMPLE_EVENT_X_CHANGED, EO_CALLBACK_PRIORITY_BEFORE, _null_cb, (void *) 500));
  eo_do(obj, eo_event_callback_del(SIMPLE_EVENT_X_CHANGED, _null_cb, (void *) 500));

  return cb_count;
}

int main(int argc, char *argv[])
{
  (void) argc;
  (void) argv;
  eo_init();
  
  printf("XXX-1\n");
  Eo *obj = eo_add(SIMPLE_CLASS, NULL);
  printf("XXX-2\n");

  Private_Data x;  

  Private_Data *pd =  eo_data_scope_get(obj, SIMPLE_CLASS);
  
  eo_do(obj, eo_event_callback_priority_add(SIMPLE_EVENT_X_CHANGED, EO_CALLBACK_PRIORITY_BEFORE, _x_changed_cb, (void *) 1));
  eo_do(obj, eo_event_callback_priority_add(SIMPLE_EVENT_X_CHANGED, EO_CALLBACK_PRIORITY_DEFAULT, _x_changed_cb, (void *) 2));
  
  eo_do(obj, simple_x_set(10));
  printf("Valor de x alterado\n");
  printf("cb_count: %d\n\n", cb_count);
 
  eo_do(obj, simple_x_set(2));
  printf("Novo valor para x\n");
  printf("cb_count: %d\n\n", cb_count);

  eo_do(obj, simple_x_set(23));
  printf("X recebe novamente outro valor x\n");
  printf("cb_count: %d\n\n", cb_count);

  eo_do(obj, simple_x_set(70));
  printf("X com novo valor\n");
  printf("cb_count: %d\n\n", cb_count);

  eo_do(obj, eo_event_callback_del(SIMPLE_EVENT_X_CHANGED, _x_changed_cb, (void *) 1));
  eo_do(obj, eo_event_callback_del(SIMPLE_EVENT_X_CHANGED, _x_changed_cb, (void *) 2));

  eo_unref(obj); 
  eo_shutdown();
  printf("cb_count: %d\n\n", cb_count);

  return 0;
}
