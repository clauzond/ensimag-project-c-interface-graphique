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

        // Test swap_side
        swap_side(&s1, &s2);
        assert((s1.x_ymin == 2));
        assert((s1.next->x_ymin == 1));
        assert((s2.next->x_ymin == 5));
        swap_side(&s1, &s2);

        // Test sort_side_table
        sort_side_table(&s1);
        assert((s1.x_ymin == 1));
        assert((s1.next->x_ymin == 2));
        assert((s1.next->next->x_ymin == 5));
        assert((s1.next->next->next->x_ymin == 8));
        assert((s1.next->next->next->next->x_ymin == 9));

        // Terminate program with no error code.
        return 0;
}
