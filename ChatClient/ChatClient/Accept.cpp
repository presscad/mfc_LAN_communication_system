// Accept.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "Accept.h"


// Accept

IMPLEMENT_DYNCREATE(Accept, CWinThread)

Accept::Accept()
{
	c_rev=(CEdit*)GetMainWnd()->GetDlgItem(IDC_EDIT2);
	//��ʼ��WSA
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(sockVersion, &wsaData)!=0)
    {
		AfxMessageBox("ʧ�ܣ�");
        
    }
	//�����׽���
    slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(slisten == INVALID_SOCKET)
    {
        AfxMessageBox("�����׽���ʧ�ܣ�");
    }
	//��IP�Ͷ˿�
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9999);
    sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        AfxMessageBox("bind error !");
    }

    //��ʼ����
    if(listen(slisten, 5) == SOCKET_ERROR)
    {
        AfxMessageBox("listen error !");
    }


}

Accept::~Accept()
{
}

BOOL Accept::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��

    //ѭ����������
    nAddrlen = sizeof(remoteAddr);
    char revData[255];
    while (true)
    {
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
        if(sClient == INVALID_SOCKET)
        {
            AfxMessageBox("accept error !");
        }
        //��������
        int ret = recv(sClient, revData, 255, 0);    
        if(ret > 0)
        {
            revData[ret] = 0x00;
			list=list+revData+"\r\n";
			c_rev->SetWindowTextA(list);
			c_rev->LineScroll(c_rev->GetLineCount());
			
        }
        closesocket(sClient);
    }
    closesocket(slisten);
    WSACleanup();
	return TRUE;
}

int Accept::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(Accept, CWinThread)
END_MESSAGE_MAP()


// Accept ��Ϣ�������
