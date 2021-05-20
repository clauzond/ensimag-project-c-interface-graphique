#ifndef EI_APPLICATION_UTILS_H
#define EI_APPLICATION_UTILS_H

#include "ei_event.h"
#include "ei_types.h"

int get_quit_number(void);

ei_bool_t is_located_event(ei_event_t event);

ei_bool_t is_quit_event(ei_event_t event);

#endif //EI_APPLICATION_UTILS_H
