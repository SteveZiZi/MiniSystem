#ifndef _DBCJSERVER_H_
#define _DBCJSERVER_H_

#include "server.h"

class DbcjServer:public server
{
public:
	DbcjServer(T_SHARE_MEM *p);

	void OntickServer();
	long GetTick();
	void HeartBeat();

private:
	long dbcjTick;	
	T_SHARE_MEM *pMem;
};	

#endif


