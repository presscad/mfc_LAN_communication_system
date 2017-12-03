// ListenerThread.cpp : ʵ���ļ�
#include "stdafx.h"
#include "ChatSever.h"
#include "ListenerThread.h"
#include<map>

// ListenerThread
IMPLEMENT_DYNCREATE(ListenerThread, CWinThread)

ListenerThread::ListenerThread()
{
	pList=(CListBox*)GetMainWnd()->GetDlgItem(IDC_Users);
	pLog=(CListBox*)GetMainWnd()->GetDlgItem(IDC_LOG);
	 //��ʼ��WSA
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(sockVersion, &wsaData)!=0)
    {
		pLog->AddString("ͨѶʧ��");
		return;
    }

    //�����׽���
   slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(slisten == INVALID_SOCKET)
    {
       pLog->AddString("socket error !");
	   return;
    }

    //��IP�Ͷ˿�
   // sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);
    sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY); 
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
		pLog->AddString("bind error!");
		return;
    }
	    //��ʼ����
    if(listen(slisten, 5) == SOCKET_ERROR)
    {
		 pLog->AddString("listen error !");
		 return;
    }
}

ListenerThread::~ListenerThread()
{
}

BOOL ListenerThread::InitInstance()
{
    nAddrlen = sizeof(remoteAddr);
    char revData[255]; 
	pLog->AddString("�ȴ�����...");
    while (true)
    {
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
        if(sClient == INVALID_SOCKET)
        {
           pLog->AddString("���մ���!");
		   return false;
        }
		
        int ret = recv(sClient, revData, 255, 0);    
        if(ret > 0)
        {
            revData[ret] = 0x00;
			if(Analysis(revData)){	
				send(sClient, "success", strlen("success"), 0);
				Sleep(100);
				send(sClient,m_name,strlen(m_name),0);
			}else{
				send(sClient, "fail", strlen("fail"), 0);
			}
        }
        closesocket(sClient);
    }
	return TRUE;
}

int ListenerThread::ExitInstance()
{
	closesocket(sClient);
	closesocket(slisten);
	idlist.clear();
	online.clear();
	for(int i=pList->GetCount();i>=0;i--)
	pList->DeleteString(i);
	pLog->AddString("ֹͣ����");
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(ListenerThread, CWinThread)
END_MESSAGE_MAP()


// ListenerThread ��Ϣ�������


bool ListenerThread::Analysis(char* command)
{
	char type[5];
	strncpy(type,command,4);
	type[4]='\0';
	char cmd[255];
	strncpy(cmd,command+5,255);
	if(!strcmp(type,"#log")||!strcmp(type,"#que")){
		//�û���ѯ��¼����
		m_AdoConn.OnInitADOConn ();
		_RecordsetPtr m_pRecordset;
		m_pRecordset=m_AdoConn.GetRecordSet (cmd);
		long m_cout=m_pRecordset->GetRecordCount();
		if (m_cout<=0)//���Ե�ǰ��¼��,�ж��Ƿ�����ͬ�ʺŴ���
		{
		m_AdoConn.ExitConnect();
		return false;
		}
	
		if(!strcmp(type,"#log"))	{
			m_id=(LPCTSTR)(_bstr_t) m_pRecordset->GetCollect("clientid");
		 	m_name=(LPCTSTR)(_bstr_t) m_pRecordset->GetCollect("clientname");
			m_ip=(LPCTSTR)(_bstr_t)inet_ntoa(remoteAddr.sin_addr);
			if(isOnline(m_id)) return false;
			idlist.push_back(m_id);
			online.push_back(m_ip);
			pList->AddString(m_id+"  "+m_name+"  "+m_ip);
			pLog->AddString(m_id+"("+m_name+")"+"�ѵ�¼��IP:"+m_ip);
		}
		m_AdoConn.ExitConnect();
	}else if(!strcmp(type,"#reg")||!strcmp(type,"#out")){
		//�û�ע�����
		ADOConn m_AdoConn;
		m_AdoConn.OnInitADOConn ();
		if(!m_AdoConn.ExecuteSQL(cmd)){
		m_AdoConn.ExitConnect();//�Ͽ����ݿ�����
		return false;
		}
		pLog->AddString(cmd);
		return true;
	}else if(!strcmp(type,"#msg")){
		//�û�������Ϣ����
		pLog->AddString(cmd);
		pLog->SetCurSel(pLog->GetCount()-1);  //���ò�����¼�Զ�����
		for(std::list<CString>::iterator it=online.begin();it!=online.end();it++)
		{
			WORD sockVersion1= MAKEWORD(2,2);
			WSADATA data1;
			if(WSAStartup(sockVersion1, &data1) != 0)
			{
				pLog->AddString("����ʧ��!");
			}
			//�����׽���
			SOCKET sclient1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if(sclient1 == INVALID_SOCKET)
			{
				pLog->AddString("��Ч�� socket !");
			}
			//��IP�Ͷ˿�
			sockaddr_in serAddr1;
			serAddr1.sin_family = AF_INET;
			serAddr1.sin_port = htons(9999);
			serAddr1.sin_addr.S_un.S_addr = inet_addr(*it);
			
			if (connect(sclient1, (sockaddr *)&serAddr1, sizeof(serAddr1)) == SOCKET_ERROR)
			{
				online.remove(*it);
				pLog->AddString("����ʧ�ܵ�"+(*it));
			}
			else
			{
				send(sclient1, cmd, strlen(cmd), 0);
				closesocket(sclient1);//�ر�һ���׽ӿ�
				WSACleanup();//��ֹWinsock 2 DLL (Ws2_32.dll) ��ʹ��
			}

		}

	}else if(!strcmp(type,"#ext")){   
		//�û��˳�����
		 idlist.remove(cmd);
		 online.remove(inet_ntoa(remoteAddr.sin_addr));
		 pList->DeleteString(pList->FindString(0,cmd));
		 strcat(cmd,"�ѳɹ��˳�");
		 pLog->AddString(cmd);
		 pLog->SetCurSel(pLog->GetCount()-1);  //���ò�����¼�Զ�����
	}

	return true;
}







bool ListenerThread::isOnline(CString id)
{
	for(std::list<CString>::iterator it=idlist.begin();it!=idlist.end();it++){
		if(!(*it).Compare(id)) return true;
	}
	return false;
}
