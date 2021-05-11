#include <stdlib.h>

#include "ei_types.h"
#include "segment.h"
#include "assert.h"

#include "hw_interface.h"

int main(int argc, char* argv[])
{
        ei_side s1 = {0, 5, 0, 0, NULL};
        ei_side s2 = {0, 2, 0, 0, NULL};
        ei_side s3 = {0, 1, 0, 0, NULL};
        ei_side s4 = {0, 9, 0, 0, NULL};
        ei_side s5 = {0, 8, 0, 0, NULL};
        s1.next = &s2;
        s2.next = &s3;
        s3.next = &s4;
        s4.next = &s5;

        // Test swap_sides
	swap_sides(&s1, &s2);
        assert((s1.x_ymin == 2));
        assert((s1.next->x_ymin == 5));
        assert((s2.next->x_ymin == 1));
	swap_sides(&s1, &s2);

        // Test sort_side_table
        sort_side_table(&s1);
        assert((s1.x_ymin == 1));
        assert((s1.next->x_ymin == 2));
        assert((s1.next->next->x_ymin == 5));
        assert((s1.next->next->next->x_ymin == 8));
        assert((s1.next->next->next->next->x_ymin == 9));

        // Test find_intersection
        // sur les 4 exemples du schéma
        int y = 2;
        ei_side se1 = {10, 0, 1, 3, 0, NULL};
        ei_point_t point = find_intersection(y, &se1);
        assert((point.x == 0 && point.y == 2 && se1.E != 0));
        y = 2;
        ei_side se2 = {10, 0, 3, 1, 0, NULL};
        point = find_intersection(y, &se2);
        assert((point.x == 2 && point.y == 2 && se2.E != 0));
        y = 2;
        ei_side se3 = {10, 1, -1, 3, 0, NULL};
        point = find_intersection(y, &se3);
        assert((point.x == 1 && point.y == 2 && se3.E != 0));
        y = 2;
        ei_side se4 = {10, 3, -3, 1, 0, NULL};
        point = find_intersection(y, &se4);
        assert((point.x == 1 && point.y == 2 && se4.E != 0));
        // sur un exemple avec dx=0
        y = 2;
        ei_side se5 = {10, 3, 0, 1, 0, NULL};
        point = find_intersection(y, &se5);
        assert((point.x == 3 && point.y == 2 && se5.E == 0));

        // Terminate program with no error code.
        return 0;
}
