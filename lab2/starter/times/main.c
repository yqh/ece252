#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>             /* man sysconf(3)  */
#include <sys/times.h>          /* man times(2) */

#define _GNU_SOURCE             /* man secure_getenv, see Feature Test Macro */
#define BUF_SIZE 256
#define CMD_LEN  256
#define NUM_FUNS 2

struct fn_info
{
    void *(*fnp)(void *args);    /* function pointer */
    const char name[32];         /* function name */
};

void *f1(void *args);
void *f2(void *args);
int sprintf_time(void *buf, time_t t);
const char *get_name_by_fnp (void *(*fnp)(void *args));
void *time_it(void *(*fnp)(void *args), void *args);
void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend);

struct fn_info g_fn_map[NUM_FUNS] = \
{
    {f1, "f1()"}, \
    {f2, "f2()"}
};

void *f1(void *args)
{
    int x = 0;
    sleep(2);
    /*
    for (int i=0; i<100000000; i++) {
        x = i;
    }
    */
    printf("x=%d.\n", x);
    return NULL;
}

void *f2(void *args)
{
    int status = 0;
    char cmd[CMD_LEN];
    char *dir = getenv("HOME");
    if (dir == NULL) {
        return NULL;
    }
    printf("dir = %s \n", dir);
    sprintf(cmd, "du -ks %s/*", dir);
    status = system(cmd);
    printf("status = %d.\n", status);
    return NULL;
};

int sprintf_time(void *buf, time_t t)
{
    struct tm *tm_ptr;
    int ret = 0;

    if (buf == NULL) {
        fprintf(stderr, "cannot access memory of destination buffer.\n");
        return -1;
    }

    tm_ptr = localtime(&t);
    ret = strftime(buf, BUF_SIZE, "time and date: %r, %a %b %d, %Y", tm_ptr);
    if (ret == 0) {
        perror("strftime");
        return -errno;
    }

    return ret;
}

const char *get_name_by_fnp (void *(*fnp)(void *args)) {
    int index = -1;
    
    for (int i = 0; i < NUM_FUNS; i++) {
        if (g_fn_map[i].fnp == fnp) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        return g_fn_map[index].name; 
    }

    return NULL;
}

void *time_it(void *(*fnp)(void *args), void *args)
{
    struct tms tms_start;
    struct tms tms_end;
    clock_t start;
    clock_t end;

    printf("function: %s\n", get_name_by_fnp(fnp));
    if ((start = times(&tms_start)) == -1) { /* starting time */
        perror("start times");
    }

    (*fnp)(NULL);                           /* execute the function */

    if ((end = times(&tms_end)) == -1) {    /* ending time */
        perror("end times");
    }

    pr_times(end-start, &tms_start, &tms_end);
    
    return NULL;
}

void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    //static long clktck = 0;
    long clktck = 0;

    if (clktck == 0) { /* fetch clock ticks per second first time */
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0) {
            perror("sysconf");
        }
    }
    printf(" real: %7.2f\n", real / (double) clktck);
    printf(" user: %7.2f\n",
           (tmsend->tms_utime - tmsstart->tms_utime) / (double) clktck);
    printf(" sys: %7.2f\n",
           (tmsend->tms_stime - tmsstart->tms_stime) / (double) clktck);
    printf(" child user: %7.2f\n",
           (tmsend->tms_cutime - tmsstart->tms_cutime) / (double) clktck);
    printf(" child sys: %7.2f\n",
           (tmsend->tms_cstime - tmsstart->tms_cstime) / (double) clktck);

}


int main(int argc, char **argv)
{
    struct timespec tsp;
    struct timeval  tv;
    time_t          t;
    int ret;
    char *buf = NULL;
    char clocks[] = {CLOCK_REALTIME, CLOCK_MONOTONIC,
                     CLOCK_PROCESS_CPUTIME_ID, CLOCK_THREAD_CPUTIME_ID};

    buf = malloc(BUF_SIZE);
    if (buf == NULL) {
        perror("malloc");
        return errno;
    }
    /* Time resolution in seconds */
    time(&t);
    sprintf_time(buf, t);
    printf("%s.\n", buf);

    /* Time resolution in microseconds */
    ret = gettimeofday(&tv, NULL);
    printf("tv.sec = %ld, tv.tv_usec = %ld.\n", tv.tv_sec, tv.tv_usec);

    /* Time resolution in nanoseconds */
    for (int i=0; i<4; i++) {
        ret = clock_getres(clocks[i], &tsp);
        ret = clock_gettime(clocks[i], &tsp);

        printf("clock[%d]: tsp.tv_sec = %ld, tsp.tv_nsec = %ld.\n",
               i, tsp.tv_sec, tsp.tv_nsec); 
    }

    /* get _SC_CLK_TCK, num of clock ticks per second from sysconf */
    int long ticks = 0;
    ticks = sysconf(_SC_CLK_TCK);
    printf("_SC_CLK_TCK = %ld.\n", ticks);

    time_it(f1, NULL);
    time_it(f2, NULL);
    
    return 0;
}
