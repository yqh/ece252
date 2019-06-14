/*
 * The code Copyright(c) 2018-2019 Yiqing Huang, <yqhuang@uwaterloo.ca>.
 * This software may be freely redistributed under the terms of the X11 License.
 */

/**
 * @brief To doemostrate a zombie process
 * @file  zombie.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define _XOPEN_SOURCE 500

int main ()
{
    pid_t child_pid;
    /* Create a child process. */
    child_pid = fork ();

    if ( child_pid > 0 ) {
        int pid=getpid();
        sleep(1);
        printf("Parent pid=%d.\n", pid);
        printf("Use command \"ps -eo ruser,pid,ppid,pgid,stat,cmd | grep %d| grep -v grep\" to see both processes.\n", pid);
        /* Parent process sleeps for 120 seconds. */
        sleep (120);
    } else if ( child_pid == 0 ) {
        /* The child process exits immediately after printf. 
           will be in zombie status before parent exits,
           since parent does not wait on child process.
         */

        printf("Child pid = %d.\n", getpid());
        exit (0);
    } else {
        perror("fork");
        abort();
    }
    return 0;
}
