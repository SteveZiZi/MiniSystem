#ifndef INCLUDED_CONTEXT
#define INCLUDED_CONTEXT

#include "ShareMem.h"
#include "../base/FileBase.h"


#define FILE_DYJC_CONTEXT PATH_BASE"/ramdisk/share/context.dat"	

struct Context
{
	struct HeaderChecker Checker;
	Context();
	static Context& Instance();
public:
	int m_pid;
	
private:
	static bool InitFile(FILE* fp, void* ipOther);
	static bool CheckFile(FILE* fp, void* ipOther);
	int Save(bool ibForce);
private:	
	static ShareMem m_ShareMem;
};

#define CONTEXT Context::Instance()
#define DECLARE_CONTEXT(context) Context& context=CONTEXT

#endif

