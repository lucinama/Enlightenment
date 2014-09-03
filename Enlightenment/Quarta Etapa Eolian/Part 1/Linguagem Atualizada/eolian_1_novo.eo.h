#ifndef _EOLIAN_1_NOVO_EO_H_
#define _EOLIAN_1_NOVO_EO_H_

#ifndef _EOLIAN_1_NOVO_EO_TYPES
#define _EOLIAN_1_NOVO_EO_TYPES


#endif
/**
 * Simple Class
 */
#define SIMPLE_CLASS simple_class_get()

const Eo_Class *simple_class_get(void) EINA_CONST;

/**
 *
 * Sets properties X and Y
 *
 * @param[in] x X value
 * @param[in] y Y value
 *
 */
EOAPI void  simple_xy_set(int x, int y);

/**
 *
 * Gets properties X and Y
 *
 * @param[out] x X value
 * @param[out] y Y value
 *
 */
EOAPI void  simple_xy_get(int *x, int *y);

/**
 *
 * Gets property MXY = X*Y
 *
 *
 */
EOAPI int  simple_mxy_get(void);


#endif
