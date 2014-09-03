#ifndef _SIMPLE_EO_H_
#define _SIMPLE_EO_H_

#ifndef _SIMPLE_EO_TYPES
#define _SIMPLE_EO_TYPES


#endif
/**
 * Simple Class
 */
#define SIMPLE_CLASS simple_class_get()

const Eo_Class *simple_class_get(void) EINA_CONST;

/**
 *
 * Set property X
 *
 * @param[in] x X value
 *
 */
EOAPI void  simple_x_set(int x);

EOAPI extern const Eo_Event_Description _SIMPLE_EVENT_X_CHANGED;

/**
 * Called when x has been changed.
 */
#define SIMPLE_EVENT_X_CHANGED (&(_SIMPLE_EVENT_X_CHANGED))

#endif
