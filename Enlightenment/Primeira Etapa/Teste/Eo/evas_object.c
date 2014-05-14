#include "Eo.h"
EAPI Eo_Op EVAS_OBJ_LINE_BASE_ID = EO_NOOP;
#define MY_CLASS EVAS_OBJ_LINE_CLASS


static void
_line_xy_get(Eo *eo_obj, void *_pd, va_list *list)
{
const Evas_Object_Line *o = _pd;
Evas_Coord *x1 = va_arg(*list, Evas_Coord *);
Evas_Coord *y1 = va_arg(*list, Evas_Coord *);
Evas_Coord *x2 = va_arg(*list, Evas_Coord *);
Evas_Coord *y2 = va_arg(*list, Evas_Coord *);
Evas_Object_Protected_Data *obj = eo_data_scope_get(eo_obj, EVAS_OBJ_CLASS);
if (x1) *x1 = obj->cur.geometry.x + o->cur.x1;
if (y1) *y1 = obj->cur.geometry.y + o->cur.y1;
if (x2) *x2 = obj->cur.geometry.x + o->cur.x2;
if (y2) *y2 = obj->cur.geometry.y + o->cur.y2;
}
static void
_constructor(Eo *eo_obj, void *class_data, va_list *list EINA_UNUSED)
{
eo_do_super(eo_obj, eo_constructor());
Evas_Object_Protected_Data *obj = eo_data_scope_get(eo_obj, EVAS_OBJ_CLASS);
evas_object_line_init(eo_obj);
}

/* class constructor */
static void
_class_constructor(Eo_Class *klass)
{
const Eo_Op_Func_Description func_desc[] = {
/* Virtual functions of parent class implemented in this class */
EO_OP_FUNC(EO_BASE_ID(EO_BASE_SUB_ID_CONSTRUCTOR), _constructor),
EO_OP_FUNC(EO_BASE_ID(EO_BASE_SUB_ID_DESTRUCTOR), _destructor),
/* Specific functions to this class */
EO_OP_FUNC(EVAS_OBJ_LINE_ID(EVAS_OBJ_LINE_SUB_ID_XY_SET), _line_xy_set),
EO_OP_FUNC(EVAS_OBJ_LINE_ID(EVAS_OBJ_LINE_SUB_ID_XY_GET), _line_xy_get),
EO_OP_FUNC_SENTINEL
};
eo_class_funcs_set(klass, func_desc);
}
/* Descriptions for the functions specific to this class */
static const Eo_Op_Description op_desc[] = {
EO_OP_DESCRIPTION(EVAS_OBJ_LINE_SUB_ID_XY_SET, "Sets the coordinates of the end points of the given evas line object."),
EO_OP_DESCRIPTION(EVAS_OBJ_LINE_SUB_ID_XY_GET, "Retrieves the coordinates of the end points of the given evas line object."),
EO_OP_DESCRIPTION_SENTINEL
};
/* Description of the class */
static const Eo_Class_Description class_desc = {
EO_VERSION,
"Evas_Object_Line",
EO_CLASS_TYPE_REGULAR,
EO_CLASS_DESCRIPTION_OPS(&EVAS_OBJ_LINE_BASE_ID, op_desc, EVAS_OBJ_LINE_SUB_ID_LAST),
NULL,
sizeof(Evas_Object_Line),
_class_constructor,
NULL
};
/* Definition of the class */
EO_DEFINE_CLASS(evas_object_line_class_get, &class_desc, EVAS_OBJ_CLASS, NULL);
