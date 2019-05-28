/**
 * @brief: How to pass command line input arguments to main program
 * To execute: <executable> [arg1] [arg2]...[argN] 
 * EXAMPLE: ./cmd_arg.out Hello ECE252 101 201 
 */

#include <stdio.h>	/* printf needs to include this header file */

/**
 *@brief: main function that lists all command line arguments
 *@param: int argc is the number of command line arguments. 
 *        The executable itself is the first argument.
 *@param: char *argv is an array to hold each command line argument as an element.
 *        argv[0] contains the string representation of executable's name
 *        argv[1] contains the string representation of the 1st input argument
 *        ...
 *        argv[n] contains the string representation of the n'th input argument
 */
int main(int argc, char *argv[]) 
{
    int i;

    printf("A complete list of command line arguments:\n");
    for (i = 0; i < argc; i++) {
        printf("argv[%d]=%s\n", i, argv[i]);
    }
    return 0;
}
