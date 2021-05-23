#include <stdlib.h>

#include "ei_widget.h"

void ei_widget_destroy_child(ei_widget_t *widget) {
	// Call destructor if provided
	widget->destructor(widget);

	// Destroys its descendants
	ei_widget_t *ptr = widget->children_head;
	ei_widget_t *old = widget->children_head;
	while (ptr != NULL) {
		ptr = ptr->next_sibling;
		ei_widget_destroy_child(old);
		old = ptr;
	}

	// No need to link correctly between siblings and parent

	// Frees memory
	widget->wclass->releasefunc(widget);
}

ei_widget_t *ei_find_widget_by_id(uint32_t id) {

}

#include "ei_widget_utils.h"