//
// Created by baptiste on 12/05/2021.
//
#include <stdlib.h>
#include <stdint.h>
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

ei_linked_point_t *rounded_frame(ei_rect_t rect, float rayon) {
	/* TODO: résoudre bug, pas dessiné en entier */
	ei_linked_point_t *premier = malloc(sizeof(*premier));
	premier = NULL;
	ei_point_t centre;

	centre.x = rect.top_left.x + rayon;
	centre.y = rect.top_left.y + rayon;
	ei_linked_point_t *angle_top_left = malloc(sizeof(*angle_top_left));
	angle_top_left = arc(centre, rayon, 1.5* M_PI,  M_PI);

	centre.x = rect.top_left.x + rect.size.width - 1 - rayon;
	centre.y = rect.top_left.y + rayon;
	ei_linked_point_t *angle_top_right = malloc(sizeof(*angle_top_right));
	angle_top_right = arc(centre, rayon, 2 * M_PI, 1.5 * M_PI);

	centre.x = rect.top_left.x + rayon;
	centre.y = rect.top_left.y + rect.size.height - 1 - rayon;
	ei_linked_point_t *angle_bot_left = malloc(sizeof(*angle_bot_left));
	angle_bot_left = arc(centre, rayon, M_PI, 0.5*M_PI);

	centre.x = rect.top_left.x + rect.size.width - 1 - rayon;
	centre.y = rect.top_left.y + rect.size.height - 1 - rayon;
	ei_linked_point_t *angle_bot_right = malloc(sizeof(*angle_bot_right));
	angle_bot_right = arc(centre, rayon, 0.5 * M_PI, 0);

	premier = angle_top_left;
	ei_linked_point_t *ptr = premier;
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}
	ptr->next = angle_top_right;
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