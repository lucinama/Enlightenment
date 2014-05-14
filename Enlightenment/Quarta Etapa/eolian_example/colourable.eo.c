EAPI const Eo_Event_Description _COLOURABLE_EVENT_COLOUR_CHANGED =
   EO_EVENT_DESCRIPTION("colour_changed", "");

void _colourable_colour_set(Eo *obj, Colourable_Data *pd, int rgb);

EAPI EO_VOID_FUNC_BODYV(colourable_colour_set, EO_FUNC_CALL(rgb), int rgb);

int _colourable_colour_get(Eo *obj, Colourable_Data *pd);

EAPI EO_FUNC_BODY(colourable_colour_get, int, 0);

void _colourable_composite_colour_set(Eo *obj, Colourable_Data *pd, int r, int g, int b);

EAPI EO_VOID_FUNC_BODYV(colourable_composite_colour_set, EO_FUNC_CALL(r, g, b), int r, int g, int b);

void _colourable_composite_colour_get(Eo *obj, Colourable_Data *pd, int *r, int *g, int *b);

EAPI EO_VOID_FUNC_BODYV(colourable_composite_colour_get, EO_FUNC_CALL(r, g, b), int *r, int *g, int *b);

void _colourable_print_colour(Eo *obj, Colourable_Data *pd);

EAPI EO_VOID_FUNC_BODY(colourable_print_colour);

int _colourable_colour_mask(Eo *obj, Colourable_Data *pd, int mask);

EAPI EO_FUNC_BODYV(colourable_colour_mask, int, 0, EO_FUNC_CALL(mask), int mask);

void _colourable_constructor(Eo *obj, Colourable_Data *pd);

EAPI EO_VOID_FUNC_BODY(colourable_constructor);

void _colourable_rgb_composite_constructor(Eo *obj, Colourable_Data *pd, int r, int g, int b);

EAPI EO_VOID_FUNC_BODYV(colourable_rgb_composite_constructor, EO_FUNC_CALL(r, g, b), int r, int g, int b);

void _colourable_rgb_24bits_constructor(Eo *obj, Colourable_Data *pd, int rgb);

EAPI EO_VOID_FUNC_BODYV(colourable_rgb_24bits_constructor, EO_FUNC_CALL(rgb), int rgb);

static Eo_Op_Description _colourable_op_desc[] = {
     EO_OP_FUNC(colourable_constructor, _colourable_constructor, ""),
     EO_OP_FUNC(colourable_rgb_composite_constructor, _colourable_rgb_composite_constructor, ""),
     EO_OP_FUNC(colourable_rgb_24bits_constructor, _colourable_rgb_24bits_constructor, ""),
     EO_OP_FUNC(colourable_colour_set, _colourable_colour_set, "Sets a 24-bit RGB colour."),
     EO_OP_FUNC(colourable_colour_get, _colourable_colour_get, "Gets the 24-bit RGB colour."),
     EO_OP_FUNC(colourable_composite_colour_set, _colourable_composite_colour_set, "Sets a composite RGB colour."),
     EO_OP_FUNC(colourable_composite_colour_get, _colourable_composite_colour_get, "Gets the composite RGB colour."),
     EO_OP_FUNC(colourable_print_colour, _colourable_print_colour, "Print the RGB colour."),
     EO_OP_FUNC(colourable_colour_mask, _colourable_colour_mask, "The masked RGB value."),
     EO_OP_SENTINEL
};

static const Eo_Event_Description *_colourable_event_desc[] = {
     COLOURABLE_EVENT_COLOUR_CHANGED,
     NULL
};

static const Eo_Class_Description _colourable_class_desc = {
     EO_VERSION,
     "Colourable",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_colourable_op_desc),
     _colourable_event_desc,
     sizeof(Colourable_Data),
     NULL,
     NULL
};

EO_DEFINE_CLASS(colourable_class_get, &_colourable_class_desc, EO_CLASS, NULL);