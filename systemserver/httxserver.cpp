#include "httxserver.h"

HttxServer::HttxServer(T_SHARE_MEM *p)
{
	pMem = p;
}

void HttxServer::OntickServer()
{
	CSysIpc::SetHttxPid(getpid());
	HeartBeat();
	/* send mesage test */
//	bstring sendpackage;
	//sendpackage.append((unsigned char *)("hello, hao are you!\n"));
	char *p = "hello,hao are you!";
	CSysIpc::IPC_HttxToDbcj(p,19);
	/* test end */
	sleep(20);
}

long HttxServer::GetTick()
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

void HttxServer::HeartBeat()
{
	httxTick = GetTick();
	printf("HttxServer: hear beat %d ... \n ",httxTick);
}


