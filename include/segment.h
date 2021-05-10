#ifndef SEGMENT_H
#define SEGMENT_H

#include "ei_types.h"
#include "hw_interface.h"

/**
 * \brief
 * @param       surface         Where to draw the line, from (x1, y1) to (x2, y2).
 *                              The surface must be *locked* by \ref hw_surface_lock.
 * @param       x1
 * @param       x2
 * @param       y1
 * @param       y2
 * @param	color		The color used to draw the line. The alpha channel is managed.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void draw_segment_straight(ei_surface_t surface,
                           int x1, int x2, int y1, int y2,
                           ei_color_t color,
                           const ei_rect_t *clipper);

/**
 *
 * @param       surface         Where to draw the line, from (x1, y1) to (x2, y2).
 *                              The surface must be *locked* by \ref hw_surface_lock.
 * @param       x1
 * @param       x2
 * @param       y1
 * @param       y2
 * @param       dx
 * @param       dy
 * @param       swap            0 or 1 ; determines whether x and y coordinates are swapped
 * @param	color		The color used to draw the line. The alpha channel is managed.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void draw_segment_bresenham(ei_surface_t surface,
                            int x1, int x2, int y1, int y2, int dx, int dy, int swap,
                            ei_color_t color,
                            const ei_rect_t *clipper);

#endif //SEGMENT_H