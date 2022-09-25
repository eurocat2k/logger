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

const char *loglevelTXT[] = {
    "INFO", 
    "DEBUG", 
    "WARNING", 
    "ERROR"
};

#define LEAD_SPACES 21

void mylog(loglevel_t loglevel, char **dst, const char *format, ...);
void mylog_printf(FILE *dst, char *outstr);
size_t append_log(loglevel_t loglevel, char **dst, const char *format, va_list args);
static char *gettimestamp();

void saferFree(void **pp);
void SaferFree(void *p);
void DumpHex(const void* data, size_t size);

#endif /* EAFCEC1E_78CA_4D81_A713_C5733A4FACA7 */
