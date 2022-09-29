#include "mylogger.h"
#include "misc.h"
#include "/usr/local/include/zlog.h"

#define BUFSIZE         (64)
#define LOG_STRFTIME    ("%F %T") // YYYY-MM-DD HH:MM:SS
#define MAX_BUFSIZ      (8192)

size_t append_log(loglevel_t loglevel, char **dst, const char *format, va_list args);
size_t append_zlog(char **dst, const char *format, va_list ap);
static char *gettimestamp();
void mylog_zlog_printf(void *c, loglevel_t loglevel, char *outstr);

size_t append_log(loglevel_t loglevel, char **dst, const char *format, va_list ap) {
    size_t ret = -1, len, tlen;
    char *p = NULL, *tail, *ref, *tstamp;
    va_list aplocal;
    va_copy(aplocal, ap);   // create a copy of the va_list
    ref = *dst;
    if (ref == NULL) {
        // add leader - loglevel description and timestamp if axists - to the output first
        tstamp = gettimestamp();
        size_t llen = snprintf(NULL, 0, "%s: %s - ", tstamp, loglevelTXT[loglevel]);
        llen += 1;
        if ((ref = calloc(llen + 1, sizeof(uint8_t))) == NULL) {
            perror("calloc: adding lead");
            goto err;
        }
        snprintf(ref, llen, "%s: %s - ", tstamp, loglevelTXT[loglevel]);
        SafeFree(tstamp);
        // append with first formatted string if any
        len = vsnprintf(NULL, 0, format, ap);
        len += 1;
        tlen = llen + len;
        if ((p = calloc(tlen, sizeof(char))) == NULL) {
            SafeFree(ref);
            perror("calloc failed at first append");
            goto err;
        }
        memmove(p, ref, llen);
        vsnprintf((p + llen - 1), len, format, aplocal);
        *dst = p;
    } else {
        // append output with formatted string if any
        len = vsnprintf(NULL, 0, format, ap);
        len += 1;
        size_t llen = strlen(ref) + 1;
        tlen = llen + len + LEAD_SPACES;  // add LEAD_SPACES (4) spaces to the beginning of the formatted string by default
        if (tlen <= MAX_BUFSIZ - 1) {
            p = calloc(tlen, sizeof(char));
            memmove(p, ref, llen);
            SafeFree(ref);
        } else {
            p = calloc(MAX_BUFSIZ + 1, sizeof(char));
            memmove(p, ref, MAX_BUFSIZ);
            SafeFree(ref);
            len -= tlen - MAX_BUFSIZ;   // truncate formatted string length not to excced MAX_BUFSIZ limit
        }
        for (char i = 0; i < LEAD_SPACES; i += 1) {
            *(p + i + llen - 1) = 0x20; // add SPACE character at the end of lead
        }
        vsnprintf((p + llen + LEAD_SPACES -1), len, format, aplocal);    // append existing text after TAB with new formatted string
        *dst = p;
    }
err:
    return ret;
}

size_t append_zlog(char **dst, const char *format, va_list ap) {
    size_t ret = -1, len, tlen;
    char *p = NULL, *tail, *ref, *tstamp;
    va_list aplocal;
    va_copy(aplocal, ap);   // create a copy of the va_list
    ref = *dst;
    if (ref == NULL) {
        // append with first formatted string if any
        len = vsnprintf(NULL, 0, format, ap);
        len += 1;
        tlen = len;
        if ((p = calloc(tlen, sizeof(char))) == NULL) {
            SafeFree(ref);
            perror("calloc failed at first append");
            goto err;
        }
        ret = vsnprintf(p, len, format, aplocal);
        *dst = p;
    } else {
        // append output with formatted string if any
        len = vsnprintf(NULL, 0, format, ap);
        len += 1;
        size_t llen = strlen(ref) + 1;
        tlen = llen + len + LEAD_SPACES;  // add LEAD_SPACES (4) spaces to the beginning of the formatted string by default
        if (tlen <= MAX_BUFSIZ - 1) {
            p = calloc(tlen, sizeof(char));
            memmove(p, ref, llen);
            SafeFree(ref);
        } else {
            p = calloc(MAX_BUFSIZ + 1, sizeof(char));
            memmove(p, ref, MAX_BUFSIZ);
            SafeFree(ref);
            len -= tlen - MAX_BUFSIZ;   // truncate formatted string length not to excced MAX_BUFSIZ limit
        }
        for (char i = 0; i < LEAD_SPACES; i += 1) {
            *(p + i + llen - 1) = 0x20; // add SPACE character at the end of lead
        }
        vsnprintf((p + llen + LEAD_SPACES -1), len, format, aplocal);    // append existing text after TAB with new formatted string
        *dst = p;
    }
err:
    return ret;
}

void mylog(loglevel_t loglevel, char **dst, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    append_log(loglevel, dst, fmt, ap);
    va_end(ap);
}

void zlog_mylog(loglevel_t loglevel, char **dst, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    append_zlog(dst, fmt, ap);
    va_end(ap);
}

void mylog_fprintf(FILE *dst, char *outstr) {
    if (outstr) {
        fprintf(dst, "%.*s", (int)strlen(outstr), outstr);
        SafeFree(outstr);
    }
}

void mylog_zlog_printf(void *c, loglevel_t loglevel, char *outstr) {
    zlog_category_t *zc = (zlog_category_t*)c;
    if (zc == NULL) {
        printf("STDOUT\n");
        // dump STDOUT
        if (NULL != outstr) {
            fprintf(stdout, "%.*s", (int)strlen(outstr), outstr);
            SafeFree(outstr);
        }
    } else {
        // zc is defined, and possible zlog_category_t pointer
        printf("ZLOG\n");
        if (NULL != outstr) {
            switch (loglevel) {
                case INFO:
                    zlog_info(zc, "%.*s", (uint16_t)strlen(outstr), outstr);
                    break;
                case DEBUG:
                    zlog_debug(zc, "%.*s", (uint16_t)strlen(outstr), outstr);
                    break;
                case WARNING:
                    zlog_warn(zc, "%.*s", (uint16_t)strlen(outstr), outstr);
                    break;
                case ERROR:
                    zlog_error(zc, "%.*s", (uint16_t)strlen(outstr), outstr);
                    break;
                case FATAL:
                    zlog_fatal(zc, "%.*s", (uint16_t)strlen(outstr), outstr);
                default:
                    break;
            }
            SafeFree(outstr);
        }
    }
}

static char *gettimestamp() {
    int r;
    time_t t;
    char *res, *p;
    struct tm *tmp;
    size_t tslen = 0;

    // In order to not waste space, the string is reallocated
    // later on. strftime(3) returns how many bytes have been put
    // into the buffer. If it does not fit into the buffer, it
    // errors out.
    if ((res = calloc(BUFSIZE, sizeof(char))) == NULL) {
        perror("calloc failed at timstamp initial allocation");
        goto err;
    }
    t = time(NULL);
    tmp = localtime(&t);
    if (tmp == NULL) {
	perror("localtime(3)");
        SafeFree(res);
	goto err;
    }
    r = strftime(res, BUFSIZE, LOG_STRFTIME, tmp);
    if (r == 0) {
	perror("strftime(3) failed");
	SafeFree(res);
	goto err;
    }
    tslen = strlen(res) + 1;
    if ((p = calloc(tslen, sizeof(char))) == NULL) {
        SafeFree(res);
        goto err;
    }
    memmove(p, res, tslen);
    SafeFree(res);
    res = p;
err:
    return res;
}
