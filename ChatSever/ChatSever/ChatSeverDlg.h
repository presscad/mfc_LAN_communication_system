
// ChatSeverDlg.h : 头文件
#include<iostream>
#include<fstream>
using namespace std;

#pragma once


// CChatSeverDlg 对话框
class CChatSeverDlg : public CDialogEx
{
// 构造
public:
	CChatSeverDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHATSEVER_DIALOG };

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
	ListenerThread* m_pListen;
	CListBox m_UsersList;
	afx_msg void OnBnClickedBegin();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedButton2();
	CString m_id;
	CString m_pwd;
};
