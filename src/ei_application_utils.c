#include "ei_types.h"
#include "ei_event.h"

#include "ei_application_utils.h"

int get_quit_number(void) {
	return 666;
}

ei_bool_t is_located_event(ei_event_t event) {
	return (ei_bool_t)(event.type == ei_ev_mouse_buttondown || event.type == ei_ev_mouse_buttonup || event.type == ei_ev_mouse_move);
}

ei_bool_t is_quit_event(ei_event_t event) {
	int user_param = (int) event.param.application.user_param;
	return (ei_bool_t)(user_param == get_quit_number());
}

