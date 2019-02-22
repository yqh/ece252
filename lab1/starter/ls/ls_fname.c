/**
 * @file: ls_fname.c
 * @brief: simple ls command to list file names of a directory 
  */

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>   /* for printf().  man 3 printf */
#include <stdlib.h>  /* for exit().    man 3 exit   */
#include <string.h>  /* for strcat().  man strcat   */

int main(int argc, char *argv[]) 
{
    DIR *p_dir;
    struct dirent *p_dirent;
    char str[64];

    if (argc == 1) {
        fprintf(stderr, "Usage: %s <directory name>\n", argv[0]);
        exit(1);
    }

    if ((p_dir = opendir(argv[1])) == NULL) {
        sprintf(str, "opendir(%s)", argv[1]);
        perror(str);
        exit(2);
    }

    while ((p_dirent = readdir(p_dir)) != NULL) {
        char *str_path = p_dirent->d_name;  /* relative path name! */

        if (str_path == NULL) {
            fprintf(stderr,"Null pointer found!"); 
            exit(3);
        } else {
            printf("%s\n", str_path);
        }
    }

    if ( closedir(p_dir) != 0 ) {
        perror("closedir");
        exit(3);
    }

    return 0;
}
