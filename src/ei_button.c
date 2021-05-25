//
// Created by baptiste on 12/05/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "ei_types.h"
#include "ei_draw.h"
#include "ei_button.h"
#include "ei_free.h"


ei_linked_point_t *arc(ei_point_t centre,
                       float rayon,
                       float debut,
                       float fin) {
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
        }
        return premier;
}

ei_linked_point_t *rounded_frame (ei_rect_t rect,
                                 float rayon,
                                 ei_bool_t top_part,
                                 ei_bool_t bot_part) {
        /* TODO: résoudre bug, pas dessiné en entier */
        ei_linked_point_t *premier = NULL;
        ei_point_t centre;

        centre.x = rect.top_left.x + rayon;
        centre.y = rect.top_left.y + rayon;
        ei_linked_point_t *angle_top_left = arc(centre, rayon, 1.5 * M_PI, M_PI);
        if(top_part == 0){
                angle_top_left = NULL;
        }

        centre.x = rect.top_left.x + rect.size.width - 1 - rayon;
        centre.y = rect.top_left.y + rayon;
        ei_linked_point_t *angle_top_right = arc(centre, rayon, (2 - 0.25 * (1 - bot_part)) * M_PI , (1.5 + 0.25 * (1 - top_part)) * M_PI);

        centre.x = rect.top_left.x + rayon;
        centre.y = rect.top_left.y + rect.size.height - 1 - rayon;
        ei_linked_point_t *angle_bot_left = arc(centre, rayon, (1 - 0.25 * (1 - top_part)) * M_PI, (0.5 + 0.25 * (1 - bot_part)) * M_PI);

        centre.x = rect.top_left.x + rect.size.width - 1 - rayon;
        centre.y = rect.top_left.y + rect.size.height - 1 - rayon;
        ei_linked_point_t *angle_bot_right = arc(centre, rayon, 0.5 * M_PI, 0);

        if(bot_part == 0){
                angle_bot_right = NULL;
        }

        ei_linked_point_t *ptr;
        if(angle_top_left != NULL){
                premier = angle_top_left;
                ptr = premier;
                while (ptr->next != NULL) {
                        ptr = ptr->next;
                }
                ptr->next = angle_top_right;
        }
        else{
                premier = angle_top_right;
                ptr = premier;
        }
        while (ptr->next != NULL) {
                ptr = ptr->next;
        }
        ptr->next = angle_bot_right;
        while (ptr->next != NULL) {
                ptr = ptr->next;
        }
        ptr->next = angle_bot_left;
        while (ptr->next != NULL) {
                ptr = ptr->next;
        }
        ei_linked_point_t *last = malloc(sizeof(*last));
        last->next = NULL;
        last->point = premier->point;
        ptr->next = last;
        return premier;
}

void draw_button(ei_surface_t surface,
                 const char *text,
                 ei_font_t font,
                 ei_color_t text_color,
                 const ei_rect_t *clipper,
                 ei_rect_t rect,
                 ei_color_t button_color,
                 float rayon,
                 ei_relief_t relief,
                 ei_bool_t pick) {
        ei_color_t top_color;
        ei_color_t bot_color;
        if (pick == EI_TRUE) {
                ei_linked_point_t *pts = rounded_frame(rect, rayon, EI_TRUE,EI_TRUE);
                ei_draw_polygon(surface, pts, button_color, clipper);
                free_points(pts);
        }
        else {
                if(relief == ei_relief_sunken) {
                        top_color.red = button_color.red * 0.9; top_color.green = button_color.green * 0.9;
                        top_color.blue = button_color.blue * 0.9, top_color.alpha = button_color.alpha;
                        bot_color.red = button_color.red * 1.1; bot_color.green = button_color.green * 1.1;
                        bot_color.blue = button_color.blue * 1.1, bot_color.alpha = button_color.alpha;
                }
                else {
                        top_color.red = button_color.red * 1.1; top_color.green = button_color.green * 1.1;
                        top_color.blue = button_color.blue * 1.1, top_color.alpha = button_color.alpha;
                        bot_color.red = button_color.red * 0.9; bot_color.green = button_color.green * 0.9;
                        bot_color.blue = button_color.blue * 0.9, bot_color.alpha = button_color.alpha;
                }
                ei_linked_point_t *pts = rounded_frame(rect, rayon, EI_TRUE,EI_FALSE);
                ei_draw_polygon(surface, pts, top_color, clipper);
                free_points(pts);
                pts = rounded_frame(rect, rayon, EI_FALSE,EI_TRUE);
                ei_draw_polygon(surface, pts, bot_color, clipper);
                free_points(pts);
                rect.top_left.x += rect.size.width/20;
                rect.top_left.y += rect.size.height/20;
                rect.size.width -= rect.size.width*2/20;
                rect.size.height -= rect.size.height * 2/20;
                pts = rounded_frame(rect, rayon, EI_TRUE, EI_TRUE);
                ei_draw_polygon(surface, pts, button_color, clipper);
                free_points(pts);
                ei_point_t where; where.x = rect.top_left.x + rect.size.width*1.5/10; where.y = rect.top_left.y + rect.size.height*3/10;
                ei_draw_text(surface, &where, text, font, text_color, clipper);
        }

}
