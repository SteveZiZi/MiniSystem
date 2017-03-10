
#ifndef DEBUG_H
#define DEBUG_H

#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include "../include/type.h"

#define CCE_LISTEN_PORT 7090
#define _MONITOR  	0x05

#define _DEBUG                  /* Debug key */

#ifndef _LINUXPC                /* Program run environment */
#define NDEBUG                  /* Disable macro assert */
#endif

#define	DM_EMERG	"<0>"       /* system is unusable           */
#define	DM_ALERT	"<1>"       /* action must be taken immediately */
#define	DM_CRIT	    "<2>"       /* critical conditions          */
#define	DM_ERR	    "<3>"       /* error conditions         */
#define	DM_WARNING	"<4>"       /* warning conditions           */
#define	DM_NOTICE	"<5>"       /* normal but significant condition */
#define	DM_INFO	    "<6>"       /* informational            */
#define	DM_DEBUG	"<7>"       /* debug-level messages         */

/* Use the default dm loglevel */
#define DM_DEFAULT	"<d>"

extern int console_printk[];

#define console_loglevel (console_printk[0])
#define default_message_loglevel (console_printk[1])
#define minimum_console_loglevel (console_printk[2])
#define default_console_loglevel (console_printk[3])

void dbg_init(int fd);

/*
 * Function:   Hex string convert to ascii string,then output
 *             For instance: 0x01,0x02,0x03,0x04 ==> "01 02 03 04"
 * Parameters: title  - Some info for hex string, may be NULL
 *             cmd    - Hex string
 *             cmdlen - Hex string length
 * Return:     None
 *
 */
void dbg_prtcmd(const char *title, const unsigned char * cmd, size_t cmdlen);

/*
 * Function:   Print debug info,simulate "printf" that in C library
 * Parameters: fmt - Parameter list
 * Return:     None
 *
 */

void dbg_printf(const char *fmt, ...);

#define _dbg_printf(level, fmt, arg...) dbg_printf(level "<%s - %s():%d>  " fmt, __FILE__, __func__, __LINE__ , ## arg)
#endif

