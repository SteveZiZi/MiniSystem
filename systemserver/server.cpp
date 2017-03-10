#include "server.h"

long server::minuteTick = 0;	
T_SHARE_MEM* server::pFatherMem = NULL;	

void server::UpdateTick(int signum)
{

	if (signum == SIGALRM)
	{
		//minuteTick++;
		if (pFatherMem != NULL)
		{
			//pFatherMem->minuteTick = minuteTick;
			pFatherMem->minuteTick++;
			printf("pid %d update system time tick .minuteTick= %d ..\n",getpid(),pFatherMem->minuteTick);
			alarm(60);
		}
	}

}

void server::SetMemoryAddress(T_SHARE_MEM *p)
{
	pFatherMem = p;	
}

void server::SigInstall()
{
	sigset_t sigSet;
	struct sigaction sigact;
	
	if (sigemptyset(&sigSet) < 0)
	{
		printf("initial signal muster fail \n");
	}
	
	if (sigaddset(&sigSet,SIGALRM))
	{
		printf("Add SIGALRM signal fail");
	}
	
	if (sigprocmask(SIG_UNBLOCK,&sigSet,NULL) < 0)
	{
		printf("Set SIGALRM signal is unblock fail \n");
	}
	
	sigemptyset(&sigact.sa_mask);
	sigact.sa_handler = (void (*)(int))UpdateTick;
	sigaction(SIGALRM,&sigact,NULL);
	/* start timer*/
	alarm(60);
	
}	

long server::GetTick()
{
	if (pFatherMem != NULL)
	{
		return pFatherMem->minuteTick;
	}
	else
	{
		return 0;
	}
}

