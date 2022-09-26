#include "libsrc/mylogger.h"
#include "/usr/local/include/zlog.h"

int main() {
    char *out = NULL;
    char *zout = NULL;
    int rc;
	zlog_category_t *zc;

	rc = zlog_init("zlog.conf");
	if (rc) {
		printf("init failed\n");
		return -1;
	}

	zc = zlog_get_category("my_cat");
	if (!zc) {
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

    //  output stream test
	// mylog(INFO, &out, "%s: %d - 0x%4.04x\n", "LOGGER", 4654, 32126);
    // mylog(INFO, &out, "second line: error code:%d - 0x%4.04x\n", 4654, 3);
    // mylog(INFO, &out, "third line: message: %s\n", "TEST");
    // mylog(INFO, &out, "fourth line: %f, message: %s %d\n", 1.2354, "TEST", 8);
    // mylog(INFO, &out, "fifth line: %.2f%%, message: %s AZ UJ MEZEBEN AMELYNEK A SZAMA: %d\n", 0.75654 * 100.0, "CSIGA GOLT VAGY PONTOT SZEREZ", 9);
    // mylog_fprintf(stdout, out);

    // ZLOG TEST
    // zlog_info(zc, "hello, zlog -- info");
	// zlog_error(zc, "hello, zlog -- error");
    zlog_mylog(DEBUG, &zout, "%s: %d - 0x%4.04x\n", "LOGGER", 4654, 32126);
    zlog_mylog(DEBUG, &zout, "second line: error code:%d - 0x%4.04x\n", 4654, 3);
    zlog_mylog(DEBUG, &zout, "third line: message: %s\n", "TEST");
    zlog_mylog(DEBUG, &zout, "fourth line: %f, message: %s %d\n", 1.2354, "TEST", 8);
    zlog_mylog(DEBUG, &zout, "fifth line: %.2f%%, message: %s AZ UJ MEZEBEN AMELYNEK A SZAMA: %d\n", 0.75654 * 100.0, "CSIGA GOLT VAGY PONTOT SZEREZ", 9);
    mylog_zlog_printf(zc, DEBUG, zout);
    zlog_fini();
    return 0;
}