
/**
 * @brief An example of POSIX unamed semaphore shared between processes 
 * @author yqhuang@uwaterloo.ca
 */

//#define _XOPEN_SOURCE 500
//#define _POSIX_C_SOURCE 200808L

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#define SHM_SIZE 1024 
#define SEM_PROC 1
#define NUM_SEMS 2


int main( int argc, char** argv ) {
    pid_t cpid = 0;
    sem_t *sems;
    void *buf;

    /* allocate two shared memory regions */
    int shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    int shmid_sems = shmget(IPC_PRIVATE, sizeof(sem_t) * NUM_SEMS, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    if (shmid == -1 || shmid_sems == -1) {
        perror("shmget");
        abort();
    }

    /* attach to shared memory regions */
    buf = shmat(shmid, NULL, 0);
    sems = shmat(shmid_sems, NULL, 0);
    if ( buf == (void *) -1 || sems == (void *) -1 ) {
        perror("shmat");
        abort();
    }

    /* initialize shared memory varaibles */
    memset(buf, 0, SHM_SIZE);
    if ( sem_init(&sems[0], SEM_PROC, 1) != 0 ) {
        perror("sem_init(sem[0])");
        abort();
    }
    if ( sem_init(&sems[1], SEM_PROC, 0) != 0 ) {
        perror("sem_init(sem[1])");
        abort();
    }

    cpid = fork(); 
    if ( cpid > 0 ) { /* Parent */

        printf("Parent is blocked, waiting for a message from the child.\n");
        if ( sem_wait(&sems[1]) != 0 ) {
            perror("sem_wait on sems[1]");
            abort();
        }

        printf("Parent received a message from the child:  %s.\n", (char*) buf);

        if ( sem_post(&sems[0]) != 0 ) {
            perror("sem_post on sems[0]");
            abort();
        }

        if ( shmdt(buf) != 0 ) {
            perror("shmdt");
            abort();
        }
        if ( shmctl(shmid, IPC_RMID, NULL) == -1 ) {
            perror("shmctl");
            abort();
        }

        if ( shmdt(sems) != 0 ) {
            perror("shmdt");
            abort();
        }

        waitpid(cpid, NULL, 0);

        if ( shmctl(shmid_sems, IPC_RMID, NULL) == -1 ) {
            perror("shmctl");
            abort();
        }

        if (sem_destroy(&sems[0]) || sem_destroy(&sems[1])) {
            perror("sem_destroy");
            abort();
        }

    } else if ( cpid == 0 ) { /* Child */
        printf("Child is sleeping before sending a message to the parent.\n");
        usleep(rand()%50000);
        if ( sem_wait(&sems[0]) != 0 ) {
            perror("sem_wait on sem[0]");
            abort();
        }
        sprintf(buf, "I am the child (pid=%d)", getpid());
        if ( sem_post(&sems[1]) != 0 ) {
            perror("sem_post on sem[1]");
            abort();
        }
        if ( shmdt(buf) != 0 ) {
            perror("shmdt");
            abort();
        }

        if ( shmdt(sems) != 0 ) {
            perror("shmdt");
            abort();
        }
    } else {
        perror("fork");
        abort();
    }
    return 0;
}
