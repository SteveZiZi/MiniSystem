#include "sysipc.h"

CMessage CSysIpc::MsgQue('a');

T_SHARE_MEM* CSysIpc::pMem = NULL;

void CSysIpc::SetShareMemAddr(T_SHARE_MEM *p)
{
	pMem = p;
	return;
}

void CSysIpc::SetDbcjPid(int pid)
{
	if (pMem != NULL)
	{
		pMem->dbcjpid = pid;
	}
	return;
}
void CSysIpc::SetHttxPid(int pid)
{
	
	if (pMem != NULL)
	{
		pMem->httxpid = pid;
	}
	return;
}
void CSysIpc::SetPPPPid(int pid)
{
	if (pMem != NULL)
	{
		pMem->ppppid = pid;
	}
	return;
}
int CSysIpc::GetDbcjPid()
{
	if (pMem != NULL)
	{
		return pMem->dbcjpid;
	}
	return -1;
}
int CSysIpc::GetHttxPid()
{
	if (pMem != NULL)
	{
		return pMem->httxpid;
	}
	return -1;
}
int CSysIpc::GetPPPPid()
{
	if (pMem != NULL)
	{
		return pMem->ppppid;
	}
	return -1;
}

bool CSysIpc::IPC_HttxToDbcj(char *pbuf, int datalen)
{
	T_IPCINFO ipcInfo;

	ipcInfo.DestPid = CSysIpc::GetDbcjPid();
	ipcInfo.SourcePid = CSysIpc::GetHttxPid();
	ipcInfo.pbuffer = (char*)malloc(datalen+sizeof(T_IPCINFO));

	memcpy(ipcInfo.pbuffer,(char *)(&(ipcInfo.DestPid)),sizeof(ipcInfo.DestPid));
	memcpy(ipcInfo.pbuffer+sizeof(ipcInfo.DestPid),(char *)(&(ipcInfo.SourcePid)),sizeof(ipcInfo.SourcePid));
	memcpy(ipcInfo.pbuffer+sizeof(ipcInfo.DestPid),pbuf,datalen);

	ipcInfo.BufLen = datalen+sizeof(T_IPCINFO);

	if (MsgQue.SendMessage(ipcInfo.DestPid,(char *)ipcInfo.pbuffer,ipcInfo.BufLen) == false)
	{
		printf(" httx send message to dbcj fail.\n");
		free(ipcInfo.pbuffer);
		return false;
	}
	else
	{
		printf(" httx send message to dbcj sucess.\n");
		free(ipcInfo.pbuffer);
		return true;
	}
}

bool CSysIpc::IPC_GetIpcInfo(T_IPCINFO &ipc)
{
	return MsgQue.ReceiveMessage(ipc.SourcePid,ipc.pbuffer,ipc.BufLen);
}

bool CSysIpc::IPC_GetIpcData(int pid,char *pbuf,int &datalen)
{
	T_IPCINFO ipc;
	int tempLen = sizeof(ipc.DestPid)+sizeof(ipc.SourcePid);

	ipc.SourcePid = pid;
	ipc.pbuffer = (char*)malloc(datalen+sizeof(T_IPCINFO));
	ipc.BufLen = datalen+sizeof(T_IPCINFO);
	
	if (IPC_GetIpcInfo(ipc)== true)
	{
		if (datalen < ipc.BufLen - tempLen)
		{
			printf("message receive buffer size is not enough\n");
		}
		memcpy(pbuf,ipc.pbuffer+tempLen,ipc.BufLen - tempLen);
		datalen = ipc.BufLen - tempLen;
		free(ipc.pbuffer);
		return true;
	}
	else
	{
		free(ipc.pbuffer);
		return false;
	}
}
