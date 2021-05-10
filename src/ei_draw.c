#include <stdint.h>

#include "ei_types.h"
#include "hw_interface.h"

#include "segment.h"

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
        int ir, ig, ib, ia;

        /* Obtenir les indices et ranger dans un tableau */
        hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);
        int array[4] = {255, 255, 255, 255};
        array[ir] = color.red;
        array[ig] = color.green;
        array[ib] = color.blue;
        if (ia != -1) {
                array[ia] = color.alpha;
        }

        /* Multiplication par 16^6, 16^4 et 16^2 des indices dans l'ordre d'apparition */
        uint32_t rgba = array[3] * 16777216 + array[2] * 65536 + array[1] * 256 + array[0];
        return rgba;
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
        /* TODO: Refactorisation */
        int x1, x2, y1, y2, dx, dy;
        int swap = 0;

        /* Tracé d'un point */
        if (first_point->next == NULL) {
                x1 = first_point->point.x;
                y1 = first_point->point.y;
                draw_segment_straight(surface, x1, x1, y1, y1, color, clipper);
                return;
        }

        /* Segment par segment */
        while (first_point->next != NULL) {
                x1 = first_point->point.x;
                y1 = first_point->point.y;
                first_point = first_point->next;
                x2 = first_point->point.x;
                y2 = first_point->point.y;

                dx = x2 - x1;
                dy = y2 - y1;

                /* Conditions à respecter */
                if (dx < 0) {
                        dx = -dx;
                } else if (dx == 0) {
                        draw_segment_straight(surface, x1, x2, y1, y2, color, clipper);
                        continue;
                }
                if (dy < 0) {
                        dy = -dy;
                } else if (dy == 0) {
                        draw_segment_straight(surface, x1, x2, y1, y2, color, clipper);
                        continue;
                }
                if (dx < dy) {
                        swap = 1;
                }
                draw_segment_bresenham(surface, x1, x2, y1, y2, dx, dy, swap, color, clipper);
        }
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
        /* TODO: Clipping de ei_fill */
        ei_size_t size = hw_surface_get_size(surface);
        uint32_t col;
        uint32_t *pixel_ptr;
        int i;

        if (color == NULL) {
                col = ei_map_rgba(surface, (ei_color_t) {0x00, 0x00, 0x00, 0xff});
        } else {
                col = ei_map_rgba(surface, *color);
        }

        pixel_ptr = (uint32_t *) hw_surface_get_buffer(surface);
        for (i = 0; i < (size.width * size.height); i++) {
                *pixel_ptr++ = col;
        }
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