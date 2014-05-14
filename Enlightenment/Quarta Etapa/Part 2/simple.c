#include <stdio.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <Eo.h>
#include "simple.eo.h"
#include "interface.eo.h"

typedef struct
{
  int x,y;
} Simple_Data;

#define MY_CLASS SIMPLE_CLASS

static void
_simple_xy_get(Eo *obj EINA_UNUSED, Simple_Data *pd, int*x, int* y)
{
  *x = pd->x;
  *y = pd->y;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
}

static void
_simple_xy_set(Eo *obj EINA_UNUSED, Simple_Data *pd, int x, int y)
{
  pd->x = x;
  pd->y = y;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
}

int
_simple_interface_mxy_get(Eo *obj EINA_UNUSED, Simple_Data *pd)
{
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  return pd->x * pd->y; 
}

#include "simple.eo.c"

