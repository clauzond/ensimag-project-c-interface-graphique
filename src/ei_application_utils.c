#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_types.h"
#include "ei_event.h"
#include "ei_application.h"

#include "ei_application_utils.h"

int get_quit_number(void) {
	return 666;
}

ei_bool_t is_located_event(ei_event_t event) {
	return (ei_bool_t) (event.type == ei_ev_mouse_buttondown || event.type == ei_ev_mouse_buttonup ||
			    event.type == ei_ev_mouse_move);
}

ei_bool_t is_quit_event(ei_event_t event) {
	int user_param = (int) event.param.application.user_param;
	return (ei_bool_t) (user_param == get_quit_number());
}

void draw_root_widget(void) {
	ei_widget_t* root_widget = ei_app_root_widget();
	ei_surface_t root_window = ei_app_root_surface();
	draw_widget_recursively(root_widget, root_window);
}

void draw_widget_recursively(ei_widget_t *widget, ei_surface_t root_window) {
	// Traitement pour un widget

	// Prochain widget à traiter
	if (widget->next_sibling != NULL) {
		draw_widget_recursively(widget->next_sibling, root_window);
	} else if (widget->children_head != NULL) {
		draw_widget_recursively(widget->children_head, root_window);
	}
}