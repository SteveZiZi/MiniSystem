#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "../include/stdinclude.h"

/* messgae class */
typedef struct _MESSAGE
{
	long msg_type;
	char msg_text[1];
}T_Message;

class CMessage
{
public:
  CMessage(char tmpChar);
  ~CMessage();
  bool CreateMsgQue(char tmpChar);
  bool SendMessage(int pid,const char* pbuf,int iBufLen);
  bool ReceiveMessage(int pid,char *pbuf,int &iBufLen);
  bool DestoryMegQue();
  bool GetMsgQueStruct(struct msqid_ds *buf);
  inline int GetMsgQueId()
  {
	return	MsgQueId; 	  	
  }

private:
	int MsgQueId;
};	


#endif




