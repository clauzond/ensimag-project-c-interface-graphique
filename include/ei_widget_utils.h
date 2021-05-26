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
	char *text;
	ei_font_t text_font;
	ei_color_t text_color;
	ei_anchor_t text_anchor;
	ei_surface_t *img;
	ei_rect_t *img_rect;
	ei_anchor_t img_anchor;
	ei_bool_t requested_bool;
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
	ei_bool_t requested_bool;
} ei_button_t;

typedef struct ei_move_mode {
        ei_bool_t move_mode_bool;
        ei_point_t last_location;
} ei_move_mode;

typedef struct ei_toplevel_t {
	ei_widget_t widget; // Doit être de type "ei_widget_t" pour polymorphisme
	ei_color_t color;
	int border_width;
	char *title;
	ei_bool_t closable;
	ei_axis_set_t resizable;
	ei_size_t min_size;
	struct ei_move_mode move_mode;
} ei_toplevel_t;

void empty_callback(ei_widget_t *widget, struct ei_event_t *event, void *user_param);

void ei_widget_destroy_child(ei_widget_t *widget);

uint32_t ei_get_widget_id(ei_widget_t *widget);

ei_widget_t *ei_find_widget_by_id(uint32_t id);

ei_widget_t *search_widget(ei_widget_t *widget, uint32_t id);

ei_size_t ei_widget_natural_size(int border_width, char *text, ei_font_t text_font, ei_rect_t *img_rect);

ei_frame_t ei_init_default_frame(void);

ei_button_t ei_init_default_button(void);

ei_toplevel_t ei_init_default_toplevel(void);

ei_widget_t *frame_allocfunc(void);

void frame_releasefunc(ei_widget_t *widget);

void frame_drawfunc(ei_widget_t *widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t *clipper);

void frame_setdefaultsfunc(ei_widget_t *widget);

void frame_geomnotifyfunc(ei_widget_t *widget, ei_rect_t rect);

ei_bool_t frame_handlefunc(ei_widget_t *widget, struct ei_event_t *event);

ei_widgetclass_t ei_init_frame_class(void);

ei_widget_t *button_allocfunc(void);

void button_releasefunc(ei_widget_t *widget);

void button_drawfunc(ei_widget_t *widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t *clipper);

void button_setdefaultsfunc(ei_widget_t *widget);

void button_geomnotifyfunc(ei_widget_t *widget, ei_rect_t rect);

ei_bool_t button_handlefunc(ei_widget_t *widget, struct ei_event_t *event);

ei_widgetclass_t ei_init_button_class(void);

ei_widget_t *toplevel_allocfunc(void);

void toplevel_releasefunc(ei_widget_t *widget);

void
toplevel_drawfunc(ei_widget_t *widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t *clipper);

void toplevel_setdefaultsfunc(ei_widget_t *widget);

void toplevel_geomnotifyfunc(ei_widget_t *widget, ei_rect_t rect);

ei_bool_t toplevel_handlefunc(ei_widget_t *widget, struct ei_event_t *event);

ei_widgetclass_t ei_init_toplevel_class(void);

void draw_toplevel (ei_surface_t surface,
                    const char *text,
                    ei_font_t font,
                    ei_color_t text_color,
                    const ei_rect_t *clipper,
                    ei_rect_t rect,
                    ei_color_t toplevel_color,
                    ei_bool_t pick,
                    int border_width);

ei_linked_point_t *rect_frame(ei_rect_t rect, ei_bool_t top_part,
                             ei_bool_t bot_part);

void draw_frame(ei_surface_t surface,
		const char *text,
		ei_font_t font,
		ei_color_t text_color,
		const ei_rect_t *clipper,
		ei_rect_t rect,
		ei_color_t frame_color,
		ei_relief_t relief,
		ei_bool_t pick);

#endif //EI_WIDGET_UTILS_H
