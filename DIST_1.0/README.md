
# mylog interface

<h3>void mylog(loglevel_t level, char** output, const char* fmt, ...);</h3>

Variadic function.

```c
    /**
     * @name   mylog
     * @note   collects log entries into the output buffer with timestamp and loglevel info
     * @param  loglevel_t level: loglevel - enum type: 0 - INFO, 1 - DEBUG
     *         2 - WARNING, 3 - ERROR
     * @param  char** output: the address of the message pool where
     *         chunks are collected before send to output    
     * @param  const char* fm: format - printf like format string
     * @retval None
     */
    void mylog(loglevel_t loglevel, char **dst, const char *format, ...);
```

**loglevel_t** loglevel - INFO, DEBUG, WARNING, ERROR

```c
    typedef enum { INFO, DEBUG, WARNING, ERROR } loglevel_t;
```

**char**** output - pointer to the address of ouput pool

**char*** fmt - printf like format string

**...** argument list reference

<h2>Description</h2>

The **mylog** allocates and reallocates output buffer - *referenced by char*** *output* - as new formatted strings added to the message pool.

<h3>void mylog_printf(FILE *stream, char *outstr);</h3>

```c
    /**
     * @name   mylog_printf
     * @note   sends output pool contents to the output stream
     * @param  FILE* stream: the output stream - stdout, stderr or any FILE* pointer
     * @param  char* outstr: the output pool with collected chunks of strings
     * @retval None
     */
    void mylog_printf(FILE *stream, char *outstr);
```

**FILE*** stream - output stream

**char*** outstr - the pool of accumulated output strings

<h2>Description</h2>

**mylog_printf** puts the accumulated output messages pool contents to the **FILE*** referenced output stream, then frees up the allocated memory of the output pool.

Every time when user calls at least once the **mylog** function, then the user **MUST** call the **mylog_printf** - or at least **free(outstr)** before leave the code block, otherwise memory exhaustion may occure!

Go [back](../README.md) to the main page.
