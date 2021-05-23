//
// Created by baptiste on 21/05/2021.
//
#include <stdlib.h>
#include <stdio.h>

#include "ei_free.h"
#include"ei_types.h"
#include"ei_free.h"

void free_points(ei_linked_point_t *ptr) {
	ei_linked_point_t *point;
	while (ptr != NULL) {
		point = ptr->next;
		free(ptr);
		ptr = point;
	}
}