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
_xy_get(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  const Private_Data *pd = class_data;
  int *x, *y;
  x = va_arg(*list, int *);
  y = va_arg(*list, int *);
  *x = pd->x;
  *y = pd->y;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
}

static void
_xy_set(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  printf("Erro1\n");
  Private_Data *pd = class_data;
  int x,y;
  x = va_arg(*list, int);
  y = va_arg(*list, int);
  printf("Erro2\n");
  pd->x = x;
  pd->y = y;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);

}

static void
_mxy_get(Eo *obj EINA_UNUSED, void *class_data, va_list *list)
{
  const Private_Data *pd = class_data;
  int *mxy;
  mxy = va_arg(*list, int *);
  if(mxy)
    *mxy = pd->x * pd->y;
  printf("%s %s\n", eo_class_name_get(MY_CLASS), __func__);
 }
  
static void
_class_constructor(Eo_Class *klass)
{
  const Eo_Op_Func_Description func_desc[] = {
    EO_OP_FUNC(SIMPLE_ID(SIMPLE_SUB_ID_XY_SET), _xy_set),
    EO_OP_FUNC(SIMPLE_ID(SIMPLE_SUB_ID_XY_GET), _xy_get),
    EO_OP_FUNC(SIMPLE_ID(SIMPLE_SUB_ID_MXY_GET), _mxy_get),
    EO_OP_FUNC_SENTINEL
  };

  eo_class_funcs_set(klass, func_desc);
}

static const Eo_Op_Description op_desc[] = {
  EO_OP_DESCRIPTION(SIMPLE_SUB_ID_XY_SET, "Set properties X and Y"),
  EO_OP_DESCRIPTION(SIMPLE_SUB_ID_XY_GET, "Get properties X and Y"),
  EO_OP_DESCRIPTION(SIMPLE_SUB_ID_MXY_GET, "Get properties MXY = X*Y"),
  EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
  EO_VERSION,
  "Simple",
  EO_CLASS_TYPE_REGULAR,
  EO_CLASS_DESCRIPTION_OPS(&SIMPLE_BASE_ID, op_desc, SIMPLE_SUB_ID_LAST),
  NULL,
  sizeof(Private_Data),
  _class_constructor,
  NULL

};

EO_DEFINE_CLASS(simple_class_get, &class_desc, EO_BASE_CLASS, NULL, NULL, NULL)
