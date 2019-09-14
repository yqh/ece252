#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv){
    char str[8];
    char PNG[8] = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};
 
   // printf("%s",argv[1]);
    FILE *fp = fopen(argv[1],"rb");
    if(fp){
        fread(str, 8, 1, fp);
        // for(int i = 0; i < 8; ++i){
        //     printf("%x\n",str[i]);
        //     printf("%x\n",PNG[i]);
        // }
        printf("%d", strcmp (str, PNG));
    }
    fclose(fp);

}