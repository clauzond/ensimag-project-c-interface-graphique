#include <stdlib.h>
#include <stdio.h>

#include "ei_application.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_types.h"

#include "ei_widget_utils.h"
#include "ei_application_utils.h"

/**
 * @brief	Creates a new instance of a widget of some particular class, as a descendant of
 *		an existing widget.
 *
 *		The widget is not displayed on screen until it is managed by a geometry manager.
 *		When no more needed, the widget must be released by calling \ref ei_widget_destroy.
 *
 * @param	class_name	The name of the class of the widget that is to be created.
 * @param	parent 		A pointer to the parent widget. Can not be NULL.
 * @param	user_data	A pointer provided by the programmer for private use. May be NULL.
 * @param	destructor	A pointer to a function to call before destroying a widget structure. May be NULL.
 *
 * @return			The newly created widget, or NULL if there was an error.
 */
ei_widget_t *ei_widget_create(ei_widgetclass_name_t class_name,
			      ei_widget_t *parent,
			      void *user_data,
			      ei_widget_destructor_t destructor) {
	// TODO: Vérification que la classe dont le nom a été passé en paramètre est connue par la bibliothèque

	// TODO: Appel de la fonction d'allocation de widgets de la classe

	// Initialisation des attributs communs à tous les widgets
	ei_widget_t *widget;
	widget->wclass = class_name;
	widget->user_data = user_data;
	widget->destructor = destructor;

	// Widget Hierachy Management
	widget->parent = parent;

	if (widget->parent->children_head != NULL) {
		widget->next_sibling = widget->parent->children_head->next_sibling;
		widget->parent->children_head->next_sibling = widget;
	} else {
		widget->parent->children_head = widget;
		ei_widget_t *ptr = widget->parent;
		while (ptr != NULL) {
			ptr->children_tail = widget;
			ptr = ptr->parent;
		}
		widget->next_sibling = NULL;
	}
	widget->children_head = NULL;
	widget->children_tail = NULL;

	// TODO: Appel de la fonction d'initialisation des attributs spécifiques à la classe

	return widget;
}


/**
 * @brief	Destroys a widget. Calls its destructor if it was provided.
 * 		Removes the widget from the screen if it is currently managed by the placer.
 * 		Destroys all its descendants.
 *
 * @param	widget		The widget that is to be destroyed.
 */
void ei_widget_destroy(ei_widget_t *widget) {
	// Call destructor if provided
	widget->destructor(widget);

	// Removes from screen if managed by placer
	if (widget->placer_params != NULL) {
		ei_app_invalidate_rect(&widget->screen_location); // Includes content_rect
		ei_placer_forget(widget);
	}

	// Destroys its descendants
	ei_widget_t *ptr = widget->children_head;
	ei_widget_t *old = widget->children_head;
	while (ptr != NULL) {
		ptr = ptr->next_sibling;
		ei_widget_destroy_child(old);
		old = ptr;
	}

	// Link correctly between siblings and parent (parcours linéaire)
	// TODO: link correctly

	// Frees memory
	widget->wclass->releasefunc(widget);
}


/**
 * @brief	Returns the widget that is at a given location on screen.
 *
 * @param	where		The location on screen, expressed in the root window coordinates.
 *
 * @return			The top-most widget at this location, or NULL if there is no widget
 *				at this location (except for the root widget).
 */
ei_widget_t *ei_widget_pick(ei_point_t *where) {
	ei_surface_t pick_surface = ei_get_pick_surface();
	hw_surface_set_origin(pick_surface, *where);
	uint32_t *pixel_ptr = (uint32_t *) hw_surface_get_buffer(pick_surface);
	return ei_find_widget_by_id(*pixel_ptr);
}


typedef struct ei_frame_t {
	ei_widget_t *widget; // Doit être de type "ei_widget_t" pour polymorphisme
	ei_size_t *requested_size;
	const ei_color_t *color;
	int *border_width;
	ei_relief_t *relief;
	char **text;
	ei_font_t *text_font;
	ei_color_t *text_color;
	ei_anchor_t *text_anchor;
	ei_surface_t *img;
	ei_rect_t **img_rect;
	ei_anchor_t *img_anchor;
} ei_frame_t;


void ei_frame_configure(ei_widget_t *widget,
			ei_size_t *requested_size,
			const ei_color_t *color,
			int *border_width,
			ei_relief_t *relief,
			char **text,
			ei_font_t *text_font,
			ei_color_t *text_color,
			ei_anchor_t *text_anchor,
			ei_surface_t *img,
			ei_rect_t **img_rect,
			ei_anchor_t *img_anchor) {
	// Polymorphisme
	ei_frame_t *button = (ei_frame_t *)widget;
}


typedef struct ei_button_t {
	ei_widget_t widget; // Doit être de type "ei_widget_t" pour polymorphisme
	ei_size_t *requested_size;
	const ei_color_t *color;
	int *border_width;
	int *corner_radius;
	ei_relief_t *relief;
	char **text;
	ei_font_t *text_font;
	ei_color_t *text_color;
	ei_anchor_t *text_anchor;
	ei_surface_t *img;
	ei_rect_t **img_rect;
	ei_anchor_t *img_anchor;
	ei_callback_t *callback;
	void **user_param;

	// Paramètres hors config
	ei_rect_t *button_rect;
	ei_color_t *top_color;
	ei_color_t *bot_color;
	ei_color_t *inside_color;
	float *rayon;
	ei_anchor_t *button_anchor;
} ei_button_t;


void ei_button_configure(ei_widget_t *widget,
			 ei_size_t *requested_size,
			 const ei_color_t *color,
			 int *border_width,
			 int *corner_radius,
			 ei_relief_t *relief,
			 char **text,
			 ei_font_t *text_font,
			 ei_color_t *text_color,
			 ei_anchor_t *text_anchor,
			 ei_surface_t *img,
			 ei_rect_t **img_rect,
			 ei_anchor_t *img_anchor,
			 ei_callback_t *callback,
			 void **user_param) {
	// Polymorphisme
	ei_button_t *button = (ei_button_t *)widget;

	/* TODO: requested_size */
	if (color == NULL) {
//                widget->wclass-> = ei_default_background_color;
	}
	if (border_width == NULL) {
		border_width = k_default_button_border_width;
	}
	if (corner_radius == NULL) {
		corner_radius = k_default_button_corner_radius;
	}
	if (relief == NULL) {
		relief = ei_relief_none;
	}
	if (text_font == NULL) {
		text_font = ei_default_font;
	}
	if (text_color == NULL) {
//                text_color = ei_font_default_color;
	}
	if (text_anchor == NULL) {
		text_anchor = ei_anc_center;
	}
	if (img_anchor == NULL) {
		img_anchor = ei_anc_center;
	}

}


void ei_toplevel_configure(ei_widget_t *widget,
			   ei_size_t *requested_size,
			   ei_color_t *color,
			   int *border_width,
			   char **title,
			   ei_bool_t *closable,
			   ei_axis_set_t *resizable,
			   ei_size_t **min_size) {

}
