/*
 * The code is derived from paster.c
 * Copyright (C) 2013-2019, Patrick Lam, <p23lam@uwaterloo.ca>.
 *
 * Modifications to the code are
 * Copyright 2019, Yiqing Huang, <yqhuang@uwaterloo.ca>
 * 
 * This software may be freely redistributed under the terms
 * of the X11 license. 
 */


/**
 * @file main_getopt.c
 * @brief using getopt to parse command-line options 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief: a command that takes -t and -n options
 * -t <number of threads>, default value 1 (i.e. single threaded)
 * -n <image number>, default value 1 (valid values: 1, 2, and 3)
 *    There are three images in total on the server side.
 * SYNOPSIS
 *        <command> [-t <number of threads>] [-n <image number>]
 */

int main(int argc, char **argv)
{
    int c;
    int t = 1;
    int n = 1;
    char *str = "option requires an argument";
    
    while ((c = getopt (argc, argv, "t:n:")) != -1) {
        switch (c) {
        case 't':
	    t = strtoul(optarg, NULL, 10);
	    printf("option -t specifies a value of %d.\n", t);
	    if (t <= 0) {
                fprintf(stderr, "%s: %s > 0 -- 't'\n", argv[0], str);
                return -1;
            }
            break;
        case 'n':
            n = strtoul(optarg, NULL, 10);
	    printf("option -n specifies a value of %d.\n", n);
            if (n <= 0 || n > 3) {
                fprintf(stderr, "%s: %s 1, 2, or 3 -- 'n'\n", argv[0], str);
                return -1;
            }
            break;
        default:
            return -1;
        }
    }
}
