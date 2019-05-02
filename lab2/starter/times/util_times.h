/**
 * @file util_times.h
 * @brief utility function to obtain time resource usage.
 * @author yqhuang@uwaterloo.ca
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>             /* man sysconf(3)  */
#include <sys/times.h>          /* man times(2) */

#define BUF_SIZE_256 256
#define NUM_FUNS 3

typedef struct fn_info
{
    void *(*fnp)(void *args);    /* function pointer */
    const char name[64];         /* function name */
} *FN_INFO_P;

typedef struct fn_info_map
{
    unsigned int size;            /* size of the fn_info_strutp */
    FN_INFO_P fn_info_structp;    /* array of fn_info structures*/
} *FN_INFO_MAP_P;

const char *get_name_by_fnp (FN_INFO_P ptr, void *(*fnp)(void *args));
void *time_it(FN_INFO_P ptr, void *(*fnp)(void *args), void *args);
void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend);
