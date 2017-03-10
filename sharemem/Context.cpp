#include "Context.h"


ShareMem Context::m_ShareMem;

Context::Context()
{
	memset(this,0,sizeof(*this));
	Checker.Init();
}

bool Context::InitFile(FILE* fp, void* ipOther)
{
	ASSERT(fp);
	if (fseek(fp,0L ,SEEK_SET)!=0)
	{
		printf("fseek(fp,0L ,SEEK_SET) error in Context::InitFile\n");
		return false;
	}
	Context* pContext=new Context;
	bool bResult=(fwrite(pContext,sizeof(Context),1,fp)==1);
	delete pContext;
	return bResult;
}

bool Context::CheckFile(FILE* fp, void* ipOther)
{
	if (fseek(fp,0L,SEEK_END)!=0)
	{
		printf("fseek(fp,0L,SEEK_END) error in Context::InitFile\n");
		return false;
	}
	long len=ftell(fp);
	if (len>0 && (unsigned int)len==sizeof(Context))
	{
		fseek(fp,0 ,SEEK_SET);
		HeaderChecker checker;
		if (fread(&checker,sizeof(HeaderChecker),1,fp)==1)
		{
			HeaderChecker initChecker;
			if (memcmp(&checker,&initChecker,sizeof(HeaderChecker))==0)
			{
				return true;
			}
		}
	}
	printf("Context file check return false\n");
	return false;
}


Context& Context::Instance()
{	
	static Context* pContext=NULL;
	if (pContext==NULL)
	{
		if (m_ShareMem.IsInited()==false)
		{
			m_ShareMem.Init(FILE_DYJC_CONTEXT,sizeof(Context),Context::InitFile,Context::CheckFile,NULL);
			m_ShareMem.OpenShareMemFile(Context::InitFile,Context::CheckFile,NULL);
		}
		pContext=(Context*)m_ShareMem.GetMem();
	}
	ASSERT(pContext!=NULL);
	ASSERT(pContext==m_ShareMem.GetMem());
	return *pContext;
}

int Context::Save(bool ibForce)
{
	if (ibForce==true)
	{
		if (m_ShareMem.Save(this,sizeof(*this))==true)
		{
			printf("Save Status succeed(%s)\n",ibForce?"force request":"changed");
			return 0;
		}
		else
		{
			printf("Save Status failed(%s)\n",ibForce?"force request":"changed");
		}
	}
	return -1;
}


