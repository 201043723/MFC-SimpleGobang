
// MyGobang_DHK.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyGobang_DHKApp:
// �йش����ʵ�֣������ MyGobang_DHK.cpp
//

class CMyGobang_DHKApp : public CWinApp
{
public:
	CMyGobang_DHKApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyGobang_DHKApp theApp;