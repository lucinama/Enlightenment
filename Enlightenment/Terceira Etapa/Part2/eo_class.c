#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <Eo.h>
#include "eo_class.h"

EAPI Eo_Op SIMPLE_BASE_ID = 0;

#define MY_CLASS SIMPLE_CLASS

typedef struct
{
  int x,y;
} Private_Data;

static void
_xy_get(Eo *obj EINA_UNUSED, void *class_data, int* x, int* y)
{
  const Private_Data *pd = class_data;
  *x = pd->x;
  *y = pd->y;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
}

static void
_xy_set(Eo *obj EINA_UNUSED, void *class_data, int x, int y)
{
  Private_Data *pd = class_data;
  pd->x = x;
  pd->y = y;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
}

static int
_mxy_get(Eo *obj EINA_UNUSED, void *class_data)
{
  const Private_Data *pd = class_data;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
  return pd->x * pd->y;
}
  
EAPI EO_VOID_FUNC_BODYV(simple_xy_set, EO_FUNC_CALL(x,y), int x,int y);
EAPI EO_VOID_FUNC_BODYV(simple_xy_get, EO_FUNC_CALL(x,y), int* x,int* y);
EAPI EO_FUNC_BODY(simple_mxy_get, int, 0);

static Eo_Op_Description op_desc[] = {
    EO_OP_FUNC(simple_xy_set, _xy_set, "Set properties X and Y"),
    EO_OP_FUNC(simple_xy_get, _xy_get, "Get properties X and Y"),
    EO_OP_FUNC(simple_mxy_get, _mxy_get, "Get property MXY = X*Y"),
    EO_OP_SENTINEL
  };

static const Eo_Class_Description class_desc = {
  EO_VERSION,
  "Simple",
  EO_CLASS_TYPE_REGULAR,
  EO_CLASS_DESCRIPTION_OPS(op_desc),
  NULL,
  sizeof(Private_Data),
  NULL,
  NULL

};

EO_DEFINE_CLASS(simple_class_get, &class_desc, EO_CLASS, NULL);
