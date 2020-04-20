/**
 * @brief: header file of in memory deflation and inflation using zlib. 
 * Based on the zlib example zpipe.c at https://www.zlib.net/zlib_how.html
 *
 * Modification is
 * Copyright 2018-2020 Yiqing Huang
 *
 * This software may be freely redistributed under the terms of MIT License
 *            https://www.zlib.net/zlib_how.html
 */

#pragma once

/* INCLUDES */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "zlib.h"

/* DEFINES */
#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384  /* =256*64 on the order of 128K or 256K should be used */

/* TYPEDEFS */
typedef unsigned char U8;
typedef unsigned long int U64;

/* FUNCTION PROTOTYPES */
int mem_def(U8 *dest, U64 *dest_len, U8 *source,  U64 source_len, int level);
int mem_inf(U8 *dest, U64 *dest_len, U8 *source,  U64 source_len);
void zerr(int ret);
