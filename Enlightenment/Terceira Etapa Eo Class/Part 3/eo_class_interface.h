#ifndef INTERFACE_H
#define INTERFACE_H

#include <Eo.h>

EAPI int interface_mxy_get(void);

#define INTERFACE_CLASS interface_class_get()
const Eo_Class *interface_class_get(void);

#endif
