
// ChatSeverDlg.h : ͷ�ļ�
#include<iostream>
#include<fstream>
using namespace std;

#pragma once


// CChatSeverDlg �Ի���
class CChatSeverDlg : public CDialogEx
{
// ����
public:
	CChatSeverDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATSEVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	ListenerThread* m_pListen;
	CListBox m_UsersList;
	afx_msg void OnBnClickedBegin();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedButton2();
	CString m_id;
	CString m_pwd;
};
