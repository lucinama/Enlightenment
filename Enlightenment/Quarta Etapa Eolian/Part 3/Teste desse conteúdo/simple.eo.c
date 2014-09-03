
void _simple_x_set(Eo *obj, Simple_Data *pd, int x);

EOAPI EO_VOID_FUNC_BODYV(simple_x_set, EO_FUNC_CALL(x), int x);

int _simple_x_get(Eo *obj, Simple_Data *pd);

EOAPI EO_FUNC_BODY(simple_x_get, int, 0);

void _simple_y_set(Eo *obj, Simple_Data *pd, int y);

EOAPI EO_VOID_FUNC_BODYV(simple_y_set, EO_FUNC_CALL(y), int y);

int _simple_y_get(Eo *obj, Simple_Data *pd);

EOAPI EO_FUNC_BODY(simple_y_get, int, 0);

int _simple_interface_mxy_get(Eo *obj, Simple_Data *pd);


void _simple_eo_base_constructor(Eo *obj, Simple_Data *pd);


static Eo_Op_Description _simple_op_desc[] = {
     EO_OP_FUNC_OVERRIDE(interface_mxy_get, _simple_interface_mxy_get),
     EO_OP_FUNC_OVERRIDE(eo_constructor, _simple_eo_base_constructor),
     EO_OP_FUNC(simple_x_set, _simple_x_set, "Sets properties X"),
     EO_OP_FUNC(simple_x_get, _simple_x_get, "Gets properties X"),
     EO_OP_FUNC(simple_y_set, _simple_y_set, "Sets properties Y"),
     EO_OP_FUNC(simple_y_get, _simple_y_get, "Gets properties Y"),
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

EO_DEFINE_CLASS(simple_class_get, &_simple_class_desc, EO_BASE_CLASS, INTERFACE_CLASS, MIXIN_CLASS, NULL);