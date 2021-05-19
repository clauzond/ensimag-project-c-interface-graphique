//
// Created by baptiste on 12/05/2021.
//

#ifndef PROJETC_IG_EI_BUTTON_H
#define PROJETC_IG_EI_BUTTON_H

#include <stdint.h>
#include "ei_types.h"

/**
 * \brief 	Return a linked point that corresponds to the arc.
 *
 * @param 	ei_point_t centre
 * @param 	rayon
 * @param 	debut
 * @param 	fin
 * @return			a linked point
 */
ei_linked_point_t *arc(ei_point_t centre,
                       float rayon,
                       float debut,
                       float fin);

/**
 * \brief 	Return a linked point that corresponds to rounded frame.
 *
 * @param 	rect
 * @param 	rayon
 * @param 	top_part
 * @param 	bot_part
 * @return			a linked point
 */
ei_linked_point_t *rounded_frame(ei_rect_t rect,
                                 float rayon,
                                 int top_part,
                                 int bot_part);

void draw_button(ei_surface_t surface,
                 const ei_point_t *where,
                 const char *text,
                 ei_font_t font,
                 ei_color_t text_color,
                 const ei_rect_t *clipper,
                 ei_rect_t rect,
                 ei_color_t top_color,
                 ei_color_t bot_color,
                 ei_color_t inside_color,
                 float rayon);

#endif //PROJETC_IG_EI_BUTTON_H
