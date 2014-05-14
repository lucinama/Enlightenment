#ifndef _COLOURABLE_EO_H_
#define _COLOURABLE_EO_H_

#define COLOURABLE_CLASS colourable_class_get()

const Eo_Class *colourable_class_get(void) EINA_CONST;

/**
 * @def colourable_constructor
 *
 * No description supplied.
 *
 *
 */
EAPI void  colourable_constructor(void);

/**
 * @def colourable_rgb_composite_constructor
 *
 * No description supplied.
 *
 * @param[in] r The red component.
 * @param[in] g The green component.
 * @param[in] b The blue component.
 *
 */
EAPI void  colourable_rgb_composite_constructor(int r, int g, int b);

/**
 * @def colourable_rgb_24bits_constructor
 *
 * No description supplied.
 *
 * @param[in] rgb 24-bit RGB Component.
 *
 */
EAPI void  colourable_rgb_24bits_constructor(int rgb);

/**
 * @def colourable_colour_set
 *
 * Sets a 24-bit RGB colour.
 *
 * @param[in] rgb The RGB colour value.
 *
 */
EAPI void  colourable_colour_set(int rgb);

/**
 * @def colourable_colour_get
 *
 * Gets the 24-bit RGB colour.
 *
 *
 */
EAPI int  colourable_colour_get(void);

/**
 * @def colourable_composite_colour_set
 *
 * Sets a composite RGB colour.
 *
 * @param[in] r The red component.
 * @param[in] g The green component.
 * @param[in] b The blue component.
 *
 */
EAPI void  colourable_composite_colour_set(int r, int g, int b);

/**
 * @def colourable_composite_colour_get
 *
 * Gets the composite RGB colour.
 *
 * @param[out] r The red component.
 * @param[out] g The green component.
 * @param[out] b The blue component.
 *
 */
EAPI void  colourable_composite_colour_get(int *r, int *g, int *b);

/**
 * @def colourable_print_colour
 *
 * Print the RGB colour.
 *
 *
 */
EAPI void  colourable_print_colour(void);

/**
 * @def colourable_colour_mask
 *
 * The masked RGB value.
 *
 * @param[in] mask The colour mask to be applied to current RGB value.
 *
 */
EAPI int  colourable_colour_mask(int mask);

EAPI extern const Eo_Event_Description _COLOURABLE_EVENT_COLOUR_CHANGED;

/**
 * No description
 */
#define COLOURABLE_EVENT_COLOUR_CHANGED (&(_COLOURABLE_EVENT_COLOUR_CHANGED))

#endif