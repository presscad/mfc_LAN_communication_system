#pragma once



// Accept

class Accept : public CWinThread
{
	DECLARE_DYNCREATE(Accept)

protected:
	Accept();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~Accept();

public:
	SOCKET slisten;
	sockaddr_in sin;
	SOCKET sClient;
    sockaddr_in remoteAddr;
	int nAddrlen;
	CEdit * c_rev;
	CString list;
	virtual BOOL InitInstance();
	virtual int ExitInstance();
protected:
	DECLARE_MESSAGE_MAP()
};


