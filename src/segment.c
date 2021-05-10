#include <stdint.h>
#include "ei_draw.h"
#include "ei_types.h"
#include "hw_interface.h"

void draw_segment_straight(ei_surface_t surface,
                           int x1, int x2, int y1, int y2,
                           ei_color_t color,
                           const ei_rect_t *clipper) {
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

        /* On positionne le pointeur au départ (x1, y1) */
        pixel_ptr += x1;
        pixel_ptr += y1 * width;

        E = 0;
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
}