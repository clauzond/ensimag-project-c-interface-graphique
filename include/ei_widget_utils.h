#ifndef EI_WIDGET_UTILS_H
#define EI_WIDGET_UTILS_H

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"

typedef struct ei_frame_t {
	ei_widget_t widget; // Doit être de type "ei_widget_t" pour polymorphisme
	ei_color_t color;
	int border_width;
	ei_relief_t relief;
	char **text;
	ei_font_t text_font;
	ei_color_t text_color;
	ei_anchor_t text_anchor;
	ei_surface_t *img;
	ei_rect_t *img_rect;
	ei_anchor_t img_anchor;
} ei_frame_t;

typedef struct ei_button_t {
	ei_widget_t widget; // Doit être de type "ei_widget_t" pour polymorphisme
	ei_color_t color;
	int border_width;
	int corner_radius;
	ei_relief_t relief;
	char *text;
	ei_font_t text_font;
	ei_color_t text_color;
	ei_anchor_t text_anchor;
	ei_surface_t *img;
	ei_rect_t *img_rect;
	ei_anchor_t img_anchor;
	ei_callback_t callback;
	void *user_param;

	// Paramètres hors config
//	ei_rect_t *button_rect;
//	ei_color_t *top_color;
//	ei_color_t *bot_color;
//	ei_color_t *inside_color;
//	float *rayon;
//	ei_anchor_t *button_anchor;
} ei_button_t;

typedef struct ei_toplevel_t {
	ei_widget_t widget; // Doit être de type "ei_widget_t" pour polymorphisme
	ei_color_t color;
	int border_width;
	char *title;
	ei_bool_t closable;
	ei_axis_set_t resizable;
	ei_size_t min_size;
} ei_toplevel_t;

void empty_callback(ei_widget_t *widget, struct ei_event_t *event, void *user_param);

void ei_widget_destroy_child(ei_widget_t *widget);

ei_widget_t *ei_find_widget_by_id(uint32_t id);

ei_frame_t ei_init_default_frame();

ei_button_t ei_init_default_button();

ei_toplevel_t ei_init_default_toplevel();

#endif //EI_WIDGET_UTILS_H
