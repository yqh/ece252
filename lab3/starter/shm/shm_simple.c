
/**
 * @brief A simple shared memory, no structure involved. 
 * @author yqhuang@uwaterloo.ca
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define SHM_SIZE 256 

int g_val = 0;

int main( int argc, char** argv ) {
    pid_t cpid = 0;
    int shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    if ( shmid == -1 ){
        perror("shmget");
    }

    printf("Parent and child processes cannot use global variables to communicate!\n");
    printf("Because they do not share the same address space. Global variable only works within the same address space.\n");
    printf("Before fork: g_val=%d\n", g_val);
    cpid = fork(); 
    if ( cpid > 0 ) { /* Parent */
        void *buf = shmat(shmid, NULL, 0);

        if ( buf == (void *) -1 ) {
            perror("shmat");
            abort();
        }

        g_val = 100;
        printf("After fork: parent (pid=%d) sees g_val = %d\n", getpid(), g_val);
        waitpid(cpid, NULL, 0);
        printf("They can use shared memory to communicate.\n");
        printf("Parent received a message from a child:  %s.\n", (char*) buf);
        if ( shmdt(buf) != 0 ) {
            perror("shmdt");
            abort();
        }
        if ( shmctl(shmid, IPC_RMID, NULL) == -1 ) {
            perror("shmctl");
            abort();
        }
    } else if ( cpid == 0 ) { /* Child */
        void* buf = shmat( shmid, NULL, 0 );
        if ( buf == (void *) -1 ) {
            perror("shmat");
            abort();
        }

        printf("After fork: child (pid=%d) sees g_val = %d\n", getpid(), g_val);
        memset(buf, 0, SHM_SIZE);
        sprintf(buf, "I am the child (pid=%d)", getpid());
        if ( shmdt(buf) != 0 ) {
            perror("shmdt");
            abort();
        }
    } else {
        perror("fork");
        abort();
    }
    return 0;
}
