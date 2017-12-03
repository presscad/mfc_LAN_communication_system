#pragma once
#include <winsock2.h>
#include"ADOConn.h"
#include<list>
// ListenerThread

class ListenerThread : public CWinThread
{
	DECLARE_DYNCREATE(ListenerThread)

protected:
	ListenerThread();           // 动态创建所使用的受保护的构造函数
	virtual ~ListenerThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	ADOConn m_AdoConn;

	SOCKET slisten;
	sockaddr_in sin;
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen;

	CListBox *pList;
	CListBox *pLog;

	std::list<CString> online;
	std::list<CString> idlist;

	CString m_name;
	CString m_id;
	CString m_ip;
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool Analysis(char* command);
	bool isOnline(CString id);
};


