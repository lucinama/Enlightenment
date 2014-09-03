#include <stdio.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <Eo.h>
#include "simple.eo.h"
#include "interface.eo.h"
#include "mixin.eo.h"

typedef struct
{
  int x;
  int y;
} Simple_Data;

#define MY_CLASS SIMPLE_CLASS

static void
_simple_x_get(Eo *obj, Simple_Data *pd, int*x)
{
  *x = pd->x;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
}

static void
_simple_x_set(Eo *obj, Simple_Data *pd, int x)
{
  pd->x = x;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
}

static void
_simple_y_get(Eo *obj, Simple_Data *pd, int*y)
{
  *x = pd->x;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
}

static void
_simple_y_set(Eo *obj, Simple_Data *pd, int y)
{
  pd->x = x;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
}

int
_simple_interface_mxy_get(Eo *obj, Simple_Data *pd)
{
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  return pd->x * pd->y; 
}

void
_simple_eo_base_constructor(Eo *obj, Simple_Data *pd)
{
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  eo_do_super(obj, MY_CLASS, eo_constructor());
}

#include "simple.eo.c"

