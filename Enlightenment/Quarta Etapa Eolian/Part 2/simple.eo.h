#ifndef _SIMPLE_EO_H_
#define _SIMPLE_EO_H_

#define SIMPLE_CLASS simple_class_get()

const Eo_Class *simple_class_get(void) EINA_CONST;

/**
 * @def simple_xy_set
 *
 * Sets properties X and Y
 *
 * @param[in] x X value
 * @param[in] y Y value
 *
 */
EAPI void  simple_xy_set(int x, int y);

/**
 * @def simple_xy_get
 *
 * Gets properties X and Y
 *
 * @param[out] x X value
 * @param[out] y Y value
 *
 */
EAPI void  simple_xy_get(int *x, int *y);


#endif