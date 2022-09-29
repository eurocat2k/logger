#ifndef EAFCEC1E_78CA_4D81_A713_C5733A4FACA7
#define EAFCEC1E_78CA_4D81_A713_C5733A4FACA7

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>
#include "/usr/local/include/zlog.h"

typedef enum { INFO, DEBUG, WARNING, ERROR, FATAL } loglevel_t;

static const char *loglevelTXT[] = {
    "INFO", 
    "DEBUG", 
    "WARNING", 
    "ERROR",
    "FATAL"
};

#define LEAD_SPACES 21
/**
 * @name   mylog
 * @note   collects log entries into the output buffer with timestamp and loglevel info
 * @param  loglevel_t loglevel: loglevel - enum type: 0 - INFO, 1 - DEBUG
 *         2 - WARNING, 3 - ERROR
 * @param  char** dst: dst - the address of the message pool where
 *         chunks are collected before send to output    
 * @param  const char* format: format - printf like format string
 * @retval None
 */
void mylog(loglevel_t loglevel, char **dst, const char *format, ...);
/**
 * @name   zlog_mylog
 * @note   ollects log entries into the output buffer with timestamp and loglevel info
 * @param  loglevel_t loglevel: deermine zlog output loglevel
 * @param  char** dst: output buffer
 * @param  char* fmt: printf like format string
 * @retval None
 */
void zlog_mylog(loglevel_t loglevel, char **dst, const char *fmt, ...);
/**
 * @name   mylog_printf
 * @note   sends output pool contents to the output stream
 * @param  FILE* dst: the output stream - stdout, stderr or any FILE* pointer
 * @param  char* outstr: the output pool with collected chunks of strings
 * @retval None
 */
void mylog_fprintf(FILE *dst, char *outstr);
/**
 * @name   mylog_zlog_printf
 * @note   dumps output string to zlog interface - or if it's not defined, then put STDOUT by default
 * @param  zlog_category_t *zc: zlog interface handler
 * @param  loglevel_t loglevel: loglevel loglevel - enum type: 0 - INFO, 1 - DEBUG, 2 - WARNING, 3 - ERROR
 * @param  char* outstr: output buffer
 * @retval None
 */
void mylog_zlog_printf(void *c, loglevel_t loglevel, char *outstr);
/**
 * @name   SaferFree
 * @note   frees HEAP allocated memory
 * @param  void* p: pointer to the allocated memory block
 * @retval None
 */
void SafeFree(void *p);
/**
 * @name   DumpHex
 * @note   hexdump data with length
 * @param  const void* data: buffer to be hexdumped
 * @param  size_t size: the length of the buffer
 * @retval None
 */
void DumpHex(const void* data, size_t size);

#endif /* EAFCEC1E_78CA_4D81_A713_C5733A4FACA7 */
