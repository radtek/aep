// file_insert.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cfile_insertApp:
// �йش����ʵ�֣������ file_insert.cpp
//

class Cfile_insertApp : public CWinApp
{
public:
	Cfile_insertApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cfile_insertApp theApp;