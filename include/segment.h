#ifndef SEGMENT_H
#define SEGMENT_H

#include "ei_types.h"
#include "hw_interface.h"


typedef struct ei_side {
        int ymax;
        int x_ymin;
        int dx;
        int dy;
        struct ei_side *next;
} ei_side;

typedef struct ei_side_table {
        size_t length;
        struct ei_side **array;
} ei_side_table;

/**
 * \brief       Determines if point (x, y) is in clipper
 *
 * @param       x
 * @param       y
 * @param       clipper         If not NULL, the drawing is restricted within this rectangle.
 * @return                      0 iff point not in clipper
 */
int point_in_clipper(int x, int y, const ei_rect_t *clipper);

/**
 * \brief       Draw a straight segment.
 *
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
 * \brief       Draw a segment using Bresenham algorithm.
 * @param       surface         Where to draw the line, from (x1, y1) to (x2, y2).
 *                              The surface must be *locked* by \ref hw_surface_lock.
 *
 * @param       x1
 * @param       y1
 * @param       dx
 * @param       dy
 * @param       sign_x          1 or -1 ; sign of x
 * @param       sign_y          1 or -1 ; sign of y
 * @param       swap            0 or 1 ; determines whether x and y coordinates are swapped
 * @param	color		The color used to draw the line. The alpha channel is managed.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void draw_segment_bresenham(ei_surface_t surface,
                            int x1, int y1, int dx, int dy, int sign_x, int sign_y, int swap,
                            ei_color_t color,
                            const ei_rect_t *clipper);

ei_side_table construct_side_table(ei_surface_t surface, const ei_linked_point_t *first_point);

void sort_side_table(ei_side* side);

void swap_side(ei_side* s1, ei_side* s2);

#endif //SEGMENT_H