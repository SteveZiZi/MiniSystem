#ifndef _SYSIPC_H_
#define _SYSIPC_H_

#include "message.h"

typedef struct _IPCINFO
{
	int DestPid;
	int SourcePid;
	char *pbuffer;
	int BufLen;
}T_IPCINFO;


class CSysIpc
{
public:
	static void SetShareMemAddr(T_SHARE_MEM *p);
	static void SetDbcjPid(int pid);
	static void SetHttxPid(int pid);
	static void SetPPPPid(int pid);
	static int GetDbcjPid();
	static int GetHttxPid();
	static int GetPPPPid();
	
	static bool IPC_HttxToDbcj(char *pbuf, int datalen);
	static bool IPC_GetIpcInfo(T_IPCINFO &ipc);
	static bool IPC_GetIpcData(int pid,char *pbuf,int &datalen);

private:	
	static CMessage MsgQue;
	static T_SHARE_MEM *pMem;
};


#endif

