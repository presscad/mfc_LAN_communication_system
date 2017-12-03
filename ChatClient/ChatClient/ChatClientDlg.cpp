
// 局域网通信系统Dlg.cpp : 实现文件

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C局域网通信系统Dlg 对话框




C局域网通信系统Dlg::C局域网通信系统Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C局域网通信系统Dlg::IDD, pParent)
	, m_Tip(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_id = _T("");
	m_pwd = _T("");
}

void C局域网通信系统Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ServerIp, m_ServerIp);
	DDX_Text(pDX, IDC_TIP, m_Tip);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
	DDX_Control(pDX, IDC_TX, m_tx);
}

BEGIN_MESSAGE_MAP(C局域网通信系统Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C局域网通信系统Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C局域网通信系统Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C局域网通信系统Dlg::OnBnClickedButton3)
//	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// C局域网通信系统Dlg 消息处理程序

BOOL C局域网通信系统Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C局域网通信系统Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C局域网通信系统Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	
	CString lpPath = _T(".\\peizhi.ini");
	TCHAR userId[10];
	TCHAR passWord[10];
	TCHAR Ip[20];
	::GetPrivateProfileString("denglu","UserId",NULL,userId,10,lpPath);
	::GetPrivateProfileString("denglu","UserPassWord",NULL,passWord,10,lpPath);
	::GetPrivateProfileString("denglu","ServerIp",NULL,Ip,20,lpPath);
	GetDlgItem(IDC_ServerIp)->SetWindowTextA(Ip);
	GetDlgItem(IDC_EDIT1)->SetWindowTextA(userId);
	GetDlgItem(IDC_EDIT2)->SetWindowTextA(passWord);
	HBITMAP hBitmap;
	// 显示资源中的图像（仅限位图BMP）
	hBitmap =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);  
	m_tx.SetBitmap(hBitmap);
	
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C局域网通信系统Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C局域网通信系统Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_id.GetLength()==5 && m_pwd.GetLength()==6)
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
		serAddr.sin_addr.S_un.S_addr = inet_addr(strIP);
		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{
			//AfxMessageBox("连接失败\n");
			m_Tip="连接失败\n";
			UpdateData(FALSE);
			//AfxMessageBox(inet_ntoa(serAddr.sin_addr));
		}
		else
		{
			UpdateData(TRUE);
			//AfxMessageBox("连接成功\n");
			CString temp;
			temp="#log Select user.* from [user] where clientid="+m_id+" and clientpwd='"+m_pwd+"'";
			char *sendData;
			sendData =(LPSTR)(LPCSTR)temp;//需要发送的信息
			send(sclient, sendData, strlen(sendData), 0);
			char recData[255];
			int ret = recv(sclient, recData, 255, 0);
			if(ret > 0)
			{
				recData[ret] = 0x00;
				if(!strcmp(recData,"success"))
				{
					char namearr[50];
					int len=recv(sclient, namearr, 255, 0);
					namearr[len]='\0';
					DENGLU dl;
					dl.m_name=namearr;
					dl.m_id=m_id;
					dl.m_ip=strIP;
					CDialog::OnOK();
					CString lpPath = _T(".\\peizhi.ini");
					::WritePrivateProfileString("denglu",_T("UserName"), namearr, lpPath);
					::WritePrivateProfileString("denglu",_T("UserId"), m_id, lpPath);
					::WritePrivateProfileString("denglu",_T("UserPassWord"), m_pwd, lpPath);
					::WritePrivateProfileString("denglu",_T("ServerIp"), strIP, lpPath);
					dl.DoModal();
				}
				m_Tip=recData;
				UpdateData(FALSE);
			}
			sendData ="";
			closesocket(sclient);//关闭一个套接口
			WSACleanup();//终止Winsock 2 DLL (Ws2_32.dll) 的使用
		}

	}
	else
	{
		m_Tip="账号或密码格式错误！";
		UpdateData(FALSE);
	}

}


void C局域网通信系统Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	ZHUCE zhuce;
	zhuce.m_ip=strIP;
	zhuce.DoModal();
}


void C局域网通信系统Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned  char  *pIP;
	DWORD  dwIP;
	UpdateData(TRUE);
	m_ServerIp.GetAddress(dwIP);//控件获取DWORD型IP
	pIP  =  (unsigned  char*)&dwIP;
	strIP.Format("%u.%u.%u.%u",*(pIP+3),  *(pIP+2),  *(pIP+1),  *pIP);//转换为IP格式
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
}
