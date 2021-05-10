#include <stdint.h>
#include "ei_types.h"
#include "hw_interface.h"

/**
 * \brief	Converts the red, green, blue and alpha components of a color into a 32 bits integer
 * 		than can be written directly in the memory returned by \ref hw_surface_get_buffer.
 * 		The surface parameter provides the channel order.
 *
 * @param	surface		The surface where to store this pixel, provides the channels order.
 * @param	color		The color to convert.
 *
 * @return 			The 32 bit integer corresponding to the color. The alpha component
 *				of the color is ignored in the case of surfaces that don't have an
 *				alpha channel.
 */
uint32_t ei_map_rgba(ei_surface_t surface, ei_color_t color) {

}


/**
 * \brief	Draws a line that can be made of many line segments.
 *
 * @param	surface 	Where to draw the line. The surface must be *locked* by
 *				\ref hw_surface_lock.
 * @param	first_point 	The head of a linked list of the points of the polyline. It can be NULL
 *				(i.e. draws nothing), can have a single point, or more.
 *				If the last point is the same as the first point, then this pixel is
 *				drawn only once.
 * @param	color		The color used to draw the line. The alpha channel is managed.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void ei_draw_polyline(ei_surface_t surface,
                      const ei_linked_point_t *first_point,
                      ei_color_t color,
                      const ei_rect_t *clipper) {
        /* TODO: Clipping de ei_draw_polyline */
        /* Déclarations des variables */
        int x1, x2, y1, y2, dx, dy;
        int swap = 0;

        /* Segment par segment */
        while (first_point != NULL) {
                x1 = first_point->point.x;
                y1 = first_point->point.y;
                first_point = first_point->next;
                if (first_point == NULL) {
                        draw_polyline_straight(surface, x1, x1, y1, y1, color, clipper);
                        return;
                }
                x2 = first_point->point.x;
                y2 = first_point->point.y;
                dx = x2 - x1;
                dy = y2 - y1;

                /* Conditions à respecter */
                if (dx < 0) {
                        dx = -dx;
                } else if (dx == 0) {
                        draw_polyline_straight(surface, x1, x2, y1, y2, color, clipper);
                        continue;
                }
                if (dy < 0) {
                        dy = -dy;
                } else if (dy == 0) {
                        draw_polyline_straight(surface, x1, x2, y1, y2, color, clipper);
                        continue;
                }
                if (dx < dy) {
                        swap = 1;
                }
                draw_segment_bresenham(surface, x1, x2, y1, y2, dx, dy, swap, color, clipper);
        }
        return;
}

void draw_segment_straight(ei_surface_t surface,
                           int x1, int x2, int y1, int y2,
                           ei_color_t color,
                           const ei_rect_t *clipper) {
        /* TODO: factorisation du code */
        /* Doit pouvoir marcher pour un point (x1 == x2, y1 == y2) */
        int width, i;
        uint32_t *pixel_ptr;

        width = hw_surface_get_size(surface).width;
        pixel_ptr = (uint32_t *) hw_surface_get_buffer(surface);

        /* On positionne le pointeur au départ (x1, y1) */
        pixel_ptr += x1;
        pixel_ptr += y1 * width;

        if (x1 == x2) { // Ligne verticale
                for (i = y1; i <= y2; i++) {
                        *pixel_ptr = ei_map_rgba(surface, color);
                        pixel_ptr += width;
                }
        } else { // Ligne horizontale
                for (i = x1; i <= x2; i++) {
                        *pixel_ptr = ei_map_rgba(surface, color);
                        pixel_ptr += 1;
                }
        }
        return;
}

void draw_segment_bresenham(ei_surface_t surface,
                            int x1, int x2, int y1, int y2, int dx, int dy, int swap,
                            ei_color_t color,
                            const ei_rect_t *clipper) {
        /* TODO: Si algorithme trop lent, voir algo sur wiki */
        int width, i, E;
        uint32_t *pixel_ptr;

        width = hw_surface_get_size(surface).width;
        pixel_ptr = (uint32_t *) hw_surface_get_buffer(surface);

        /* On positionne le pointeur au départ (x, y) */
        pixel_ptr += x1;
        pixel_ptr += y1 * width;

        if ((dx < dy) || (dx < 0) || (dy < 0)) { // TODO: remove
                printf("FAIL");
        }

        if (swap == 0) {
                for (i = x1; i <= x2; i++) {
                        *pixel_ptr = ei_map_rgba(surface, color);
                        pixel_ptr++; // x+= 1
                        E += dy;
                        if (2 * E > dx) {
                                pixel_ptr += width; // y+= 1
                                E -= dx;
                        }
                }
        } else { // On inverse x et y
                for (i = y1; i <= y2; i++) {
                        *pixel_ptr = ei_map_rgba(surface, color);
                        pixel_ptr += width; // y+= 1 (swap)
                        E += dx;
                        if (2 * E > dy) {
                                pixel_ptr++; // x+= 1 (swap)
                                E -= dy;
                        }
                }
        }
        return;
}

/**
 * \brief	Draws a filled polygon.
 *
 * @param	surface 	Where to draw the polygon. The surface must be *locked* by
 *				\ref hw_surface_lock.
 * @param	first_point 	The head of a linked list of the points of the line. It is either
 *				NULL (i.e. draws nothing), or has more than 2 points. The last point
 *				is implicitly connected to the first point, i.e. polygons are
 *				closed, it is not necessary to repeat the first point.
 * @param	color		The color used to draw the polygon. The alpha channel is managed.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void ei_draw_polygon(ei_surface_t surface,
                     const ei_linked_point_t *first_point,
                     ei_color_t color,
                     const ei_rect_t *clipper) {

}

/**
 * \brief	Draws text by calling \ref hw_text_create_surface.
 *
 * @param	surface 	Where to draw the text. The surface must be *locked* by
 *				\ref hw_surface_lock.
 * @param	where		Coordinates, in the surface, where to anchor the top-left corner of
 *				the rendered text.
 * @param	text		The string of the text. Can't be NULL.
 * @param	font		The font used to render the text. If NULL, the \ref ei_default_font
 *				is used.
 * @param	color		The text color. Can't be NULL. The alpha parameter is not used.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void ei_draw_text(ei_surface_t surface,
                  const ei_point_t *where,
                  const char *text,
                  ei_font_t font,
                  ei_color_t color,
                  const ei_rect_t *clipper) {

}

/**
 * \brief	Fills the surface with the specified color.
 *
 * @param	surface		The surface to be filled. The surface must be *locked* by
 *				\ref hw_surface_lock.
 * @param	color		The color used to fill the surface. If NULL, it means that the
 *				caller want it painted black (opaque).
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void ei_fill(ei_surface_t surface,
             const ei_color_t *color,
             const ei_rect_t *clipper) {

}


/**
 * \brief	Copies pixels from a source surface to a destination surface.
 *		The source and destination areas of the copy (either the entire surfaces, or
 *		subparts) must have the same size before considering clipping.
 *		Both surfaces must be *locked* by \ref hw_surface_lock.
 *
 * @param	destination	The surface on which to copy pixels.
 * @param	dst_rect	If NULL, the entire destination surface is used. If not NULL,
 *				defines the rectangle on the destination surface where to copy
 *				the pixels.
 * @param	source		The surface from which to copy pixels.
 * @param	src_rect	If NULL, the entire source surface is used. If not NULL, defines the
 *				rectangle on the source surface from which to copy the pixels.
 * @param	alpha		If true, the final pixels are a combination of source and
 *				destination pixels weighted by the source alpha channel and
 *				the transparency of the final pixels is set to opaque.
 *				If false, the final pixels are an exact copy of the source pixels,
 				including the alpha channel.
 *
 * @return			Returns 0 on success, 1 on failure (different sizes between source and destination).
 */
int ei_copy_surface(ei_surface_t destination,
                    const ei_rect_t *dst_rect,
                    ei_surface_t source,
                    const ei_rect_t *src_rect,
                    ei_bool_t alpha) {

}