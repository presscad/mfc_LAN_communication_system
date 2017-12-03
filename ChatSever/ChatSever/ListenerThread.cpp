// ListenerThread.cpp : 实现文件
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
	 //初始化WSA
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(sockVersion, &wsaData)!=0)
    {
		pLog->AddString("通讯失败");
		return;
    }

    //创建套接字
   slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(slisten == INVALID_SOCKET)
    {
       pLog->AddString("socket error !");
	   return;
    }

    //绑定IP和端口
   // sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);
    sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY); 
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
		pLog->AddString("bind error!");
		return;
    }
	    //开始监听
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
	pLog->AddString("等待连接...");
    while (true)
    {
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
        if(sClient == INVALID_SOCKET)
        {
           pLog->AddString("接收错误!");
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
	pLog->AddString("停止连接");
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(ListenerThread, CWinThread)
END_MESSAGE_MAP()


// ListenerThread 消息处理程序


bool ListenerThread::Analysis(char* command)
{
	char type[5];
	strncpy(type,command,4);
	type[4]='\0';
	char cmd[255];
	strncpy(cmd,command+5,255);
	if(!strcmp(type,"#log")||!strcmp(type,"#que")){
		//用户查询登录操作
		m_AdoConn.OnInitADOConn ();
		_RecordsetPtr m_pRecordset;
		m_pRecordset=m_AdoConn.GetRecordSet (cmd);
		long m_cout=m_pRecordset->GetRecordCount();
		if (m_cout<=0)//测试当前记录号,判断是否有相同帐号存在
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
			pLog->AddString(m_id+"("+m_name+")"+"已登录。IP:"+m_ip);
		}
		m_AdoConn.ExitConnect();
	}else if(!strcmp(type,"#reg")||!strcmp(type,"#out")){
		//用户注册操作
		ADOConn m_AdoConn;
		m_AdoConn.OnInitADOConn ();
		if(!m_AdoConn.ExecuteSQL(cmd)){
		m_AdoConn.ExitConnect();//断开数据库连接
		return false;
		}
		pLog->AddString(cmd);
		return true;
	}else if(!strcmp(type,"#msg")){
		//用户发送消息操作
		pLog->AddString(cmd);
		pLog->SetCurSel(pLog->GetCount()-1);  //设置操作记录自动滚动
		for(std::list<CString>::iterator it=online.begin();it!=online.end();it++)
		{
			WORD sockVersion1= MAKEWORD(2,2);
			WSADATA data1;
			if(WSAStartup(sockVersion1, &data1) != 0)
			{
				pLog->AddString("建立失败!");
			}
			//创建套接字
			SOCKET sclient1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if(sclient1 == INVALID_SOCKET)
			{
				pLog->AddString("无效的 socket !");
			}
			//绑定IP和端口
			sockaddr_in serAddr1;
			serAddr1.sin_family = AF_INET;
			serAddr1.sin_port = htons(9999);
			serAddr1.sin_addr.S_un.S_addr = inet_addr(*it);
			
			if (connect(sclient1, (sockaddr *)&serAddr1, sizeof(serAddr1)) == SOCKET_ERROR)
			{
				online.remove(*it);
				pLog->AddString("发送失败到"+(*it));
			}
			else
			{
				send(sclient1, cmd, strlen(cmd), 0);
				closesocket(sclient1);//关闭一个套接口
				WSACleanup();//终止Winsock 2 DLL (Ws2_32.dll) 的使用
			}

		}

	}else if(!strcmp(type,"#ext")){   
		//用户退出操作
		 idlist.remove(cmd);
		 online.remove(inet_ntoa(remoteAddr.sin_addr));
		 pList->DeleteString(pList->FindString(0,cmd));
		 strcat(cmd,"已成功退出");
		 pLog->AddString(cmd);
		 pLog->SetCurSel(pLog->GetCount()-1);  //设置操作记录自动滚动
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
