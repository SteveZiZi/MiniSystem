#ifndef _SERVER_H_
#define _SERVER_H_

#include "../include/stdinclude.h"
#include "../sysipc/sysipc.h"

class server
{
public:
	virtual void OntickServer(){}
	static void UpdateTick(int signum);
	
	static void SetMemoryAddress(T_SHARE_MEM *p);
	
	static void SigInstall();
	static long GetTick();

private:
	static long minuteTick;	
	static T_SHARE_MEM *pFatherMem;
};

#endif 


