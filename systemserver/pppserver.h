#ifndef _PPPSERVER_H_
#define _PPPSERVER_H_

#include "server.h"

class PPPServer:public server
{
public:
	PPPServer(T_SHARE_MEM *p);
	void OntickServer();
	long GetTick();
	void HeartBeat();
	
private:
	long pppTick;		
	T_SHARE_MEM *pMem;
};

#endif

