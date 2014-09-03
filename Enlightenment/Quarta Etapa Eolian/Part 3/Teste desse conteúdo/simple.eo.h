#ifndef _SIMPLE_EO_H_
#define _SIMPLE_EO_H_

/**
 * Simple Class
 */
#define SIMPLE_CLASS simple_class_get()

const Eo_Class *simple_class_get(void) EINA_CONST;

/**
 *
 * Sets properties X
 *
 * @param[in] x X value
 *
 */
EOAPI void  simple_x_set(int x);

/**
 *
 * Gets properties X
 *
 *
 */
EOAPI int  simple_x_get(void);

/**
 *
 * Sets properties Y
 *
 * @param[in] y Y value
 *
 */
EOAPI void  simple_y_set(int y);

/**
 *
 * Gets properties Y
 *
 *
 */
EOAPI int  simple_y_get(void);


#endif