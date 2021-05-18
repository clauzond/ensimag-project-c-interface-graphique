//
// Created by baptiste on 12/05/2021.
//

#ifndef PROJETC_IG_EI_BUTTON_H
#define PROJETC_IG_EI_BUTTON_H

#include <stdint.h>
#include "ei_types.h"

ei_linked_point_t *arc(ei_point_t centre, float rayon, float debut, float fin);

ei_linked_point_t *rounded_frame(ei_rect_t rect, int32_t rayon);

#endif //PROJETC_IG_EI_BUTTON_H
