//
// Created by baptiste on 12/05/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "ei_types.h"


ei_linked_point_t *arc(ei_point_t centre, float rayon, float debut, float fin) {
        /* TODO: résoudre bug, cercle pas dessiné en entier */
        ei_linked_point_t *premier = malloc(sizeof(*premier));
        premier = NULL;
        if (fin >= debut) { // Parcours dans l'ordre croissant des angles
                float angle = debut;
                while (angle <= fin) {
                        ei_point_t point;
                        point.x = centre.x + (int) rayon * cos(angle);
                        point.y = centre.y + (int) rayon * sin(angle);
                        if (premier == NULL || point.x != premier->point.x || point.y != premier->point.y) {
                                ei_linked_point_t *nouveau = malloc(sizeof(*nouveau));
                                nouveau->point = point;
                                nouveau->next = premier;
                                premier = nouveau; // ajout en tete du nouveau point
                        }
                        angle = angle + 0.01;
                }
                return premier;
        } else { // Parcours dans l'ordre décroissant des angles
                float angle = debut;
                while (angle >= fin) {
                        ei_point_t point;
                        point.x = centre.x + (int) rayon * cos(angle);
                        point.y = centre.y + (int) rayon * sin(angle);
                        if (premier == NULL || point.x != premier->point.x || point.y != premier->point.y) {
                                ei_linked_point_t *nouveau = malloc(sizeof(*nouveau));
                                nouveau->point = point;
                                nouveau->next = premier;
                                premier = nouveau; // ajout en tete du nouveau point
                        }
                        angle = angle - 0.01;
                }
                return premier;
        }

}

ei_linked_point_t *rounded_frame(ei_rect_t rect, float rayon, int top_part, int bot_part)
{
        ei_linked_point_t *premier = malloc(sizeof(*premier));
        premier = NULL;
        ei_point_t centre;
        ei_linked_point_t *angle_top_left = malloc(sizeof(*angle_top_left));
        ei_linked_point_t *angle_top_right = malloc(sizeof(*angle_top_right));
        ei_linked_point_t *angle_bot_left = malloc(sizeof(*angle_bot_left));
        ei_linked_point_t *angle_bot_right = malloc(sizeof(*angle_bot_right));

        centre.x = rect.top_left.x + rayon; centre.y = rect.top_left.y + rayon;
        angle_top_left = arc(centre, rayon,M_PI, 1.5*M_PI);

        centre.x = rect.top_left.x + rect.size.width - 1 - rayon; centre.y = rect.top_left.y + rayon;
        angle_top_right = arc(centre, rayon, 1.5*M_PI, 2*M_PI);

        centre.x = rect.top_left.x + rayon; centre.y = rect.top_left.y + rect.size.height -1 - rayon;
        angle_bot_left = arc(centre, rayon, 0.5*M_PI, M_PI);

        centre.x = rect.top_left.x + rect.size.width - 1 - rayon; centre.y = rect.top_left.y + rect.size.height - 1 - rayon;
        angle_bot_right = arc(centre, rayon, 0, 0.5*M_PI);

        if(top_part == 1 && bot_part == 0){
                centre.x = rect.top_left.x + rayon; centre.y = rect.top_left.y + rayon;
                angle_top_left = arc(centre, rayon,M_PI, 1.5*M_PI);

                centre.x = rect.top_left.x + rect.size.width - 1 - rayon; centre.y = rect.top_left.y + rayon;
                angle_top_right = arc(centre, rayon, 1.5*M_PI, 1.75*M_PI);

                centre.x = rect.top_left.x + rayon; centre.y = rect.top_left.y + rect.size.height -1 - rayon;
                angle_bot_left = arc(centre, rayon, 0.25*M_PI, M_PI);

                angle_bot_right = NULL;
        }
        else if(top_part == 0 && bot_part == 1){
                angle_top_left = NULL;

                centre.x = rect.top_left.x + rect.size.width - 1 - rayon; centre.y = rect.top_left.y + rayon;
                angle_top_right = arc(centre, rayon, 1.75*M_PI, 2*M_PI);

                centre.x = rect.top_left.x + rayon; centre.y = rect.top_left.y + rect.size.height -1 - rayon;
                angle_bot_left = arc(centre, rayon, 0.5*M_PI, 0.75*M_PI);

                centre.x = rect.top_left.x + rect.size.width - 1 - rayon; centre.y = rect.top_left.y + rect.size.height - 1 - rayon;
                angle_bot_right = arc(centre, rayon, 0, 0.5*M_PI);
        }

        ei_point_t point;
        while(angle_top_right->next != NULL){ //ajout en tete de l'angle en haut à droite
                ei_linked_point_t *nouveau = malloc(sizeof(*nouveau));
                point = angle_top_right->point;
                nouveau->point = point;
                nouveau->next = premier;
                premier = nouveau;
                angle_top_right = angle_top_right->next;
        }

        while(angle_top_left->next != NULL){ //ajout en tete de l'angle en haut à gauche
                ei_linked_point_t *nouveau = malloc(sizeof(*nouveau));
                point = angle_top_left->point;
                nouveau->point = point;
                nouveau->next = premier;
                premier = nouveau;
                angle_top_left = angle_top_left->next;
        }

        while(angle_bot_left->next != NULL){ //ajout en tete de l'angle en bas à gauche
                ei_linked_point_t *nouveau = malloc(sizeof(*nouveau));
                point = angle_bot_left->point;
                nouveau->point = point;
                nouveau->next = premier;
                premier = nouveau;
                angle_bot_left = angle_bot_left->next;
        }

        while(angle_bot_right->next != NULL){ //ajout en tete de l'angle en bas à droite
                ei_linked_point_t *nouveau = malloc(sizeof(*nouveau));
                point = angle_bot_right->point;
                nouveau->point = point;
                nouveau->next = premier;
                premier = nouveau;
                angle_bot_right = angle_bot_right->next;
        }
        return premier;
}

