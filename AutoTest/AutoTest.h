
// AutoTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
    #error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"        // ������


// CAutoTestApp: 
// �йش����ʵ�֣������ AutoTest.cpp
//

class CAutoTestApp : public CWinApp
{
public:
    CAutoTestApp();

// ��д
public:
    virtual BOOL InitInstance();

// ʵ��

    DECLARE_MESSAGE_MAP()
};

extern CAutoTestApp theApp;