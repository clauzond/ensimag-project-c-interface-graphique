#include <stdlib.h>

#include "ei_widget.h"

#include "ei_placer_utils.h"


void init_placer_params(struct ei_widget_t *widget) {
	if (widget->placer_params != NULL) {
		return;
	}
	// If not managed by placer, create placer_params
	ei_placer_params_t *param = malloc(sizeof(ei_placer_params_t));
	param->anchor = malloc(sizeof(ei_anchor_t));
	param->anchor = NULL;
	param->x = malloc(sizeof(int));
	param->x = NULL;
	param->y = malloc(sizeof(int));
	param->y = NULL;
	param->w = malloc(sizeof(int));
	param->w = NULL;
	param->h = malloc(sizeof(int));
	param->h = NULL;
	param->rx = malloc(sizeof(float));
	param->rx = NULL;
	param->ry = malloc(sizeof(float));
	param->ry = NULL;
	param->rw = malloc(sizeof(float));
	param->rw = NULL;
	param->rh = malloc(sizeof(float));
	param->rh = NULL;

	widget->placer_params = param;
}

ei_bool_t is_valid_padding(float rel_c, int c, int dimension) {
	int pos_c = c + rel_c * dimension;
	return (ei_bool_t) (0 <= pos_c && pos_c <= dimension);
}

ei_bool_t is_valid_coord(int c, int dimension) {
	return (ei_bool_t) (0 <= c && c < dimension);
}

void manage_anchor(ei_widget_t *widget, ei_anchor_t *anchor) {
	if (anchor != NULL) {
		widget->placer_params->anchor = anchor;
		widget->placer_params->anchor_data = *anchor;
	}
}

void manage_coord_x(ei_widget_t *widget, int* x, float* rel_x) {
	// Gestion x
	// 0. rel_x - padding with x or no padding
	// 1. x
	// 2. default value (placer_params)
	// 3. x = 0, rel_x = 0.0
	if (rel_x != NULL && (0 <= *rel_x && *rel_x <= 1)) {
		if (x != NULL && is_valid_padding(*rel_x, *x, widget->parent->content_rect->size.width)) {
			widget->placer_params->rx = rel_x;
			widget->placer_params->rx_data = *rel_x;
			widget->placer_params->x = x;
			widget->placer_params->x_data = *x;
		} else {
			widget->placer_params->rx = rel_x;
			widget->placer_params->rx_data = *rel_x;
			widget->placer_params->x = NULL;
			widget->placer_params->x_data = 0;
		}
	} else if (x != NULL && is_valid_coord(*x, widget->parent->content_rect->size.width)) {
		widget->placer_params->x = x;
		widget->placer_params->x_data = *x;
	} else if (widget->placer_params->rx == NULL) {
		if (widget->placer_params->x == NULL) {
			widget->placer_params->rx = NULL;
			widget->placer_params->rx_data = 0;
			widget->placer_params->x = NULL;
			widget->placer_params->x_data = 0;
		}
	}
}

void manage_coord_y(ei_widget_t *widget, int* y, float* rel_y) {
	// Gestion y
	// 0. rel_y - padding with y or no padding
	// 1. y
	// 2. default value (placer_params)
	// 3. y = 0, rel_y = 0.0
	if (rel_y != NULL && (0 <= *rel_y && *rel_y <= 1)) {
		if (y != NULL && is_valid_padding(*rel_y, *y, widget->parent->content_rect->size.height)) {
			widget->placer_params->ry = rel_y;
			widget->placer_params->ry_data = *rel_y;
			widget->placer_params->y = y;
			widget->placer_params->y_data = *y;
		} else {
			widget->placer_params->ry = rel_y;
			widget->placer_params->ry_data = *rel_y;
			widget->placer_params->y = NULL;
			widget->placer_params->y_data = 0;
		}
	} else if (y != NULL && is_valid_coord(*y, widget->parent->content_rect->size.height)) {
		widget->placer_params->y = y;
		widget->placer_params->y_data = *y;
	} else if (widget->placer_params->ry == NULL) {
		if (widget->placer_params->y == NULL) {
			widget->placer_params->ry = NULL;
			widget->placer_params->ry_data = 0;
			widget->placer_params->y = NULL;
			widget->placer_params->y_data = 0;
		}
	}
}

void manage_width(ei_widget_t *widget, int* width, float* rel_width) {
	// Gestion width
	// 0. Paramètres
	// 1. requested_size
	// 2. valeur par default (placer_params)
	// 3. = 0
}

void manage_height(ei_widget_t *widget, int* height, float* rel_height) {
	// Gestion height
	// 0. Paramètres
	// 1. requested_size
	// 2. valeur default (placer_params)
	// 3. = 0
}


