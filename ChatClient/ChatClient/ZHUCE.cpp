// ZHUCE.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ZHUCE.h"
#include "afxdialogex.h"

// ZHUCE 对话框

IMPLEMENT_DYNAMIC(ZHUCE, CDialogEx)

ZHUCE::ZHUCE(CWnd* pParent /*=NULL*/)
	: CDialogEx(ZHUCE::IDD, pParent)
	, m_Tip(_T(""))
	, m_name(_T(""))
	, m_id(_T(""))
	, m_pwd(_T(""))
	, m_rpwd(_T(""))
{

}

ZHUCE::~ZHUCE()
{
}

void ZHUCE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TIP, m_Tip);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_ID, m_id);
	DDX_Text(pDX, IDC_PWD, m_pwd);
	DDX_Text(pDX, IDC_RPWD, m_rpwd);
}


BEGIN_MESSAGE_MAP(ZHUCE, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &ZHUCE::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ZHUCE::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_NAME, &ZHUCE::OnEnChangeName)
	ON_BN_CLICKED(IDC_BUTTON5, &ZHUCE::OnBnClickedButton5)
END_MESSAGE_MAP()


// ZHUCE 消息处理程序


void ZHUCE::OnBnClickedButton3()
{
	UpdateData(TRUE);
	bool id=true;
	bool id1=true;
	bool name=true;
	bool pwd=true;//长度为6
	bool rpwd=true;//密码是否一致
	int idcount=m_id.GetLength();
	int namecount=m_name.GetLength();
	int pwdcount=m_pwd.GetLength();
	if(idcount!=5)	{
		id=false;
		
	}
	if(namecount==0 || namecount>10)	name=false;
	if(pwdcount!=6)	pwd=false;
	if(m_pwd!=m_rpwd)	rpwd=false;
	for(int i=0;i<idcount;i++)
	{
		if(m_id.GetAt(i)<48 || m_id.GetAt(i)>57)
		{
			id=false;
			break;
		}
	}
	m_Tip="";
	UpdateData(FALSE);
	if(id && id1 && name && pwd && rpwd)
	{
		
		m_Tip="#que Select user.* from [user] where clientid="+m_id;//发送判断注册用户id
		char* p=(LPSTR)(LPCSTR)m_Tip;
		if(strcmp(tongxin(p),"success"))
		{
			m_Tip="#reg INSERT INTO [user] (clientid,clientpwd,clientname) VALUES ("+m_id+",'" +m_pwd + "','" + m_name +"')"; //  执行INSERT语句	
			p=(LPSTR)(LPCSTR)m_Tip;
			if(!strcmp(tongxin(p),"success"))
			{
				AfxMessageBox("注册成功");
				CDialog::OnCancel();
			}
		}
		else
		{
			m_Tip="账号已存在！";
			UpdateData(FALSE);
		}
	}
	else
	{
		if(!id)
		{
			m_Tip=m_Tip+"用户id格式输入错误，请重新输入!\n";
			m_id="";
		}
		if(!name)
		{
			m_Tip=m_Tip+"用户名输入错误，请重新输入!\n";
			m_name="";
		}
		if(!pwd)
		{
			m_Tip=m_Tip+"用户密码格式输入错误，请重新输入!\n";
			m_pwd="";
			m_rpwd="";
		}
		if(!rpwd)
		{
			m_Tip=m_Tip+"用户密码输入不一致，请重新输入!\n";
			m_rpwd="";
			m_pwd="";
		}
		UpdateData(FALSE);
	}
	
}


void ZHUCE::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void ZHUCE::OnEnChangeName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



char * ZHUCE::tongxin(char * sqlcmd)
{
	//初始化WSA
	WORD sockVersion= MAKEWORD(2,2);
	WSADATA data;
	if(WSAStartup(sockVersion, &data) != 0)
	{
		AfxMessageBox("失败!");
		
	}

	//创建套接字
	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sclient == INVALID_SOCKET)
	{
		AfxMessageBox("无效的 socket !");
	}
	//绑定IP和端口
    sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = inet_addr(m_ip);
	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		//AfxMessageBox("连接失败\n");
		m_Tip="连接失败\n";
		UpdateData(FALSE);
		//AfxMessageBox(inet_ntoa(serAddr.sin_addr));
	}
	else
	{
		//AfxMessageBox("连接成功\n");
		char *sendData;
		sendData =sqlcmd;//需要发送的信息
		send(sclient, sendData, strlen(sendData), 0);
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if(ret > 0)
		{
			recData[ret] = 0x00;
			m_Tip=recData;
			UpdateData(FALSE);
		}
		closesocket(sclient);//关闭一个套接口
		WSACleanup();//终止Winsock 2 DLL (Ws2_32.dll) 的使用
		return recData;
	}

}


void ZHUCE::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(hefa())
	{
		m_Tip="#out delete from [user] where clientid="+m_id+" and clientname='" + m_name +"'"+" and clientpwd='" + m_pwd +"'"; //  执行DElete语句	
		char *p=(LPSTR)(LPCSTR)m_Tip;
		if(!strcmp(tongxin(p),"success"))
		{
			AfxMessageBox("销号成功");
			CDialog::OnCancel();
		}
		else
		{
			AfxMessageBox("销号失败");
		}
	}
}


bool ZHUCE::hefa(void)
{
	UpdateData(TRUE);
	bool id=true;
	bool id1=true;
	bool name=true;
	bool pwd=true;//长度为6
	bool rpwd=true;//密码是否一致
	int idcount=m_id.GetLength();
	int namecount=m_name.GetLength();
	int pwdcount=m_pwd.GetLength();
	if(idcount!=5)	{
		id=false;
		
	}
	if(namecount==0 || namecount>10)	name=false;
	if(pwdcount!=6)	pwd=false;
	if(m_pwd!=m_rpwd)	rpwd=false;
	for(int i=0;i<idcount;i++)
	{
		if(m_id.GetAt(i)<48 || m_id.GetAt(i)>57)
		{
			id=false;
			break;
		}
	}
	m_Tip="";
	UpdateData(FALSE);
	if(id && id1 && name && pwd && rpwd)
		return true;
	else
		return false;
}
