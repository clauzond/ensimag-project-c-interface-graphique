#include <stdlib.h>

#include "ei_utils.h"
#include "ei_types.h"
#include "ei_widget.h"

#include "ei_widget_utils.h"

void empty_callback(ei_widget_t *widget, struct ei_event_t *event, void *user_param) {
	return;
}

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

ei_size_t ei_widget_natural_size(int border_width, char *text, ei_font_t text_font, ei_rect_t *img_rect) {
	ei_size_t requested_size;
	if (text != NULL) {
		hw_text_compute_size(text, text_font, &requested_size.width, &requested_size.height);
	} else if (img_rect != NULL) {
		requested_size = img_rect->size;
	} else {
		requested_size = ei_size_zero();
	}
	requested_size.width += border_width;
	requested_size.height += border_width;
	return requested_size;
}

ei_frame_t ei_init_default_frame() {
	ei_frame_t frame;
	// frame.widget is not initialized
	frame.color = ei_default_background_color;
	frame.border_width = 0;
	frame.relief = ei_relief_none;
	frame.text = NULL;
	frame.text_font = ei_default_font;
	frame.text_color = ei_font_default_color;
	frame.text_anchor = ei_anc_center;
	frame.img = NULL;
	frame.img_rect = NULL;
	frame.img_anchor = ei_anc_center;
	frame.requested_bool = EI_FALSE;
	return frame;
}

ei_button_t ei_init_default_button() {
	ei_button_t button;
	// button.widget is not initialized
	button.color = ei_default_background_color;
	button.border_width = k_default_button_border_width;
	button.corner_radius = k_default_button_corner_radius;
	button.relief = ei_relief_raised;
	button.text = NULL;
	button.text_font = ei_default_font;
	button.text_color = ei_font_default_color;
	button.text_anchor = ei_anc_center;
	button.img = NULL;
	button.img_rect = NULL;
	button.img_anchor = ei_anc_center;
	button.callback = empty_callback;
	button.user_param = NULL;
	button.requested_bool = EI_FALSE;
}

ei_toplevel_t ei_init_default_toplevel() {
	ei_toplevel_t toplevel;
	// toplevel.widget is not initialized
	toplevel.color = ei_default_background_color;
	toplevel.border_width = 4;
	toplevel.title = "Toplevel";
	toplevel.closable = EI_TRUE;
	toplevel.resizable = ei_axis_both;
	toplevel.min_size = ei_size(160, 120);
}