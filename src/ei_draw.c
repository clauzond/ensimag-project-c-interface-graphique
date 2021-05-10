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
        int x, y, dx, dy;
        int x1, x2, y1, y2;
        int E;
        int sign_x, sign_y = 1, 1;
        int swap = 0;

        /* Segment par segment */
        while (first_point->next != NULL) {
                x1, y1 = first_point->point.x, first_point->point.y;
                first_point = first_point->next;
                x2, y2 = first_point->point.x, first_point->point.y;
                /* Conditions à respecter */
                if (x1 > x2) { // dx < 0
                        x1, x2 = -x1, -x2;
                        sign_x = -1;
                } else if (x1 == x2) { // dx == 0
                        draw_polyline_straight(surface, x1, x2, y1, y2, color, clipper)
                }
                if (y1 > y2) { // dy < 0
                        y1, y2 = -y1, -y2;
                        sign_y = -1;
                } else if (y1 == y2) { // dy == 0
                        draw_polyline_straight(surface, x1, x2, y1, y2, color, clipper)
                }
                if (x2 - x1 < y2 - y1) { // |dx| < |dy|
                        x1, y1 = y1, x1;
                        x2, y2 = y2, x2;
                        swap = 1;
                }
                draw_segment_bresenham(surface, x1, x2, y1, y2, sign_x, sign_y, swap, color, clipper);
        }

}

void draw_segment_straight(ei_surface_t surface,
                            int x1, int x2, int y1, int y2,
                            ei_color_t color,
                            const ei_rect_t *clipper) {}

void draw_segment_bresenham(ei_surface_t surface,
                            int x1, int x2, int y1, int y2, int sign_x, int sign_y, int swap,
                            ei_color_t color,
                            const ei_rect_t *clipper) {
        // La surface est déjà locked
        // Il reste à utiliser le buffer ; s'inspirer de minimal.c
        // Pour le parcours du buffer, faire ligne par ligne (raisonner dans la boucle de l'algo)
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