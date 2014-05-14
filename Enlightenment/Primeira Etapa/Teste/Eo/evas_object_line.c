#include "Eo.h"
#define EVAS_OBJ_LINE_CLASS evas_object_line_class_get()
const Eo_Class *evas_object_line_class_get(void) EINA_CONST;
extern EAPI Eo_Op EVAS_OBJ_LINE_BASE_ID;
enum
  {
EVAS_OBJ_LINE_SUB_ID_XY_SET,
EVAS_OBJ_LINE_SUB_ID_XY_GET,
EVAS_OBJ_LINE_SUB_ID_LAST
  }
#define EVAS_OBJ_LINE_ID(sub_id) (EVAS_OBJ_LINE_BASE_ID + sub_id)
/*
* @def evas_obj_line_xy_set
* @since 1.8
*
* Sets the coordinates of the end points of the given evas line object.
*
* @param[in] x1
* @param[in] y1
* @param[in] x2
* @param[in] y2
*
*/
#define evas_obj_line_xy_set(x1, y1, x2, y2) EVAS_OBJ_LINE_ID(EVAS_OBJ_LINE_SUB_ID_XY_SET), EO_TYPECHECK(Evas_Coord, x1), EO_TYPECHECK(Evas_Coord, y1), EO_TYPECHECK(Evas_Coord, x2), EO_TYPECHECK(Evas_Coord, y2)
/*
* @def evas_obj_line_xy_get
* @since 1.8
*
* Retrieves the coordinates of the end points of the given evas line object.
*
* @param[out] x1
* @param[out] y1
* @param[out] x2
* @param[out] y2
*
*/
#define evas_obj_line_xy_get(x1, y1, x2, y2) EVAS_OBJ_LINE_ID(EVAS_OBJ_LINE_SUB_ID_XY_GET), EO_TYPECHECK(Evas_Coord *, x1), EO_TYPECHECK(Evas_Coord *, y1), EO_TYPECHECK(Evas_Coord *, x2), EO_TYPECHECK(Evas_Coord *, y2)
