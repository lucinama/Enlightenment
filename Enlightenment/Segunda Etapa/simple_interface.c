#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "Eo.h"
#include "simple_interface.h"

EAPI Eo_Op INTERFACE_BASE_ID = EO_NOOP;

#define MY_CLASS INTERFACE_CLASS

static const Eo_Op_Description op_desc[] = {
     EO_OP_DESCRIPTION(INTERFACE_SUB_ID_A_POWER_3_GET, "Get the a^3"),
     EO_OP_DESCRIPTION_SENTINEL
};

static const Eo_Class_Description class_desc = {
     EO_VERSION,
     "Interface",
     EO_CLASS_TYPE_INTERFAC
     EO_CLASS_DESCRIPTION_OPS(&INTERFACE_BASE_ID, op_desc, INTERFACE_SUB_ID_LAST),
     NULL,
     0,
     NULL,
     NULL
};

EO_DEFINE_CLASS(interface_class_get, &class_desc, NULL, NULL)
