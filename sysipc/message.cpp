#include "message.h"

CMessage::CMessage(char tmpChar)
{
	CreateMsgQue(tmpChar);
}

CMessage::~CMessage()
{
	DestoryMegQue();
}

bool CMessage::CreateMsgQue(char tmpChar)
{
	key_t key;	
	
	if ((key=ftok(".",tmpChar)) == -1)
	{
		printf("ftok error! \n");
		return false;
	}
	
	/* create message queue */
	if ((MsgQueId = msgget(key,IPC_CREAT|0666)) == -1)
	{
		printf(" message queue create error! \n");
		return false;
	}
	
	return true;
}

bool CMessage::SendMessage(int pid,const char* pbuf,int iBufLen)
{
		T_Message *pSndMsg;
		
		printf("SendMessage : pid= %d ,pbuf=%d, iBufLen=%d",pid,pbuf,iBufLen);
		if (pid <= 0 || pbuf == NULL || iBufLen == 0)
		{
			return false;
		}
		
		pSndMsg = (T_Message *)malloc(iBufLen+sizeof(pid));
		pSndMsg->msg_type= pid;
		memcpy(pSndMsg->msg_text,pbuf,iBufLen);
		int iResult=msgsnd(MsgQueId,(void *)pSndMsg,iBufLen+sizeof(pid),IPC_NOWAIT);
		if (iResult == -1)
		{
				iResult=msgsnd(MsgQueId,(void *)pSndMsg,iBufLen+sizeof(pid),IPC_NOWAIT);
				if (iResult == -1)
				{
					printf("send to message to pid %d fail!",pid);
					free(pSndMsg);
					return false;
				}
		}
		free(pSndMsg);
		return true;
}

bool CMessage::ReceiveMessage(int pid,char *pbuf,int &iBufLen)
{
	T_Message *RecMsg;
	int ioDataLen = 0;
	printf("ReceiveMessage : pid= %d ,pbuf=%d, iBufLen=%d",pid,pbuf,iBufLen);
	if (pid <= 0 || pbuf == NULL || iBufLen == 0)
	{
		return false;
	}
	
	RecMsg = (T_Message *)pbuf;
	int iResult = msgrcv(MsgQueId,RecMsg,ioDataLen,pid,IPC_NOWAIT);
	if (iResult == -1)
	{
		return false;
	}
	printf("receive message length = %d \n",iResult);
	ioDataLen = iResult;
	pbuf += sizeof(long); // abandom message.msg_type 
	iBufLen = ioDataLen-sizeof(long);
	return true;	
}
bool CMessage::DestoryMegQue()	
{
	if (MsgQueId < 1)
	{
		return false;
	}
	
	int result = msgctl(MsgQueId,IPC_RMID,NULL);
	if (result == -1)
	{
		printf("MsgQueId %d remove fail.\n",MsgQueId);
		return false;
	}
	return true;

}	





