/**
 * @brief  A shared memory that makes use of C struct 
 * @author yqhuang@uwaterloo.ca
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <semaphore.h>
#include "shm_stack.h"

#define STACK_SIZE 3

/* pushing three items to the stack */
void push3(struct int_stack *p, int start)
{
    int i;
    
    if ( p == NULL) {
        abort();
    }
    
    for( i = 0; ; i++ )  {
        int ret;
        int item = start - i;

        ret = push(p, item);
        if ( ret != 0 ) {
            break;
        }
        printf("item[%d] = 0x%4X pushed onto the stack\n", i, item);
 
    }
    printf("%d items pushed onto the stack.\n", i);
    
}

/* pop three items off the stack */
void pop3(struct int_stack *p)
{
    int i;
    if ( p == NULL) {
        abort();
    }

    for ( i = 0; ; i++ ) {
        int item;
        int ret = pop(p, &item);
        if ( ret != 0 ) {
            break;
        }
        printf("item[%d] = 0x%4X popped\n", i, item);
    }

    printf("%d items popped off the stack.\n", i);

}

void test_local()
{
    int i;
    struct int_stack *pstack;

    if ( (pstack = create_stack(STACK_SIZE)) == NULL) {
        fprintf(stderr, "Failed to create a new stack, abort...\n");
        abort();
    };

    push3(pstack, 0xFF00);
    pop3(pstack);
    destroy_stack(pstack);
}

void test_shm()
{
    int i;
    int shmid;
    pid_t cpid = 0;
    int shm_size = sizeof_shm_stack(STACK_SIZE);
    
    printf("shm_size=%d\n", shm_size);
    /* We do not use malloc() to create shared memory, use shmget() */
    shmid = shmget(IPC_PRIVATE, shm_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);    
    if (shmid == -1 ) {
        perror("shmget");
        abort();
    }
    cpid = fork();
    if ( cpid > 0 ) {           /* parent proc pops */
        struct int_stack *pstack;    
        pstack = shmat(shmid, NULL, 0);
        printf("parent: pstack=%p\n", pstack);
        waitpid(cpid, NULL, 0);
        pop3(pstack);
        shmdt(pstack);
        /* We do not use free() to release the shared memory, use shmctl() */
        shmctl(shmid, IPC_RMID, NULL);
    } else if ( cpid == 0 ) {   /* child proc pushes */
        struct int_stack *pstack;    
        pstack = shmat(shmid, NULL, 0);
        printf("child: pstack = %p\n", pstack);
        init_shm_stack(pstack, STACK_SIZE);
        push3(pstack, 0xABCD);
        shmdt(pstack);
    } else {
        perror("fork");
        abort();
    }
    
}

int main()
{
    test_local();
    test_shm();
    return 0;

}
