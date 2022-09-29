#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void safeFree(void **pp)
{
    if (pp != NULL && *pp != NULL) {
        free(*pp);
        *pp = NULL;
    }
    return;
}

void SafeFree(void *p)
{
    safeFree((void **)&p);
}

void zhexdump(void const * data, unsigned int len)
{
    unsigned int i;
    unsigned int r,c;
    char *dmp = NULL, *tmp = NULL;
    unsigned char ch;
    if (!data)
        return;
    if (len == 0)
        return;
    // debug_debug("len=%d", len);
    asprintf(&dmp, "%s", "+------+-------------------------------------------------------------------------+\n");
    tmp = dmp;
    for (r = 0, i = 0; r < ((int)floor(len / 16) + (len % 16) != 0); r++, i += 16) {
        asprintf(&dmp, "%s| %04X |   ", dmp, i);
        if (tmp != dmp) SafeFree(tmp);
        tmp = dmp;
        for (c = i; c < i + 8; c++) {
            if (c < len) {
                asprintf(&dmp,"%s%02X ", dmp, ((unsigned char const *)data)[c]);
                if (tmp != dmp)
                    SafeFree(tmp);
                tmp = dmp;
            } else {
                asprintf(&dmp,"%s   ", dmp);
                if (tmp != dmp)
                    SafeFree(tmp);
                tmp = dmp;
            }
        }
        asprintf(&dmp,"%s  ", dmp);
        if (tmp != dmp)
            SafeFree(tmp);
        tmp = dmp;
        for (c = i + 8; c < i + 16; c++) {
            if (c < len) {
                asprintf(&dmp,"%s%02X ", dmp, ((unsigned char const *)data)[c]);
                if (tmp != dmp)
                    SafeFree(tmp);
                tmp = dmp;
            } else {
                asprintf(&dmp,"%s   ", dmp);
                if (tmp != dmp)
                    SafeFree(tmp);
                tmp = dmp;
            }
        }
        asprintf(&dmp,"%s   ", dmp);
        if (tmp != dmp)
            SafeFree(tmp);
        tmp = dmp;
        for (c = i; c < i + 16; c++) {
            ch = *(unsigned char *)(data + c);
            if (c < len) {
                if ((ch >= 32) && (ch < 127)) {
                    asprintf(&dmp, "%s%c", dmp, ch);
                    if (tmp != dmp)
                        SafeFree(tmp);
                    tmp = dmp;
                } else {
                    asprintf(&dmp, "%s%c", dmp, '.');
                    if (tmp != dmp)
                        SafeFree(tmp);
                    tmp = dmp;
                }
            } else {
                asprintf(&dmp,"%s ", dmp);
                if (tmp != dmp)
                    SafeFree(tmp);
                tmp = dmp;
            }
        }
        asprintf(&dmp,"%s |\n", dmp);
        if (tmp != dmp)
            SafeFree(tmp);
        tmp = dmp;
    }
    asprintf(&dmp, "%s%s", dmp, "+------+-------------------------------------------------------------------------+\n");
    if (tmp != dmp)
        SafeFree(tmp);
    tmp = dmp;
    // debug_debug("HEXDUMP\n%s", dmp);
    fprintf(stdout, "%s", dmp);
    SafeFree(dmp);
}

void DumpHex(const void* data, size_t size) {
	char ascii[17];
	size_t i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}