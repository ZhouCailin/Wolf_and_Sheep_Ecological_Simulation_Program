
// newvisual.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CnewvisualApp:
// �йش����ʵ�֣������ newvisual.cpp
//

class CnewvisualApp : public CWinApp
{
public:
	CnewvisualApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CnewvisualApp theApp;