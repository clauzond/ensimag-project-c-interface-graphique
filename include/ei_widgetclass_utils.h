#ifndef EI_WIDGETCLASS_UTILS_H
#define EI_WIDGETCLASS_UTILS_H

#include "directory.h"

struct dir* get_widget_dir(void);

void free_widget_dir(void);

void set_first_widgetclass(ei_widgetclass_t *wclass);

#endif //EI_WIDGETCLASS_UTILS_H
