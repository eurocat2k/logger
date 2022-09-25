#ifndef EAFCEC1E_78CA_4D81_A713_C5733A4FACA7
#define EAFCEC1E_78CA_4D81_A713_C5733A4FACA7

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>

typedef enum { INFO, DEBUG, WARNING, ERROR } loglevel_t;

static const char *loglevelTXT[] = {
    "INFO", 
    "DEBUG", 
    "WARNING", 
    "ERROR"
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
 * @name   mylog_printf
 * @note   sends output pool contents to the output stream
 * @param  FILE* dst: the output stream - stdout, stderr or any FILE* pointer
 * @param  char* outstr: the output pool with collected chunks of strings
 * @retval None
 */
void mylog_printf(FILE *dst, char *outstr);
size_t append_log(loglevel_t loglevel, char **dst, const char *format, va_list args);
static char *gettimestamp();

void saferFree(void **pp);
void SaferFree(void *p);
void DumpHex(const void* data, size_t size);

#endif /* EAFCEC1E_78CA_4D81_A713_C5733A4FACA7 */
