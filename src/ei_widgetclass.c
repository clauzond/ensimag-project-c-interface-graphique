#include <stdlib.h>

#include "ei_widget.h"
#include "ei_widget_utils.h"
#include "ei_widgetclass.h"
#include "ei_widgetclass_utils.h"
#include "directory.h"


/**
 * @brief	Registers a class to the program so that widgets of this class can be created.
 *		This must be done only once per widged class in the application.
 *
 * @param	widgetclass	The structure describing the class.
 */
void ei_widgetclass_register(ei_widgetclass_t *widgetclass) {
	struct dir* widget_dir = get_widget_dir();
	dir_insert(widget_dir, ei_widgetclass_stringname(widgetclass->name), widgetclass);
}

/**
 * @brief	Returns the structure describing a class, from its name.
 *
 * @param	name		The name of the class of widget.
 *
 * @return			The structure describing the class.
 */
ei_widgetclass_t *ei_widgetclass_from_name(ei_widgetclass_name_t name) {
	return dir_lookup_num(get_widget_dir(), ei_widgetclass_stringname(name));
}