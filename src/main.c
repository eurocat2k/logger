#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef enum { INFO, DEBUG, WARNING, ERROR } loglevel_t;

const char *loglevelTXT[] = {
    "INFO", 
    "DEBUG", 
    "WARNING", 
    "ERROR"
};

void mylog(loglevel_t loglevel, char **dst, const char *format, ...);
size_t append_log(loglevel_t loglevel, char **dst, const char *format, va_list args);

int main() {
    char *out = NULL;
    // printf("%s", "Hello world!\n");
    mylog(INFO, &out, "%s: %d - 0x%4.04x\n", "LOGGER", 4654, 32126);
    mylog(INFO, &out, "second line': error code:%d - 0x%4.04x\n", 4654, 3);
    mylog(INFO, &out, "third line': message: %s\n", "TEST");
    mylog(INFO, &out, "fourth line': %f, message: %s %d\n", 1.2354, "TEST", 8);
    mylog(INFO, &out, "fifth line': %.2f%%, message: %s AZ UJ MEZEBEN AMELYNEK A SZAMA: %d\n", 0.75654 * 100.0, "CSIGA GOLT VAGY PONTOT SZEREZ", 9);
    printf("%s", out);
    free(out);
    // printf("%s\n", loglevelTXT[INFO]);
    return 0;
}

size_t append_log(loglevel_t loglevel, char **dst, const char *format, va_list ap) {
    char *ref = *dst, *p = NULL, *tail;
    char *header = NULL;
    size_t len = 0, nlen = 0, hlen = 0;
    // printf("%s [%d] - ", loglevelTXT[loglevel], loglevel);
    // return 0;
    if (*dst == NULL) {
        // add timestamp and loglevel information
        hlen = snprintf(NULL, 0, "%s - ", loglevelTXT[loglevel]);
        hlen += 1;
        header = calloc(hlen, sizeof(unsigned char));
        if (header == NULL) {
            perror("calloc: header");
            return -1;
        }
        snprintf(header, hlen, "%s - ", loglevelTXT[loglevel]);
        nlen = vsnprintf(NULL, 0, format, ap);
        nlen += 1;
        p = realloc(header, hlen + nlen);
        if (NULL == p) {
            perror("realloc failed: header");
            free(header);
            return -1;
        }
        if (p != header) {
          free(header);
          header = p;
        }
        tail = p + hlen - 1;
        vsnprintf(tail, nlen, format, ap);
        *dst = p;
    } else {
      // append the existing log with new entries...
      len = strlen(ref);
      nlen = vsnprintf(NULL, 0, format, ap);
      nlen += 1; // add extra byte for terminator 0
      p = realloc(ref, len + nlen);
      if (p != ref) {
        free(ref);
        ref = p;
      }
      tail = (ref + len);
      memset(tail, 0, nlen);
      vsnprintf(tail, nlen, format, ap);
      // vprintf(format, ap);
    }
}

void mylog(loglevel_t loglevel, char **dst, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    // printf("loglevel: %d %s\n", loglevel, loglevelTXT[loglevel]);
    append_log(loglevel, dst, fmt, ap);
    va_end(ap);
}
