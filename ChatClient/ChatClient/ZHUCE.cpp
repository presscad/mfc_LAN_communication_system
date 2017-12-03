// ZHUCE.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ZHUCE.h"
#include "afxdialogex.h"

// ZHUCE �Ի���

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


// ZHUCE ��Ϣ�������


void ZHUCE::OnBnClickedButton3()
{
	UpdateData(TRUE);
	bool id=true;
	bool id1=true;
	bool name=true;
	bool pwd=true;//����Ϊ6
	bool rpwd=true;//�����Ƿ�һ��
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
		
		m_Tip="#que Select user.* from [user] where clientid="+m_id;//�����ж�ע���û�id
		char* p=(LPSTR)(LPCSTR)m_Tip;
		if(strcmp(tongxin(p),"success"))
		{
			m_Tip="#reg INSERT INTO [user] (clientid,clientpwd,clientname) VALUES ("+m_id+",'" +m_pwd + "','" + m_name +"')"; //  ִ��INSERT���	
			p=(LPSTR)(LPCSTR)m_Tip;
			if(!strcmp(tongxin(p),"success"))
			{
				AfxMessageBox("ע��ɹ�");
				CDialog::OnCancel();
			}
		}
		else
		{
			m_Tip="�˺��Ѵ��ڣ�";
			UpdateData(FALSE);
		}
	}
	else
	{
		if(!id)
		{
			m_Tip=m_Tip+"�û�id��ʽ�����������������!\n";
			m_id="";
		}
		if(!name)
		{
			m_Tip=m_Tip+"�û��������������������!\n";
			m_name="";
		}
		if(!pwd)
		{
			m_Tip=m_Tip+"�û������ʽ�����������������!\n";
			m_pwd="";
			m_rpwd="";
		}
		if(!rpwd)
		{
			m_Tip=m_Tip+"�û��������벻һ�£�����������!\n";
			m_rpwd="";
			m_pwd="";
		}
		UpdateData(FALSE);
	}
	
}


void ZHUCE::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void ZHUCE::OnEnChangeName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}



char * ZHUCE::tongxin(char * sqlcmd)
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
	serAddr.sin_addr.S_un.S_addr = inet_addr(m_ip);
	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		//AfxMessageBox("����ʧ��\n");
		m_Tip="����ʧ��\n";
		UpdateData(FALSE);
		//AfxMessageBox(inet_ntoa(serAddr.sin_addr));
	}
	else
	{
		//AfxMessageBox("���ӳɹ�\n");
		char *sendData;
		sendData =sqlcmd;//��Ҫ���͵���Ϣ
		send(sclient, sendData, strlen(sendData), 0);
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if(ret > 0)
		{
			recData[ret] = 0x00;
			m_Tip=recData;
			UpdateData(FALSE);
		}
		closesocket(sclient);//�ر�һ���׽ӿ�
		WSACleanup();//��ֹWinsock 2 DLL (Ws2_32.dll) ��ʹ��
		return recData;
	}

}


void ZHUCE::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(hefa())
	{
		m_Tip="#out delete from [user] where clientid="+m_id+" and clientname='" + m_name +"'"+" and clientpwd='" + m_pwd +"'"; //  ִ��DElete���	
		char *p=(LPSTR)(LPCSTR)m_Tip;
		if(!strcmp(tongxin(p),"success"))
		{
			AfxMessageBox("���ųɹ�");
			CDialog::OnCancel();
		}
		else
		{
			AfxMessageBox("����ʧ��");
		}
	}
}


bool ZHUCE::hefa(void)
{
	UpdateData(TRUE);
	bool id=true;
	bool id1=true;
	bool name=true;
	bool pwd=true;//����Ϊ6
	bool rpwd=true;//�����Ƿ�һ��
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
