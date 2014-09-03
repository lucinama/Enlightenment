#ifndef _MIXIN_EO_H_
#define _MIXIN_EO_H_

/**
 * Mixin Class
 */
#define MIXIN_CLASS mixin_class_get()

const Eo_Class *mixin_class_get(void) EINA_CONST;

/**
 *
 * Gets property DXY = X/Y
 *
 *
 */
EOAPI int  mixin_dxy_get(void);


#endif