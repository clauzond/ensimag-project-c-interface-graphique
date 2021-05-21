//
// Created by baptiste on 21/05/2021.
//
#include "ei_widget.h"
#include "ei_widgetclass.h"

typedef struct ei_button_t {
        struct ei_widget_t*     widget;

        struct ei_relief_t*     relief;
        ei_font_t*              font;
        char**                  text;
        ei_color_t*             text_color;
        ei_rect_t*              button_rect;
        ei_color_t*             top_color;
        ei_color_t*             bot_color;
        ei_color_t*             inside_color;
        float*                  rayon;
        ei_anchor_t*            button_anchor;
} ei_button_t;
