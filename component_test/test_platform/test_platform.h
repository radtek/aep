// test_platform.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestPlatformApp:
// �йش����ʵ�֣������ test_platform.cpp
//

class CTestPlatformApp : public CWinApp
{
public:
	CTestPlatformApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestPlatformApp theApp;