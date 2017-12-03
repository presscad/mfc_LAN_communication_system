
// 局域网通信系统Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include"ZHUCE.h"
#include"DENGLU.h"
#include "afxwin.h"

// C局域网通信系统Dlg 对话框
class C局域网通信系统Dlg : public CDialogEx
{
// 构造
public:
	C局域网通信系统Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
