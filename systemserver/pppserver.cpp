#include "pppserver.h"


PPPServer::PPPServer(T_SHARE_MEM *p)
{
	pMem = p;
}

void PPPServer::OntickServer()
{
	CSysIpc::SetPPPPid(getpid());
	HeartBeat();
	sleep(60);
}

long PPPServer::GetTick()
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

void PPPServer::HeartBeat()
{
	pppTick = GetTick();
	printf("PPPServer: hear beat %d ... \n",pppTick);
}

