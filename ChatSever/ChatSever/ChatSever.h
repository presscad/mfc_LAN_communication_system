
// ChatSever.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//
#include "ListenerThread.h"
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChatSeverApp:
// �йش����ʵ�֣������ ChatSever.cpp
//

class CChatSeverApp : public CWinApp
{
public:
	CChatSeverApp();

// ��д
public:
	virtual BOOL InitInstance();
	 
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChatSeverApp theApp;