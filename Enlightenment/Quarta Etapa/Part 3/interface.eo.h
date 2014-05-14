#ifndef _INTERFACE_EO_H_
#define _INTERFACE_EO_H_

/**
 * Interface Class
 */
#define INTERFACE_CLASS interface_class_get()

const Eo_Class *interface_class_get(void) EINA_CONST;

/**
 * @def interface_mxy_get
 *
 * Gets property MXY = X*Y
 *
 *
 */
EAPI int  interface_mxy_get(void);


#endif