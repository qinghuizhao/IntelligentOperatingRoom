
// beijinghand.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CbeijinghandApp:
// �йش����ʵ�֣������ beijinghand.cpp
//

class CbeijinghandApp : public CWinApp
{
public:
	CbeijinghandApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CbeijinghandApp theApp;