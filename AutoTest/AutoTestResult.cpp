// AutoTestResult.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoTest.h"
#include "AutoTestResult.h"
#include "afxdialogex.h"


// AutoTestResult 对话框

IMPLEMENT_DYNAMIC(CAutoTestResult, CDialogEx)

CAutoTestResult::CAutoTestResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Result, pParent)
{

}

CAutoTestResult::~CAutoTestResult()
{
}

void CAutoTestResult::Init()
{
	m_list_box = (CListBox*)GetDlgItem(IDC_LIST1);
}

void CAutoTestResult::AddList(const char* data)
{
	m_list_box->InsertString(m_list_box->GetCount(), data);
}

void CAutoTestResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoTestResult, CDialogEx)
END_MESSAGE_MAP()


// AutoTestResult 消息处理程序
