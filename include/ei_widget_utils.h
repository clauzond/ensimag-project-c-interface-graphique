#ifndef EI_WIDGET_UTILS_H
#define EI_WIDGET_UTILS_H

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_widgetclass.h"

void ei_widget_destroy_child(ei_widget_t *widget);

ei_widget_t *ei_find_widget_by_id(uint32_t id);

#endif //EI_WIDGET_UTILS_H
