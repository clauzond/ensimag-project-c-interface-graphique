#include <stdint.h>
#include "ei_draw.h"
#include "ei_types.h"
#include "hw_interface.h"

int point_in_clipper(int x, int y, const ei_rect_t *clipper) {
        if (clipper == NULL) {
                return 1;
        } else {
                int cx = clipper->top_left.x;
                int cy = clipper->top_left.y;
                int h = clipper->size.height;
                int w = clipper->size.width;
                return (cx <= x && x <= (cx + w) && cy <= y && y <= (cy + h));
        }
}

void draw_segment_straight(ei_surface_t surface,
                           int x1, int x2, int y1, int y2,
                           ei_color_t color,
                           const ei_rect_t *clipper) {
        /* TODO: Transparence additionnée */
        int width = hw_surface_get_size(surface).width;
        int i, inc;
        uint32_t *pixel_ptr = (uint32_t *) hw_surface_get_buffer(surface);
        uint32_t col = ei_map_rgba(surface, color);

        /* On positionne le pointeur au départ (x1, y1) */
        pixel_ptr += x1;
        pixel_ptr += y1 * width;
        if (x1 == x2) { // Ligne verticale
                int dy = y2 - y1;
                inc = width;
                if (dy < 0) { // Parcours des pixels à l'envers
                        dy = -dy;
                        inc = -inc;
                }
                for (i = 0; i <= dy; i++) {
                        if (point_in_clipper(x1, y1 + i, clipper)) {
                                *pixel_ptr = col; // drawPixel
                        }
                        pixel_ptr += inc; // y += 1
                }
        } else { // Ligne horizontale
                int dx = x2 - x1;
                inc = 1;
                if (dx < 0) { // Parcours des pixels à l'envers
                        dx = -dx;
                        inc = -inc;
                }
                for (i = 0; i <= dx; i++) {
                        if (point_in_clipper(x1 + i, y1, clipper)) {
                                *pixel_ptr = col; // drawPixel
                        }
                        pixel_ptr += inc; // x += 1
                }
        }
}

void draw_segment_bresenham(ei_surface_t surface,
                            int x1, int y1, int dx, int dy, int sign_x, int sign_y, int swap,
                            ei_color_t color,
                            const ei_rect_t *clipper) {
        /* TODO: Transparence additionnée */
        int width = hw_surface_get_size(surface).width;
        int i, j = 0;
        int inc_x = sign_x, inc_y = (sign_y) * width; // Parcours des pixels à l'endroit ou non
        int E = 0;
        uint32_t *pixel_ptr = (uint32_t *) hw_surface_get_buffer(surface);
        uint32_t col = ei_map_rgba(surface, color);

        /* On positionne le pointeur au départ (x1, y1) */
        pixel_ptr += x1;
        pixel_ptr += y1 * width;

        if (swap == 0) {
                for (i = 0; i <= dx; i++) {
                        if (point_in_clipper(x1 + i, y1 + j, clipper)) {
                                *pixel_ptr = col; // drawPixel
                        }
                        pixel_ptr += inc_x; // x+= 1
                        E += dy;
                        if (2 * E > dx) {
                                j++;
                                pixel_ptr += inc_y; // y+= 1
                                E -= dx;
                        }
                }
        } else { // On inverse x et y
                for (i = 0; i <= dy; i++) {
                        if (point_in_clipper(x1 + j, y1 + i, clipper)) {
                                *pixel_ptr = col; // drawPixel
                        }
                        pixel_ptr += inc_y; // y+= 1 (swap)
                        E += dx;
                        if (2 * E > dy) {
                                j++;
                                pixel_ptr += inc_x; // x+= 1 (swap)
                                E -= dy;
                        }
                }
        }
}

