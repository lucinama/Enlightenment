#ifndef SIMPLE_H
#define SIMPLE_H

#include <Eo.h>

extern EAPI Eo_Op SIMPLE_BASE_ID;

enum {
  SIMPLE_SUB_ID_XY_SET,
  SIMPLE_SUB_ID_XY_GET,
  SIMPLE_SUB_ID_MXY_GET,
  SIMPLE_SUB_ID_LAST
};

#define SIMPLE_ID(sub_id) (SIMPLE_BASE_ID + sub_id)

#define simple_xy_set(x,y) SIMPLE_ID(SIMPLE_SUB_ID_XY_SET), EO_TYPECHECK(int, x), EO_TYPECHECK(int, y)

#define simple_xy_get(x,y) SIMPLE_ID(SIMPLE_SUB_ID_XY_GET), EO_TYPECHECK(int *, x), EO_TYPECHECK(int *, y)

#define simple_mxy_get(mxy) SIMPLE_ID(SIMPLE_SUB_ID_MXY_GET), EO_TYPECHECK(int *, mxy)

#define SIMPLE_CLASS simple_class_get()
const Eo_Class *simple_class_get(void);

#endif
