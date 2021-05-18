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
ei_linked_point_t *arc(ei_point_t centre, float rayon, float debut, float fin);

/**
 * \brief 	Return a linked point that corresponds to rounded frame.
 *
 * @param 	rect
 * @param 	rayon
 * @param 	top_part
 * @param 	bot_part
 * @return			a linked point
 */
ei_linked_point_t *rounded_frame(ei_rect_t rect, int32_t rayon, int top_part, int bot_part);

#endif //PROJETC_IG_EI_BUTTON_H
