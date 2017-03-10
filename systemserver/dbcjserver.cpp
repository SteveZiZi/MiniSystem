#include "dbcjserver.h"
#include "../sharemem/context.h"

DbcjServer::DbcjServer(T_SHARE_MEM *p)
{
	pMem = p;
}
void DbcjServer::OntickServer()
{
	CSysIpc::SetDbcjPid(getpid());
	HeartBeat();
	/* receve message test */
	char ch[200] = {0};
	int len = 200;
	CSysIpc::IPC_GetIpcData(CSysIpc::GetDbcjPid(),ch,len);
	printf(" len = %d \n",len);
	for (int i=0; i<len; i++)
	{
		printf("%c ",ch[i]);
	}
	printf("\n");
	/* end */
	sleep(30);
}
long DbcjServer::GetTick()
{
	if (pMem != NULL)
	{
		return pMem->minuteTick;
	}
	else
	{
		return 0;
	}
}
void DbcjServer::HeartBeat()
{
	dbcjTick = GetTick();
	CONTEXT.m_pid = dbcjTick;
	printf("CONTEXT.m_pid%d ...\n",CONTEXT.m_pid);
}

