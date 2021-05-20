#ifndef EI_PLACER_UTILS_H
#define EI_PLACER_UTILS_H

#include "ei_widget.h"

struct anchor_shift {
	float up_direction;
	float down_direction;
	float left_direction;
	float right_direction;
};

void init_placer_params(struct ei_widget_t *widget);

void forget_placer_params(ei_widget_t *widget);

ei_bool_t is_valid_padding(float rel_c, int c, int dimension);

ei_bool_t is_valid_coord(int c, int dimension);

void manage_anchor(ei_widget_t *widget, ei_anchor_t *anchor);

void manage_coord_x(ei_widget_t *widget, int *x, float *rel_x);

void manage_coord_y(ei_widget_t *widget, int *y, float *rel_y);

struct anchor_shift init_anchor_shift(float up, float down, float left, float right);

struct anchor_shift create_anchor_shift(ei_anchor_t anchor);

ei_bool_t
is_valid_dimension(int parent_dimension, float *rel_dimension, int *dimension, int pos_c, float left, float right);

void manage_width(ei_widget_t *widget, int *width, float *rel_width);

void manage_height(ei_widget_t *widget, int *height, float *rel_height);

#endif //EI_PLACER_UTILS_H