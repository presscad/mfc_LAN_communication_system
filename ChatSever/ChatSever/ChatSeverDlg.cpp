
// ChatSeverDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatSever.h"
#include "ChatSeverDlg.h"
#include "afxdialogex.h"
#include "ListenerThread.h"
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


// CChatSeverDlg 对话框




CChatSeverDlg::CChatSeverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatSeverDlg::IDD, pParent)
	, m_pListen(NULL)
	, m_id(_T(""))
	, m_pwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatSeverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Users, m_UsersList);
	//  DDX_Control(pDX, IDC_TIP, m_tip);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}

BEGIN_MESSAGE_MAP(CChatSeverDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BEGIN, &CChatSeverDlg::OnBnClickedBegin)
	ON_BN_CLICKED(IDC_STOP, &CChatSeverDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_SAVE, &CChatSeverDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CChatSeverDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CChatSeverDlg 消息处理程序

BOOL CChatSeverDlg::OnInitDialog()
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
	m_UsersList.EnableWindow(false);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatSeverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatSeverDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatSeverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}









void CChatSeverDlg::OnBnClickedBegin()
{
	m_pListen=(ListenerThread*)AfxBeginThread(RUNTIME_CLASS(ListenerThread));
	GetDlgItem(IDC_BEGIN)->EnableWindow(false);
	GetDlgItem(IDC_STOP)->EnableWindow(true);
}


void CChatSeverDlg::OnBnClickedStop()
{
	GetDlgItem(IDC_STOP)->EnableWindow(false);
	GetDlgItem(IDC_BEGIN)->EnableWindow(true);
	m_pListen->ExitInstance();
	TerminateThread(m_pListen->m_hThread,0);
	CloseHandle(m_pListen->m_hThread);
	m_pListen=NULL;
	

}


void CChatSeverDlg::OnBnClickedSave()
{
	CListBox *record=(CListBox *)GetDlgItem(IDC_LOG);
	char file[]="operate.log";
	ofstream out(file,std::ios::app);
	out<<"--------------------"<<endl;
	for(int i=0;i<record->GetCount();i++){
	CString s;
	record->GetText(i,s);
	out<<s<<endl;
	}
	out.close();
}




void CChatSeverDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString m_Tip;
	char* p;
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn ();
	_RecordsetPtr m_pRecordset;
	m_Tip="Select user.* from [user] where clientid="+m_id;
	p=(LPSTR)(LPCSTR)m_Tip;
	m_pRecordset=m_AdoConn.GetRecordSet (p);
	long m_cout=m_pRecordset->GetRecordCount();
	if (m_cout<=0)//测试当前记录号,判断是否有相同帐号存在
	{
		AfxMessageBox("账号不存在！");
	}
	else
	{
		m_Tip="Update [user] set clientpwd='"+m_pwd+"' where clientid="+m_id;//发送判断注册用户id
		p=(LPSTR)(LPCSTR)m_Tip;
		if(m_AdoConn.ExecuteSQL(p))
		{
			AfxMessageBox("密码修改成功！");
		}

	}
	m_AdoConn.ExitConnect();//断开数据库连接
	m_id="";
	m_pwd="";
	UpdateData(FALSE);
}
