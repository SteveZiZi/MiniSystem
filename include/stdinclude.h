#ifndef _STDINCLUDE_H_
#define _STDINCLUDE_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <vector>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/shm.h>
#include "type.h"

using namespace std;
#include <string>




#define MEMORY_BUF_SIZE 100



typedef struct _SHARE_MEM
{
	long minuteTick;
	int dbcjpid;
	int httxpid;
	int ppppid;
	char buf[100];
}T_SHARE_MEM;

#endif


