#include "mylogger.h"

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
        SaferFree(tstamp);
        // append with first formatted string if any
        len = vsnprintf(NULL, 0, format, ap);
        len += 1;
        tlen = llen + len;
        if ((p = calloc(tlen, sizeof(char))) == NULL) {
            SaferFree(ref);
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
        p = calloc(tlen, sizeof(char));
        memmove(p, ref, llen);
        SaferFree(ref);
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

void mylog_printf(FILE *dst, char *outstr) {
    if (outstr) {
        fprintf(dst, "%.*s", (int)strlen(outstr), outstr);
        SaferFree(outstr);
    }
}

static char *gettimestamp() {
	int r;
	time_t t;
	char *res, *p;
	struct tm *tmp;
    size_t tslen = 0;

#define BUFSIZE (64)
#define LOG_STRFTIME  ("%F %T")

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
        SaferFree(res);
		goto err;
	}
	r = strftime(res, BUFSIZE, LOG_STRFTIME, tmp);
	if (r == 0) {
		perror("strftime(3) failed");
		SaferFree(res);
		goto err;
	}
    tslen = strlen(res) + 1;
    if ((p = calloc(tslen, sizeof(char))) == NULL) {
        SaferFree(res);
        goto err;
    }
    memmove(p, res, tslen);
    SaferFree(res);
    res = p;
err:
    return res;
}
