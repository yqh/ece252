/**
 * @biref To demonstrate how to use zutil.c and crc.c functions
 *
 * Copyright 2018-2020 Yiqing Huang
 *
 * This software may be freely redistributed under the terms of MIT License
 */

#include <stdio.h>    /* for printf(), perror()...   */
#include <stdlib.h>   /* for malloc()                */
#include <errno.h>    /* for errno                   */
#include "crc.h"      /* for crc()                   */
#include "zutil.h"    /* for mem_def() and mem_inf() */
#include "lab_png.h"  /* simple PNG data structures  */

/******************************************************************************
 * DEFINED MACROS 
 *****************************************************************************/
#define BUF_LEN  (256*16)
#define BUF_LEN2 (256*32)

/******************************************************************************
 * GLOBALS 
 *****************************************************************************/
U8 gp_buf_def[BUF_LEN2]; /* output buffer for mem_def() */
U8 gp_buf_inf[BUF_LEN2]; /* output buffer for mem_inf() */

/******************************************************************************
 * FUNCTION PROTOTYPES 
 *****************************************************************************/

void init_data(U8 *buf, int len);

/******************************************************************************
 * FUNCTIONS 
 *****************************************************************************/

/**
 * @brief initialize memory with 256 chars 0 - 255 cyclically 
 */
void init_data(U8 *buf, int len)
{
    int i;
    for ( i = 0; i < len; i++) {
        buf[i] = i%256;
    }
}

int main (int argc, char **argv)
{
    U8 *p_buffer = NULL;  /* a buffer that contains some data to play with */
    U32 crc_val = 0;      /* CRC value                                     */
    int ret = 0;          /* return value for various routines             */
    U64 len_def = 0;      /* compressed data length                        */
    U64 len_inf = 0;      /* uncompressed data length                      */
    
    /* Step 1: Initialize some data in a buffer */
    /* Step 1.1: Allocate a dynamic buffer */
    p_buffer = malloc(BUF_LEN);
    if (p_buffer == NULL) {
        perror("malloc");
	return errno;
    }

    /* Step 1.2: Fill the buffer with some data */
    init_data(p_buffer, BUF_LEN);

    /* Step 2: Demo how to use zlib utility */
    ret = mem_def(gp_buf_def, &len_def, p_buffer, BUF_LEN, Z_DEFAULT_COMPRESSION);
    if (ret == 0) { /* success */
        printf("original len = %d, len_def = %lu\n", BUF_LEN, len_def);
    } else { /* failure */
        fprintf(stderr,"mem_def failed. ret = %d.\n", ret);
        return ret;
    }
    
    ret = mem_inf(gp_buf_inf, &len_inf, gp_buf_def, len_def);
    if (ret == 0) { /* success */
        printf("original len = %d, len_def = %lu, len_inf = %lu\n", \
               BUF_LEN, len_def, len_inf);
    } else { /* failure */
        fprintf(stderr,"mem_def failed. ret = %d.\n", ret);
    }

    /* Step 3: Demo how to use the crc utility */
    crc_val = crc(gp_buf_def, len_def); // down cast the return val to U32
    printf("crc_val = %u\n", crc_val);
    
    /* Clean up */
    free(p_buffer); /* free dynamically allocated memory */

    return 0;
}
