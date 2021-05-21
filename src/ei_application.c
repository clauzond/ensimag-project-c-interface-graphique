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
ei_surface_t root_window;
ei_widget_t *root_frame;
ei_linked_rect_t *rectangle_list;
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
	root_window = hw_create_window(main_window_size, fullscreen);
	ei_size_t real_size = hw_surface_get_size(root_window);

	// Create pick surface
	ei_surface_t pick_surface = hw_surface_create(root_window, real_size, EI_FALSE);
	ei_set_pick_surface(pick_surface);

	// Create rectangle list (for ei_app_invalidate_rects)
	rectangle_list = malloc(sizeof(ei_linked_rect_t));
	rectangle_list = NULL;
}

/**
* \brief	Releases all the resources of the application, and releases the hardware
*		(ie. calls \ref hw_quit).
*/
void ei_app_free(void) {
	// Free every widget
	free_widget_recursively(root_frame);

	// Free both root window and pick surface
	free_root_window(root_window);

	// Release hardware
	hw_quit();
}

/**
* \brief	Runs the application: enters the main event loop. Exits when
*		\ref ei_app_quit_request is called.
*/
void ei_app_run() {
	ei_event_t event;

	// Dessiner tout une fois
	draw_widget_recursively(root_frame, root_window);

	event.type = ei_ev_none;
	while (!is_quit_event(event)) {
		// Si une mise à jour nécessaire à l'écran, ei_app_invalidate_rect
		// Dès qu'on a fini le traitement (?), une fonction se charge d'update tous ces rectangles
		if (is_located_event(event)) {
			// ...
		} else {
			// ...
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
	new->next = rectangle_list;
	rectangle_list = new;
}

/**
 * \brief	Tells the application to quite. Is usually called by an event handler (for example
 *		when pressing the "Escape" key).
 */
void ei_app_quit_request(void) {
	// On suppose qu'en donnant un event "quit" à la fonction default_handle_func, cela stop la boucle
	// de ei_app_run
	ei_event_t event;
	event.type = ei_ev_app;
	int quit = get_quit_number();
	event.param.application.user_param = &quit;
	//ei_event_get_default_handle_func()(&event);

}

/**
 * \brief	Returns the "root widget" of the application: a "frame" widget that span the entire
 *		root window.
 *
 * @return 			The root widget.
 */
ei_widget_t *ei_app_root_widget(void) {
	return root_frame;
}

/**
 * \brief	Returns the surface of the root window. Can be usesd to create surfaces with similar
 * 		r, g, b channels.
 *
 * @return 			The surface of the root window.
 */
ei_surface_t ei_app_root_surface(void) {
	return root_window;
}