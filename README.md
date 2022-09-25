# Accumulated output for logger - like zlog - output

I'm active user of [zlog](https://github.com/HardySimpson/zlog), which tool helped me in number of projects. It has an option to collect chunks of strings before put them all at once to the log output though, but I wanted to create my buffering stuff as I do prefer to use.

<h2>Install</h2>

Before you would like to play with the code, you need to install ***autotools*** utilities from your native port source - if its not already installed on your machine.
Then you simply call ***./rebuild.sh*** small script, which will create **Makefile**s for building the library and test code of the program.

```bash
    % ./rebuild.sh
```

then

```bash
    % make install clean
```

The final code will be placed in the ***DIST_1.0*** subdirectory.

<h2>Usage</h2>

It is quite simple - see *[interface](src/README.md) docs* - as it collects chunks each time when the user calls the logger's main entry function - ***mylog***.
```c
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
```

Every call the ***mylog*** appends the ***dst*** referenced pool with the formatted input string.
At frist time it requires a reference as a **NULL** initialized pointer. See exmple below (*Example_1*):
```c
    char *logout = NULL;    // NULL initialized output before start to collect 
                            // the chunks
    ...
    int line_no = 1;
    mylog(DEBUG, &logout, "%d. line: %s", line_no, "TEST");    // calling 
                            // first time the output 
                            // buffer will look like this:
                            // 2022-09-25 16:43:22: DEBUG - 1. line: TEST
    ...
    line_no += 1;
    unsigned short error_code = 12342;
    double pi = 3.141592654;
    mylog(DEBUG, &logout, 
        "%d. line: hexcode = 0x%02x float: %f", 
        line_no, 
        error_code, 
        pi);    // after second call the buffer will look like this:
                // 2022-09-25 16:43:22: 1. line_no: DEBUG - TEST
                //                      2. line: hexcode = 0x3036 float: 3.141592654
``` 
**Example_1: collects chunks into output pool**

Finally when user wants to put out the contents of the pool to the output stream, calls the ***mylog_printf*** function with the address of the output pool (Example_2):
```c
    /**
     * @name   mylog_printf
     * @note   sends output pool contents to the output stream
     * @param  FILE* dst: the output stream - stdout, stderr or any FILE* pointer
     * @param  char* outstr: the output pool with collected chunks of strings
     * @retval None
     */
    void mylog_printf(FILE *dst, char *outstr);
```
Here is the final act, put the contents of the output pool to the output stream (*Example_2*), and frees - initializes *NULL* - the memory allocated for the pool for further usage in the code block:
```c
    ...
    mylog_printf(stdout, logout);   // will produce the following output in STDOUT
    // 2022-09-25 16:43:22: 1. line_no: DEBUG - TEST
    //                      2. line: hexcode = 0x3036 float: 3.141592654
```
**Example_2: prints out the content of the output pool, and frees the output pool**
