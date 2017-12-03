// DENGLU.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "DENGLU.h"
#include "afxdialogex.h"


// DENGLU 对话框

IMPLEMENT_DYNAMIC(DENGLU, CDialogEx)

DENGLU::DENGLU(CWnd* pParent /*=NULL*/)
	: CDialogEx(DENGLU::IDD, pParent)
	, m_send(_T(""))
	, m_rev(_T(""))
{
	
	m_ip = _T("");
}

DENGLU::~DENGLU()
{
}

void DENGLU::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SEND, m_send);
	DDX_Text(pDX, IDC_EDIT2, m_rev);
	DDX_Control(pDX, IDC_EDIT2, m_crev);
	DDX_Control(pDX, IDC_TX, m_tx);
}


BEGIN_MESSAGE_MAP(DENGLU, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DENGLU::OnBnClickedButton1)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
//	ON_EN_CHANGE(IDC_EDIT2, &DENGLU::OnChangeEdit2)
//ON_EN_UPDATE(IDC_EDIT2, &DENGLU::OnUpdateEdit2)
ON_BN_CLICKED(IDC_BUTTON2, &DENGLU::OnBnClickedButton2)
END_MESSAGE_MAP()


// DENGLU 消息处理程序


void DENGLU::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);
	CString str; //获取系统时间 　　
	CTime tm; tm=CTime::GetCurrentTime();
	str=tm.Format("%X");
	tongxin("#msg "+m_name+"("+m_id+") "+str+"\r\n    "+m_send);
	UpdateData(FALSE);
	GetDlgItem(IDC_SEND)->SetWindowTextA("");
	GetDlgItem(IDC_SEND)->SetFocus();
	
}




void DENGLU::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	GetDlgItem(IDC_NAME)->SetWindowTextA(m_name);
	GetDlgItem(IDC_ID)->SetWindowTextA(m_id);
	GetDlgItem(IDC_IP)->SetWindowTextA("服务端IP:"+m_ip);
	acp=(Accept*)AfxBeginThread(RUNTIME_CLASS(Accept));
	HBITMAP hBitmap;
// 显示资源中的图像（仅限位图BMP）
	hBitmap =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);  
	m_tx.SetBitmap(hBitmap);

	// TODO: 在此处添加消息处理程序代码
}


void DENGLU::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	tongxin("#ext "+m_id);
	TerminateThread(acp->m_hThread,0);
	CloseHandle(acp->m_hThread);
	CDialogEx::OnClose();
}


void DENGLU::tongxin(CString cmd)
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
		char temp[6];
		strncpy(temp,cmd,4);
		temp[4]='\0';
		//AfxMessageBox(temp);
		if(strcmp("#ext",temp))
		{
			AfxMessageBox("发送失败");
		}
	}
	else
	{
		//AfxMessageBox("连接成功\n");
		//temp="#msg "+m_name+":"+m_send;
		char *sendData;
		sendData =(LPSTR)(LPCSTR)cmd;//需要发送的信息
		send(sclient, sendData, strlen(sendData), 0);
		closesocket(sclient);//关闭一个套接口
		WSACleanup();//终止Winsock 2 DLL (Ws2_32.dll) 的使用
	}
}

void DENGLU::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str; //获取系统时间 　　
	CTime tm; tm=CTime::GetCurrentTime();
	str=tm.Format("%X");
	tongxin("#msg 悟空(*****) "+str+"\r\n    "+m_send);
	UpdateData(FALSE);
	GetDlgItem(IDC_SEND)->SetWindowTextA("");
	GetDlgItem(IDC_SEND)->SetFocus();
}
