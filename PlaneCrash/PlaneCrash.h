
// PlaneCrash.h : PlaneCrash Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CPlaneCrashApp:
// �йش����ʵ�֣������ PlaneCrash.cpp
//

class CPlaneCrashApp : public CWinAppEx
{
public:
	CPlaneCrashApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPlaneCrashApp theApp;
