#include <stdint.h>
#include <stdlib.h>

#include "segment.h"
#include "ei_draw.h"
#include "ei_types.h"
#include "hw_interface.h"

int point_in_clipper(int x, int y, const ei_rect_t *clipper) {
	/* TODO: Clipping force brute à remplacer */
	
	if (clipper == NULL) {
		return 0;
	} else {
		int cx = clipper->top_left.x;
		int cy = clipper->top_left.y;
		return !(cx <= x && x <= (cx + clipper->size.width) && cy <= y && y <= (cy + clipper->size.height));
	}
}

void draw_pixel(ei_surface_t surface, uint32_t *pixel_ptr, int x, int y, ei_color_t color, const ei_rect_t *clipper) {
	if (point_in_clipper(x, y, clipper)) {
		*pixel_ptr = ei_map_rgba(surface, color);
	}
}

void draw_segment_straight(ei_surface_t surface, uint32_t **pixel_ptr,
			   int x1, int x2, int y1, int y2,
			   ei_color_t color,
			   const ei_rect_t *clipper) {
	/* TODO: Transparence additionnée */
	int width = hw_surface_get_size(surface).width;
	int i, sign = 1, inc;


	/* Pointeur positionné au départ (x1, y1) */

	if (x1 == x2) { // Ligne verticale
		int dy = y2 - y1;
		inc = width;
		if (dy < 0) { // Parcours des pixels à l'envers
			dy = -dy;
			inc = -inc;
			sign = -1;
		}
		for (i = 0; i <= dy; i++) {
			draw_pixel(surface, *pixel_ptr, x1, y1 + (sign * i), color, clipper);
			(*pixel_ptr) += inc; // y += 1
		}
	} else { // Ligne horizontale
		int dx = x2 - x1;
		inc = 1;
		sign = 1;
		if (dx < 0) { // Parcours des pixels à l'envers
			dx = -dx;
			inc = -inc;
			sign = -1;
		}
		for (i = 0; i <= dx; i++) {
			draw_pixel(surface, *pixel_ptr, x1 + (sign * i), y1, color, clipper);
			(*pixel_ptr) += inc; // x += 1
		}
	}
}

void draw_segment_bresenham(ei_surface_t surface, uint32_t **pixel_ptr,
			    int x1, int y1, int dx, int dy, int sign_x, int sign_y, int swap,
			    ei_color_t color,
			    const ei_rect_t *clipper) {
	/* TODO: Transparence additionnée */
	int width = hw_surface_get_size(surface).width;
	int i, j = 0;
	int inc_x = sign_x, inc_y = (sign_y) * width; // Parcours des pixels à l'endroit ou non
	int E = 0;

	/* Pointeur positionné au départ (x1, y1) */

	if (swap == 0) {
		for (i = 0; i <= dx; i++) {
			draw_pixel(surface, *pixel_ptr, x1 + (sign_x * i), y1 + (sign_y * j), color, clipper);
			(*pixel_ptr) += inc_x; // x+= 1
			E += dy;
			if (2 * E > dx) {
				j++;
				(*pixel_ptr) += inc_y; // y+= 1
				E -= dx;
			}
		}
	} else { // On inverse x et y
		for (i = 0; i <= dy; i++) {
			draw_pixel(surface, *pixel_ptr, x1 + (sign_x * j), y1 + (sign_y * j), color, clipper);
			(*pixel_ptr) += inc_y; // y+= 1 (swap)
			E += dx;
			if (2 * E > dy) {
				j++;
				(*pixel_ptr) += inc_x; // x+= 1 (swap)
				E -= dy;
			}
		}
	}
}

ei_side_table construct_side_table(ei_surface_t surface, const ei_linked_point_t *first_point) {
	int i, x1, x2, y1, y2, tmp, height = hw_surface_get_size(surface).height;
	ei_linked_point_t *ptr;
	ei_side **array = malloc(height * sizeof(ei_side * ));
	for (i = 0; i < height; i++) {
		array[i] = NULL;
	}
	ei_side_table tc = {0, array};
	for (ptr = first_point; ptr->next == NULL; ptr = ptr->next) {
		x1 = ptr->point.x;
		y1 = ptr->point.y;
		x2 = ptr->next->point.x;
		y2 = ptr->next->point.y;
		if (y1 == y2) { // On ignore les côtés horizontaux
			continue;
		}
		if (y2 > y1) { // point 1 correspond au ymin
			tmp = y1;
			y1 = y2;
			y2 = tmp;
			tmp = x1;
			x1 = x2;
			x2 = tmp;
		}
		ei_side *cote = malloc(sizeof(ei_side));
		cote->ymax = y2;
		cote->x_ymin = x1;
		cote->dx = abs(x2 - x1);
		cote->dy = y2 - y1;
		cote->next = NULL;
		if (tc.array[y1] == NULL) {
			tc.array[y1] = cote;
		} else {
			tc.array[y1]->next = cote;
		}
		tc.length++;
	}
	return tc;
}

void add_sides_to_tca(ei_side* sides, ei_side** tca) {
	if (sides != NULL) {
		if ((*tca) == NULL) {
			*tca = sides;
		} else {
			(*tca)->next = sides;
		}
	}
}

void delete_ymax_from_tca(ei_side **tca, int y) {
	ei_side *ptr;
	ei_side sent = {0, 0, 0, 0, tca};
	for (ptr = &sent; ptr->next != NULL; ptr = ptr->next) {
		if (ptr->next->ymax == y) {
			ei_side *to_delete = ptr->next;
			ptr->next = ptr->next->next;
			free(to_delete);
		}
	}
	*tca = sent.next;
}

void swap_side(ei_side *s1, ei_side *s2) {
	int tmp1, tmp2, tmp3, tmp4;
	ei_side *tmp5;
	tmp1 = s1->ymax;
	tmp2 = s1->x_ymin;
	tmp3 = s1->dx;
	tmp4 = s1->dy;
	tmp5 = s1->next;

	s1->ymax = s2->ymax;
	s1->x_ymin = s2->x_ymin;
	s1->dx = s2->dx;
	s1->dy = s2->dy;
	s1->next = s2->next;

	s2->ymax = tmp1;
	s2->x_ymin = tmp2;
	s2->dx = tmp3;
	s2->dy = tmp4;
	s2->next = tmp5;
}

void sort_side_table(ei_side *side) {
	ei_side *i, *j, *min;
	for (i = side; i->next != NULL; i = i->next) {
		min = i;
		for (j = i->next; j != NULL; j = j->next) {
			if (j->x_ymin < min->x_ymin) {
				min = j;
			}
		}
		if (min != i) { // Swap min and i
			swap_side(min, i);
		}
	}
}

void draw_scanline(ei_surface_t surface, uint32_t **pixel_ptr, ei_side *tca, int y, ei_color_t color,
		   const ei_rect_t *clipper) {
	int drawing = 1, x;
	ei_side sent = {0, 0, 0, 0, tca};
	ei_side *ptr;
	for (ptr = &sent; ptr->next != NULL; ptr = ptr->next) {
		if (drawing) {
			for (x = ptr->x_ymin; x < ptr->next->x_ymin; x++) {
				draw_pixel(surface, *pixel_ptr, x, y, color, clipper);
				*pixel_ptr += 1;
			}
			drawing = 0;
		} else {
			*pixel_ptr += (ptr->next->x_ymin) - (ptr->x_ymin);
			drawing = 1;
		}
	}
	*pixel_ptr += hw_surface_get_size(surface).width - ptr->x_ymin;
}

ei_point_t find_intersection(int y, ei_side side) {
	// Cas |dx| < |dy|
}


void update_scanline(ei_surface_t surface, ei_side *tca, int y) {
	ei_side* ptr;
	ei_point_t point;
	for (ptr = tca; ptr == NULL; ptr = ptr->next) {
		// On veut trouver l'intersection entre le côté et la scanline
		// x_ymin sera l'abscisse de cette intersection
		point = find_intersection(y, *ptr);
	}
	}
}

//liste tri(liste L)
//{
//      liste i,j,min;
//      int aux;
//      for (i=L; i->suiv != NULL; i=i->suiv)
//      {
//              min=i;
//              for (j=i->suiv; j != NULL; j=j->suiv)
//              {
//                      if (j->val < min->val)
//                      {
//                              min=j;
//                      }
//		}
//              if (min != i)
//              {
//                      aux=min->val;
//                      min->val = i->val;
//                      i->val = aux;
//              }
//      }
//      return(L);
//}