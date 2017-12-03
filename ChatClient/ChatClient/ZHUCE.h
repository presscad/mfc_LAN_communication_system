#pragma once

// ZHUCE 对话框

class ZHUCE : public CDialogEx
{
	DECLARE_DYNAMIC(ZHUCE)

public:
	ZHUCE(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ZHUCE();

// 对话框数据
	enum { IDD = IDD_ZHUCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	CString m_ip;
	CString m_Tip;
	CString m_name;
	CString m_id;
	CString m_pwd;
	CString m_rpwd;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeName();
//	char * tongxin(void);
	char * tongxin(char * sqlcmd);
	afx_msg void OnBnClickedButton5();
	bool hefa(void);
};
