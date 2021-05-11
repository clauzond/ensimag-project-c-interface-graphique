#include "ei_application.h"
#include "ei_widgetclass.h"
#include "hw_interface.h"

void ei_app_create(ei_size_t main_window_size, ei_bool_t fullscreen);
    hw_init();
    // TODO: initialisation de tous les widgets avec ei_widgetclass_register
    ei_widgetclass_register(root)
    ei_surface_t main_window = hw_create_window(main_window_size, fullscreen);
    ei_size_t real_size = hw_surface_get_size(main_window);
    ei_surface_t offscreen = hw_surface_create(main_window, real_size, FALSE);
    ei_widget_t* frame_root = ei_widget_create(root, NULL, NULL, NULL );
    ei_app_run();

