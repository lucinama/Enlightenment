EOAPI EO_FUNC_BODY(interface_mxy_get, int, 0);

static Eo_Op_Description _interface_op_desc[] = {
     EO_OP_FUNC(interface_mxy_get, NULL, "Gets property MXY = X*Y"),
     EO_OP_SENTINEL
};

static const Eo_Class_Description _interface_class_desc = {
     EO_VERSION,
     "Interface",
     EO_CLASS_TYPE_INTERFACE,
     EO_CLASS_DESCRIPTION_OPS(_interface_op_desc),
     NULL,
     0,
     NULL,
     NULL
};

EO_DEFINE_CLASS(interface_class_get, &_interface_class_desc, NULL, NULL);