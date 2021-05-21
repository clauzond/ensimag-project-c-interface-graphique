#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_types.h"
#include "ei_event.h"
#include "ei_application.h"

#include "ei_application_utils.h"

/** Global variables **/
/**                  **/
ei_surface_t PICK_SURFACE;
/**                  **/
/** ---------------- **/

void ei_set_pick_surface(ei_surface_t surface) {
	PICK_SURFACE = surface;
}

ei_surface_t ei_get_pick_surface(void) {
	return PICK_SURFACE;
}

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

void draw_widget_recursively(ei_widget_t *widget, ei_surface_t root_window) {
	// Traitement pour un widget
	ei_rect_t *clipper = NULL;
	if (widget->parent != NULL) {
		clipper = widget->parent->content_rect;
	}
	widget->wclass->drawfunc(widget, root_window, PICK_SURFACE, clipper);

	// Prochain widget à traiter
	if (widget->next_sibling != NULL) {
		draw_widget_recursively(widget->next_sibling, root_window);
	} else if (widget->children_head != NULL) {
		draw_widget_recursively(widget->children_head, root_window);
	}
}

void free_widget_recursively(ei_widget_t *widget) {
	// TODO: pas sûr que next_sibling et children_head sont conservés, fonction à repenser après implémentation de ei_widget_destroy
	ei_widget_t *next_sibling = widget->next_sibling;
	ei_widget_t *children_head = widget->children_head;

	// Traitement pour un widget
	ei_widget_destroy(widget);

	// Prochain widget à traiter
	if (next_sibling != NULL) {
		free_widget_recursively(next_sibling);
	} else if (children_head != NULL) {
		free_widget_recursively(children_head);
	}
}

void free_root_window(ei_surface_t root_window) {
	// Free root window
	hw_surface_unlock(root_window);
	hw_surface_free(root_window);

	// Free pick surface
	hw_surface_unlock(PICK_SURFACE);
	hw_surface_free(PICK_SURFACE);
}