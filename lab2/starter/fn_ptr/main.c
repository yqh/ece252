/*
 * Copyright 2019 Yiqing Huang, <yqhuang@uwaterloo.ca>.
 *
 * This software may be freely redistributred under the terms of the X11 license.
 */

/**
 * @file  main.c 
 * @brief demonstrate C function pointer usage
 */

#include <stdio.h>
#include <stdlib.h>

int sum(int x, int y);

int wrapper_double(int x, unsigned int choice);
int double_0(int x);
int double_1(int x);

int sum(int x, int y)
{
    return (x+y);
}

/**
 * @brief a wrapper function.
 */
int wrapper_double(int x, unsigned int choice)
{
    int (*fnp_double[])(int) = {double_0, double_1};
    if (choice < 0 || choice > 1) {
        printf("Invalide choice: %d. Default to 0.\n", choice);
        choice = 0;
    }
    return (*fnp_double[choice])(x);
}


int double_0(int x) {
    printf("double_0 is called.\n");
    return (x*2);
}

int double_1(int x) {
    printf("doubl_1 is called.\n");
    return (x<<1);
}

int main(int argc, char **argv)
{
    int (*fnp_sum)(int, int) = sum;
    int ret;
    int x = 3;
    int y = 2;
    unsigned int choice = 0;
    
    ret = (*fnp_sum)(x, y);
    printf("sum(%d, %d)  = %d.\n", x, y, ret);

    printf("choose 0 for double_0() and 1 for double_1().\n");
    scanf("%d", &choice);
    printf("Your choice is %d.\n", choice);

    ret = wrapper_double(x, choice);
    printf("double of %d is %d.\n", x, ret);

    
    return 0;
}
