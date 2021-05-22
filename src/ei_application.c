#include <stdlib.h>
#include <stdio.h>

#include "ei_event.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "hw_interface.h"
#include "ei_application.h"

#include "ei_application_utils.h"

/** Global variables **/
/**                  **/
ei_bool_t DO_QUIT = EI_FALSE;
ei_surface_t ROOT_WINDOW;
ei_widget_t *ROOT_FRAME;
ei_linked_rect_t *RECTANGLE_LIST;
/**                  **/
/** ---------------- **/

/**
 * \brief	Creates an application.
 *		<ul>
 *			<li> initializes the hardware (calls \ref hw_init), </li>
 *			<li> registers all classes of widget, </li>
 *			<li> creates the root window (either in a system window, or the entire screen), </li>
 *			<li> creates the root widget to access the root window. </li>
 *		</ul>
 *
 * @param	main_window_size	If "fullscreen is false, the size of the root window of the
 *					application.
 *					If "fullscreen" is true, the current monitor resolution is
 *					used as the size of the root window. \ref hw_surface_get_size
 *					can be used with \ref ei_app_root_surface to get the size.
 * @param	fullScreen		If true, the root window is the entire screen. Otherwise, it
 *					is a system window.
 */
void ei_app_create(ei_size_t main_window_size, ei_bool_t fullscreen) {
	hw_init();

	// TODO: initialisation de toutes les classes widgets (un par un) avec ei_widgetclass_register
	// ei_widgetclass_t frameclass;
	// frameclass.name = "frame";
	// ei_widgetclass_register(&frameclass);

	// Create root window
	ROOT_WINDOW = hw_create_window(main_window_size, fullscreen);
	ei_size_t real_size = hw_surface_get_size(ROOT_WINDOW);

	// Create pick surface
	ei_surface_t pick_surface = hw_surface_create(ROOT_WINDOW, real_size, EI_FALSE);
	ei_set_pick_surface(pick_surface);

	// Create rectangle list (for ei_app_invalidate_rects)
	RECTANGLE_LIST = malloc(sizeof(ei_linked_rect_t));
	RECTANGLE_LIST = NULL;
}

/**
* \brief	Releases all the resources of the application, and releases the hardware
*		(ie. calls \ref hw_quit).
*/
void ei_app_free(void) {
	// Free every widget
	free_widget_recursively(ROOT_FRAME);

	// Free both root window and pick surface
	free_root_window(ROOT_WINDOW);

	// Release hardware
	hw_quit();
}

/**
* \brief	Runs the application: enters the main event loop. Exits when
*		\ref ei_app_quit_request is called.
*/
void ei_app_run() {
	ei_event_t event;
	ei_widget_t *active_widget = NULL;
	ei_bool_t event_handled;
	ei_rect_t big_rect;

	// Dessiner tout une première fois
	hw_surface_lock(ROOT_WINDOW);
	draw_widget_recursively(ROOT_FRAME, ROOT_WINDOW, NULL);
	hw_surface_unlock(ROOT_WINDOW);
	hw_surface_update_rects(ROOT_WINDOW, NULL);

	event.type = ei_ev_none;
	hw_event_wait_next(&event);
	while (!DO_QUIT) {
		event_handled = EI_FALSE;
		if (is_located_event(event)) {
			if (event.type == ei_ev_mouse_buttondown) { // Set active
				ei_event_set_active_widget(ei_widget_pick(&event.param.mouse.where));
			} else if (event.type == ei_ev_mouse_buttonup) { // Unset active
				ei_event_set_active_widget(NULL);
			}
		}
		active_widget = ei_event_get_active_widget();
		if (active_widget != NULL) {
			event_handled = active_widget->wclass->handlefunc(active_widget, &event);
		}
		if (!event_handled && !is_located_event(event)) {
			// Si ce n’est pas un évènement situé, le traitant concerné est celui
			// qui a été défini par le programmeur
			ei_event_get_default_handle_func()(&event);
		}

		// Update necessary rectangles
		if (RECTANGLE_LIST != NULL) {
			hw_surface_lock(ROOT_WINDOW);
			big_rect = big_union_rect(&RECTANGLE_LIST);
			draw_widget_recursively(ROOT_FRAME, ROOT_WINDOW, &big_rect);
			hw_surface_unlock(ROOT_WINDOW);
			hw_surface_update_rects(ROOT_WINDOW, NULL);
		}

		hw_event_wait_next(&event);
	}
}

/**
 * \brief	Adds a rectangle to the list of rectangles that must be updated on screen. The real
 *		update on the screen will be done at the right moment in the main loop.
 *
 * @param	rect		The rectangle to add, expressed in the root window coordinates.
 *				A copy is made, so it is safe to release the rectangle on return.
 */
void ei_app_invalidate_rect(ei_rect_t *rect) {
	ei_linked_rect_t *new = malloc(sizeof(ei_linked_rect_t));
	new->rect = *rect;
	new->next = RECTANGLE_LIST;
	RECTANGLE_LIST = new;
}

/**
 * \brief	Tells the application to quite. Is usually called by an event handler (for example
 *		when pressing the "Escape" key).
 */
void ei_app_quit_request(void) {
	DO_QUIT = EI_TRUE;
}

/**
 * \brief	Returns the "root widget" of the application: a "frame" widget that span the entire
 *		root window.
 *
 * @return 			The root widget.
 */
ei_widget_t *ei_app_root_widget(void) {
	return ROOT_FRAME;
}

/**
 * \brief	Returns the surface of the root window. Can be usesd to create surfaces with similar
 * 		r, g, b channels.
 *
 * @return 			The surface of the root window.
 */
ei_surface_t ei_app_root_surface(void) {
	return ROOT_WINDOW;
}