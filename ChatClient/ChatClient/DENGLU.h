#pragma once
#include "Accept.h"
#include "afxwin.h"

// DENGLU �Ի���

class DENGLU : public CDialogEx
{
	DECLARE_DYNAMIC(DENGLU)

public:
	DENGLU(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DENGLU();

// �Ի�������
	enum { IDD = IDD_DENGLU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_id;
	CString m_ip;
	afx_msg void OnBnClickedButton1();
	Accept* acp;
//	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CString m_send;
	CString m_rev;
	CEdit m_crev;
	afx_msg void OnClose();
	void tongxin(CString cmd);
	CStatic m_tx;
//	afx_msg void OnChangeEdit2();
//	afx_msg void OnUpdateEdit2();
	afx_msg void OnBnClickedButton2();
};
