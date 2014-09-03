
int _mixin_dxy_get(Eo *obj, void *pd);

EAPI EO_FUNC_BODY(mixin_dxy_get, int, 0);

static Eo_Op_Description _mixin_op_desc[] = {
     EO_OP_FUNC(mixin_dxy_get, _mixin_dxy_get, "Gets property DXY = X/Y"),
     EO_OP_SENTINEL
};

static const Eo_Class_Description _mixin_class_desc = {
     EO_VERSION,
     "Mixin",
     EO_CLASS_TYPE_MIXIN,
     EO_CLASS_DESCRIPTION_OPS(_mixin_op_desc),
     NULL,
     0,
     NULL,
     NULL
};

EO_DEFINE_CLASS(mixin_class_get, &_mixin_class_desc, NULL, NULL);