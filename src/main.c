#include "libsrc/mylogger.h"
int main() {
    char *out = NULL;
    mylog(INFO, &out, "%s: %d - 0x%4.04x\n", "LOGGER", 4654, 32126);
    mylog(INFO, &out, "second line: error code:%d - 0x%4.04x\n", 4654, 3);
    mylog(INFO, &out, "third line: message: %s\n", "TEST");
    mylog(INFO, &out, "fourth line: %f, message: %s %d\n", 1.2354, "TEST", 8);
    mylog(INFO, &out, "fifth line: %.2f%%, message: %s AZ UJ MEZEBEN AMELYNEK A SZAMA: %d\n", 0.75654 * 100.0, "CSIGA GOLT VAGY PONTOT SZEREZ", 9);
    mylog_printf(stdout, out);
    return 0;
}