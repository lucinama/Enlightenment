#include <stdio.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <Eo.h>
#include "mixin.eo.h"

#define MY_CLASS MIXIN_CLASS

int
_mixin_dxy_get(Eo *obj EINA_UNUSED,void *pd)
{
  int x=-1, y=-1;
  eo_do(obj, simple_xy_get(&x,&y));
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  return x / y;
}

#include "mixin.eo.c"
