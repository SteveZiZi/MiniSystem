#include <ctype.h>
#include <stdarg.h>

#include "debug.h"

/* printk's without a loglevel use this.. */
#define DEFAULT_MESSAGE_LOGLEVEL 4  /* KERN_WARNING */

/* We show everything that is MORE important than this.. */
#define MINIMUM_CONSOLE_LOGLEVEL 1  /* Minimum loglevel we let people use */
#define DEFAULT_CONSOLE_LOGLEVEL 7  /* anything MORE serious than DM_DEBUG */

int console_printk[4] = {
    DEFAULT_CONSOLE_LOGLEVEL,   /* console_loglevel */
    DEFAULT_MESSAGE_LOGLEVEL,   /* default_message_loglevel */
    MINIMUM_CONSOLE_LOGLEVEL,   /* minimum_console_loglevel */
    DEFAULT_CONSOLE_LOGLEVEL,   /* default_console_loglevel */
};

size_t atobcd(const char *src, size_t alen, unsigned char * dest)
{
    ASSERT(src);
    ASSERT(dest);

    if (alen == 0)
    {
        alen = strlen(src);
        if (src[alen] == 0x0A && alen > 0)
            alen -= 1;
    }
    if (alen == 0)
        return 0;

    size_t bcdlen = 0, i;
    if (alen == 1)
    {
        if (src[0] - 0x41 < 0)
            dest[bcdlen++] = src[0] - 0x30;
        else
            dest[bcdlen++] = src[0] - 0x37;
        return bcdlen;
    }

    for (i = 0; i < alen; i += 2)
    {
        if (src[i] - 0x41 < 0)
        {                       /* high byte is a digit */
            if (src[i + 1] - 0x41 < 0)
                dest[bcdlen++] = ((src[i] - 0x30) << 4) | (src[i + 1] - 0x30);
            else
                dest[bcdlen++] = ((src[i] - 0x30) << 4) | (src[i + 1] - 0x37);
        }
        else
        {                       /* high byte is a character */

            if (src[i + 1] - 0x41 < 0)
                dest[bcdlen++] = ((src[i] - 0x37) << 4) | (src[i + 1] - 0x30);
            else
                dest[bcdlen++] = ((src[i] - 0x37) << 4) | (src[i + 1] - 0x37);
        }
    }

    return bcdlen;
}
void getbcdtm(unsigned char * buff)
{
    ASSERT(buff);


    char tmp[15];
    time_t t = time(NULL);

    struct tm *ltm = localtime(&t);

    sprintf(tmp, "%04d%02d%02d%02d%02d%02d", ltm->tm_year + TM_YEAR_BEGIN,
            ltm->tm_mon + TM_MONTH_BEGIN, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    memmove(tmp, tmp + 2, 12);
    tmp[12] = 0;
    atobcd(tmp, strlen(tmp), buff);
    return;
}

void dbg_prtcmd(const char *title, const unsigned char * cmd, size_t cmdlen)
{

    unsigned char tm[6];
    char buff[1024], *p;
    size_t i, j = 0;
    int current_log_level = default_message_loglevel;
    ASSERT(cmd);

    if (title)
    {
        strncpy(buff, title, sizeof(buff));
        p = buff;
        /* Do we have a loglevel in the string? */
        if (p[0] == '<')
        {
            unsigned char c = p[1];
            if (c && p[2] == '>')
            {
                switch (c)
                {
                case '0'...'7':    /* loglevel */
                    current_log_level = c - '0';
                case 'd':      /* DM_DEFAULT */
                    p += 3;
                    break;
                }
            }
        }
        if (current_log_level <= console_loglevel)
            fputs(p,stderr);
    }
    if (current_log_level <= console_loglevel)
    {
        if (current_log_level <= DEFAULT_MESSAGE_LOGLEVEL)
        {
            getbcdtm(tm);
            for (i = 3; i < 6; ++i)
                j += sprintf(buff + j, "%02X", tm[i]);
            buff[j++] = ' '; 
        }
        for (i = 0; i < cmdlen; ++i)
            j += sprintf(buff + j, "%02X ", cmd[i]);
        buff[j++] = '\n';
        buff[j++] = '\0';
        fputs(buff,stderr); 
    }

}

void dbg_printf(const char *fmt, ...)
{
    char logbuf[1024], *p;
    va_list args;
    int current_log_level = default_message_loglevel;

    va_start(args, fmt);
    vsnprintf(logbuf, sizeof(logbuf), fmt, args);
    p = logbuf;

    /* Do we have a loglevel in the string? */
    if (p[0] == '<')
    {
        unsigned char c = p[1];
        if (c && p[2] == '>')
        {
            switch (c)
            {
            case '0'...'7':    /* loglevel */
                current_log_level = c - '0';
            case 'd':          /* DM_DEFAULT */
                p += 3;
                break;
            }
        }
    }
    if (current_log_level <= console_loglevel)
    {
        fputs(p, stderr);
    }

    va_end(args);

}

