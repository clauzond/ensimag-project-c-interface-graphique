#ifndef EI_PLACER_UTILS_H
#define EI_PLACER_UTILS_H

#include "ei_widget.h"

void init_placer_params(struct ei_widget_t *widget);

ei_bool_t is_valid_padding(float rel_c, int c, int dimension);

ei_bool_t is_valid_coord(int c, int dimension);

void manage_coord_x(ei_widget_t *widget, int* x, float* rel_x);

void manage_coord_y(ei_widget_t *widget, int* y, float* rel_y);

void manage_width(ei_widget_t *widget, int* width, float* rel_width);

void manage_height(ei_widget_t *widget, int* height, float* rel_height);

#endif //EI_PLACER_UTILS_H