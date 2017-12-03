
// ������ͨ��ϵͳDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "afxdialogex.h"

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


// C������ͨ��ϵͳDlg �Ի���




C������ͨ��ϵͳDlg::C������ͨ��ϵͳDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C������ͨ��ϵͳDlg::IDD, pParent)
	, m_Tip(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_id = _T("");
	m_pwd = _T("");
}

void C������ͨ��ϵͳDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ServerIp, m_ServerIp);
	DDX_Text(pDX, IDC_TIP, m_Tip);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
	DDX_Control(pDX, IDC_TX, m_tx);
}

BEGIN_MESSAGE_MAP(C������ͨ��ϵͳDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C������ͨ��ϵͳDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C������ͨ��ϵͳDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C������ͨ��ϵͳDlg::OnBnClickedButton3)
//	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// C������ͨ��ϵͳDlg ��Ϣ�������

BOOL C������ͨ��ϵͳDlg::OnInitDialog()
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
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C������ͨ��ϵͳDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C������ͨ��ϵͳDlg::OnPaint()
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
	// ��ʾ��Դ�е�ͼ�񣨽���λͼBMP��
	hBitmap =(HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);  
	m_tx.SetBitmap(hBitmap);
	
}
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C������ͨ��ϵͳDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C������ͨ��ϵͳDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_id.GetLength()==5 && m_pwd.GetLength()==6)
	{
		//��ʼ��WSA
		WORD sockVersion= MAKEWORD(2,2);
		WSADATA data;
		if(WSAStartup(sockVersion, &data) != 0)
		{
			AfxMessageBox("ʧ��!");
		
		}
		//�����׽���
		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(sclient == INVALID_SOCKET)
		{
			AfxMessageBox("��Ч�� socket !");
		}

		//��IP�Ͷ˿�
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(8888);
		serAddr.sin_addr.S_un.S_addr = inet_addr(strIP);
		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{
			//AfxMessageBox("����ʧ��\n");
			m_Tip="����ʧ��\n";
			UpdateData(FALSE);
			//AfxMessageBox(inet_ntoa(serAddr.sin_addr));
		}
		else
		{
			UpdateData(TRUE);
			//AfxMessageBox("���ӳɹ�\n");
			CString temp;
			temp="#log Select user.* from [user] where clientid="+m_id+" and clientpwd='"+m_pwd+"'";
			char *sendData;
			sendData =(LPSTR)(LPCSTR)temp;//��Ҫ���͵���Ϣ
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
			closesocket(sclient);//�ر�һ���׽ӿ�
			WSACleanup();//��ֹWinsock 2 DLL (Ws2_32.dll) ��ʹ��
		}

	}
	else
	{
		m_Tip="�˺Ż������ʽ����";
		UpdateData(FALSE);
	}

}


void C������ͨ��ϵͳDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ZHUCE zhuce;
	zhuce.m_ip=strIP;
	zhuce.DoModal();
}


void C������ͨ��ϵͳDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned  char  *pIP;
	DWORD  dwIP;
	UpdateData(TRUE);
	m_ServerIp.GetAddress(dwIP);//�ؼ���ȡDWORD��IP
	pIP  =  (unsigned  char*)&dwIP;
	strIP.Format("%u.%u.%u.%u",*(pIP+3),  *(pIP+2),  *(pIP+1),  *pIP);//ת��ΪIP��ʽ
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
}
