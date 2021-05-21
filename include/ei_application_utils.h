#ifndef EI_APPLICATION_UTILS_H
#define EI_APPLICATION_UTILS_H

#include "ei_event.h"
#include "ei_types.h"

void ei_set_pick_surface(ei_surface_t surface);

ei_surface_t ei_get_pick_surface(void);

int get_quit_number(void);

ei_bool_t is_located_event(ei_event_t event);

ei_bool_t is_quit_event(ei_event_t event);

void draw_widget_recursively(ei_widget_t *widget, ei_surface_t root_window);

void free_widget_recursively(ei_widget_t *widget);

void free_root_window(ei_surface_t root_window);

#endif //EI_APPLICATION_UTILS_H
