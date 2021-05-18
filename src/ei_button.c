//
// Created by baptiste on 12/05/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "ei_types.h"


ei_linked_point_t *arc(ei_point_t centre, float rayon, float debut, float fin)
{
        ei_linked_point_t *premier = malloc(sizeof(*premier));
        premier = NULL;
        if(fin >= debut){ //Parcourt dans l'ordre croissant des angles
                float angle = debut;
                ei_point_t point;
                while(angle <= fin){
                        ei_linked_point_t *nouveau = malloc(sizeof(*nouveau));
                        point.x = centre.x +  (int) rayon*cos(angle);
                        point.y = centre.y +  (int) rayon*sin(angle);
                        nouveau->point = point;
                        nouveau->next = premier;
                        premier = nouveau; // ajout en tete du nouveau point
                        angle = angle + 0.01;
                }
                return premier;
        }
        else{ //Parcourt dans l'ordre décroissant des angles
                float angle = debut;
                ei_point_t point;
                while(angle >= fin){
                        ei_linked_point_t *nouveau = malloc(sizeof(*nouveau));
                        point.x = centre.x +  (int) rayon*cos(angle);
                        point.y = centre.y +  (int) rayon*sin(angle);
                        nouveau->point = point;
                        nouveau->next = premier;
                        premier = nouveau; // ajout en tete du nouveau point
                        angle = angle - 0.01;
                }
                return premier;
        }

}

ei_linked_point_t *rounded_frame(ei_rect_t rect, float rayon)
{
        ei_linked_point_t *premier = malloc(sizeof(*premier));
        premier = NULL;
        ei_point_t centre;

        centre.x = rect.top_left.x + rayon; centre.y = rect.top_left.y + rayon;
        ei_linked_point_t *angle_top_left = malloc(sizeof(*angle_top_left));
        angle_top_left = arc(centre, rayon,M_PI, 1.5*M_PI);

        centre.x = rect.top_left.x + rect.size.width - 1 - rayon; centre.y = rect.top_left.y + rayon;
        ei_linked_point_t *angle_top_right = malloc(sizeof(*angle_top_right));
        angle_top_right = arc(centre, rayon, 1.5*M_PI, 2*M_PI);

        centre.x = rect.top_left.x + rayon; centre.y = rect.top_left.y + rect.size.height -1 - rayon;
        ei_linked_point_t *angle_bot_left = malloc(sizeof(*angle_bot_left));
        angle_bot_left = arc(centre, rayon, 0.5*M_PI, M_PI);

        centre.x = rect.top_left.x + rect.size.width - 1 - rayon; centre.y = rect.top_left.y + rect.size.height - 1 - rayon;
        ei_linked_point_t *angle_bot_right = malloc(sizeof(*angle_bot_right));
        angle_bot_right = arc(centre, rayon, 0, 0.5*M_PI);
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