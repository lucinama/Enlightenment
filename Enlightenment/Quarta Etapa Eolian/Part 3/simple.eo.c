
void _simple_xy_set(Eo *obj, Simple_Data *pd, int x, int y);

EAPI EO_VOID_FUNC_BODYV(simple_xy_set, EO_FUNC_CALL(x, y), int x, int y);

void _simple_xy_get(Eo *obj, Simple_Data *pd, int *x, int *y);

EAPI EO_VOID_FUNC_BODYV(simple_xy_get, EO_FUNC_CALL(x, y), int *x, int *y);

int _simple_interface_mxy_get(Eo *obj, Simple_Data *pd);


void _simple_eo_base_constructor(Eo *obj, Simple_Data *pd);


static Eo_Op_Description _simple_op_desc[] = {
     EO_OP_FUNC_OVERRIDE(interface_mxy_get, _simple_interface_mxy_get),
     EO_OP_FUNC_OVERRIDE(eo_constructor, _simple_eo_base_constructor),
     EO_OP_FUNC(simple_xy_set, _simple_xy_set, "Sets properties X and Y"),
     EO_OP_FUNC(simple_xy_get, _simple_xy_get, "Gets properties X and Y"),
     EO_OP_SENTINEL
};

static const Eo_Class_Description _simple_class_desc = {
     EO_VERSION,
     "Simple",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_simple_op_desc),
     NULL,
     sizeof(Simple_Data),
     NULL,
     NULL
};

EO_DEFINE_CLASS(simple_class_get, &_simple_class_desc, EO_CLASS, INTERFACE_CLASS, MIXIN_CLASS, NULL);