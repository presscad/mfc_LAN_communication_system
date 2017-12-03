
// ChatSeverDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatSever.h"
#include "ChatSeverDlg.h"
#include "afxdialogex.h"
#include "ListenerThread.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CChatSeverDlg �Ի���




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


// CChatSeverDlg ��Ϣ�������

BOOL CChatSeverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_UsersList.EnableWindow(false);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatSeverDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	if (m_cout<=0)//���Ե�ǰ��¼��,�ж��Ƿ�����ͬ�ʺŴ���
	{
		AfxMessageBox("�˺Ų����ڣ�");
	}
	else
	{
		m_Tip="Update [user] set clientpwd='"+m_pwd+"' where clientid="+m_id;//�����ж�ע���û�id
		p=(LPSTR)(LPCSTR)m_Tip;
		if(m_AdoConn.ExecuteSQL(p))
		{
			AfxMessageBox("�����޸ĳɹ���");
		}

	}
	m_AdoConn.ExitConnect();//�Ͽ����ݿ�����
	m_id="";
	m_pwd="";
	UpdateData(FALSE);
}
