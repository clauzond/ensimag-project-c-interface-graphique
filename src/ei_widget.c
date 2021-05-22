//
// Created by baptiste on 21/05/2021.
//
#include <stdlib.h>
#include <stdio.h>

#include "ei_widget.h"
#include "ei_widgetclass.h"
#include "ei_types.h"

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

void			ei_button_configure		        (ei_widget_t*		widget,
                                                                ei_size_t*		requested_size,
                                                                const ei_color_t*	color,
                                                                int*			border_width,
                                                                int*			corner_radius,
                                                                ei_relief_t*		relief,
                                                                char**			text,
                                                                ei_font_t*		text_font,
                                                                ei_color_t*		text_color,
                                                                ei_anchor_t*		text_anchor,
                                                                ei_surface_t*		img,
                                                                ei_rect_t**		img_rect,
                                                                ei_anchor_t*		img_anchor,
                                                                ei_callback_t*		callback,
                                                                void**			user_param) {
        /* TODO: requested_size */
        if(color == NULL){
//                widget->wclass-> = ei_default_background_color;
        }
        if(border_width == NULL){
                border_width = k_default_button_border_width;
        }
        if(corner_radius == NULL){
                corner_radius = k_default_button_corner_radius;
        }
        if(relief == NULL){
                relief = ei_relief_none;
        }
        if(text_font == NULL){
                text_font = ei_default_font;
        }
        if(text_color == NULL){
//                text_color = ei_font_default_color;
        }
        if(text_anchor == NULL){
                text_anchor = ei_anc_center;
        }
        if(img_anchor == NULL){
                img_anchor = ei_anc_center;
        }

}