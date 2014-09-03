EOAPI const Eo_Event_Description _SIMPLE_EVENT_X_CHANGED =
   EO_EVENT_DESCRIPTION("x,changed", "Called when x has been changed.");

void _simple_x_set(Eo *obj, Private_Data *pd, int x);

EOAPI EO_VOID_FUNC_BODYV(simple_x_set, EO_FUNC_CALL(x), int x);

void _simple_eo_base_constructor(Eo *obj, Private_Data *pd);


static Eo_Op_Description _simple_op_desc[] = {
     EO_OP_FUNC_OVERRIDE(eo_constructor, _simple_eo_base_constructor),
     EO_OP_FUNC(simple_x_set, _simple_x_set, "Set property X"),
     EO_OP_SENTINEL
};

static const Eo_Event_Description *_simple_event_desc[] = {
     SIMPLE_EVENT_X_CHANGED,
     NULL
};

static const Eo_Class_Description _simple_class_desc = {
     EO_VERSION,
     "Simple",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_simple_op_desc),
     _simple_event_desc,
     sizeof(Private_Data),
     NULL,
     NULL
};

EO_DEFINE_CLASS(simple_class_get, &_simple_class_desc, EO_BASE_CLASS, NULL);