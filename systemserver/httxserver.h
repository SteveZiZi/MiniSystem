#ifndef _HTTXSERVER_H_
#define _HTTXSERVER_H_

#include "server.h"

class HttxServer:public server
{
public:
	HttxServer(T_SHARE_MEM *p);
	void OntickServer();
	long GetTick();
	void HeartBeat();
	
private:
	long httxTick;		
	T_SHARE_MEM *pMem;
};	

#endif


