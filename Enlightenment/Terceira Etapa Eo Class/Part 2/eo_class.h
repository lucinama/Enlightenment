#ifndef SIMPLE_H
#define SIMPLE_H

#include <Eo.h>

EAPI void simple_xy_set(int x,int y);

EAPI void simple_xy_get(int*x, int *y);

EAPI int simple_mxy_get(void);

#define SIMPLE_CLASS simple_class_get()
const Eo_Class *simple_class_get(void);

#endif
