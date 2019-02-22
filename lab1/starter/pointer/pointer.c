/**
 * @file:  pointer.c
 * @brief: To demonstrate C structure and pointer usage 
 */
#include <stdio.h>
#include <stdlib.h>

/* To model a point on 2D terminal screen */
struct point {
    int x;  /* x coordinate */
    int y;  /* y coordinate */
};


int main(void)
{
    /* The memory of a_point is allocated on the process stack at run time */
    struct point a_point;

    /* The ptr contains the address of a_point variable */
    struct point *ptr = &a_point;

    /* First method: set the value of a point structure through a struct variable*/
    a_point.x = 0;
    a_point.y = 1;
    /* Use debugger: we can see the following are true: 
       a_point.x == 0;
       ptr->x    == 0;

       a_point.y == 1; 
       ptr->y    == 1.
       */


    /* Second method: set the value of a point structure through a pointer */
    ptr->x = 3;
    ptr->y = 4;
    /* Use debugger: we can see the following are true: 
       a_point.x == 3;
       ptr->x    == 3;

       a_point.y == 4; 
       ptr->y    == 4.
       */

    /* Third method: set the value of a point structure by deferencing a pointer */
    (*ptr).x = 5;
    (*ptr).y = 6;

    /* Use debugger: we can see the following are true: 
       a_point.x == 5;
       ptr->x    == 5;

       a_point.y == 6; 
       ptr->y    == 6.
       */

    /* Switch the ptr to memory dynamically allocated from heap */
    ptr = (struct point *)malloc(sizeof(struct point));


    /* 
       Assign new value to the new point 
       NOTE that ptr no longer points to a_point!
       */
    ptr->x = 10;
    ptr->y = 11; 

    /* 
       Use debugger: we can see the following are true: 
       a_point.x == 5 ;
       ptr->x    == 10;

       a_point.y == 6 ;
       ptr->y    == 11.
       */

    free(ptr);

    return(0);
}
