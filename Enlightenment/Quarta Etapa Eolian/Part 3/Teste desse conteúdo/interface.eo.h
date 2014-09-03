#ifndef _INTERFACE_EO_H_
#define _INTERFACE_EO_H_

/**
 * Interface Class
 */
#define INTERFACE_CLASS interface_class_get()

const Eo_Class *interface_class_get(void) EINA_CONST;

/**
 *
 * Gets property MXY = X*Y
 *
 *
 */
EOAPI int  interface_mxy_get(void);


#endif