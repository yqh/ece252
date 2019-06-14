/**
 * @brief  stack to for push/pop integers.   
 * @author yqhuang@uwaterloo.ca
 */

#include <stdio.h>
#include <stdlib.h>
#include "shm_stack.h"

/* Note this structure can be used by shared memory,
   since the items field points to the memory right after it.
   Hence the structure and the data items holds are in one
   continuous chunk of memory.

   The memory layout:
   +===============+
   + size          | 4 bytes
   +---------------+
   + pos           | 4 bytes
   +---------------+
   + items         | 8 bytes
   +---------------+
   + items[0]      | 4 bytes
   +---------------+
   + items[1]      | 4 bytes
   +---------------+
   + ...           | 4 bytes
   +---------------+
   + items[size-1] + 4 bytes
   +===============+
*/
/* a stack that can hold integers */
typedef struct int_stack
{
    int size;               /* the max capacity of the stack */
    int pos;                /* position of last item pushed onto the stack */
    int *items;             /* stack of stored integers */
} ISTACK;


int sizeof_shm_stack(int size)
{
    int total = sizeof(int) + sizeof(int) + sizeof (int *) + sizeof(int)*size;

    return total;
}

/* caller first call sizeof_shm_stack to allocate enough memory,
   then call the init_shm_stack to initialize the struct
 */
int init_shm_stack(ISTACK *p, int stack_size)
{
    if ( p == NULL || stack_size == 0 ) {
        return 1;
    }

    p->size = stack_size;
    p->pos  = -1;
    p->items = (int *) (p + sizeof(int) + sizeof(int) + sizeof(int *));
    return 0;
}



ISTACK *create_stack(int size)
{
    int mem_size = 0;
    ISTACK *pstack = NULL;
    
    if ( size == 0 ) {
        return NULL;
    }

    mem_size = sizeof_shm_stack(size);
    pstack = malloc(mem_size);

    if ( pstack == NULL ) {
        perror("malloc");
    } else {
        char *p = (char *)pstack;
        pstack->items = (int *) (p + sizeof(int) + sizeof(int) + sizeof(int *));
        pstack->size = size;
        pstack->pos  = -1;
    }

    return pstack;
}

void destroy_stack(ISTACK *p)
{
    if ( p != NULL ) {
        free(p);
    }
}

int is_full(ISTACK *p)
{
    if ( p == NULL ) {
        return 0;
    }

    return ( p->pos == (p->size -1) );
}

int is_empty(ISTACK *p)
{
    if ( p == NULL ) {
        return 0;
    }

    return ( p->pos == -1 );
    
}

int push(ISTACK *p, int item)
{
    if ( p == NULL ) {
        return -1;
    }

    if ( !is_full(p) ) {
        ++(p->pos);
        p->items[p->pos] = item;
        return 0;
    } else {
        return -1;
    }
}

int pop(ISTACK *p, int *p_item)
{
    if ( p == NULL ) {
        return -1;
    }

    if ( !is_empty(p) ) {
        *p_item = p->items[p->pos];
        (p->pos)--;
        return 0;
    } else {
        return 1;
    }
}

