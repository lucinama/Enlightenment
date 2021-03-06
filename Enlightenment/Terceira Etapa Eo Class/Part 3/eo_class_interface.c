#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Eo.h"
#include "eo_class_interface.h"

#define MY_CLASS INTERFACE_CLASS

EAPI EO_FUNC_BODY(interface_mxy_get, int, 0);

static Eo_Op_Description op_desc[] = {
  EO_OP_FUNC(interface_mxy_get, NULL, "Get properties MXY = X*Y"),
  EO_OP_SENTINEL
};

static const Eo_Class_Description class_desc = {
  EO_VERSION,
  "Interface",
  EO_CLASS_TYPE_INTERFACE,
  EO_CLASS_DESCRIPTION_OPS(op_desc),
  NULL,
  0,
  NULL,
  NULL
};

EO_DEFINE_CLASS(interface_class_get, &class_desc, NULL, NULL)

