
// ������ͨ��ϵͳDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include"ZHUCE.h"
#include"DENGLU.h"
#include "afxwin.h"

// C������ͨ��ϵͳDlg �Ի���
class C������ͨ��ϵͳDlg : public CDialogEx
{
// ����
public:
	C������ͨ��ϵͳDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	CIPAddressCtrl m_ServerIp;
	CString m_Tip;
	afx_msg void OnBnClickedButton2();
	CString  strIP;
	afx_msg void OnBnClickedButton3();
	CString m_id;
	CString m_pwd;
	CStatic m_tx;
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
