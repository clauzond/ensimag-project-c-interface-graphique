#include "ei_widgetclass_utils.h"
#include "directory.h"


/** Global variables **/
/**                  **/
struct dir* widget_dir = NULL;
/**                  **/
/** ---------------- **/

struct dir* get_widget_dir(void) {
	if (widget_dir == NULL) {
		widget_dir = dir_create(10);
	}
	return widget_dir;
}

void free_widget_dir(void) {
	dir_free(widget_dir);
}