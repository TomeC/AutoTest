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
    m_list_ctrl = (CListCtrl*)GetDlgItem(IDC_LIST3);

    LONG Styles = GetWindowLong(m_list_ctrl->m_hWnd, GWL_STYLE);
    SetWindowLong(m_list_ctrl->m_hWnd, GWL_STYLE, Styles | LVS_REPORT);
    m_list_ctrl->InsertColumn(0, "预期结果", LVCFMT_LEFT, 140);
    m_list_ctrl->InsertColumn(1, "返回结果", LVCFMT_LEFT, 400);
}

void CAutoTestResult::AddList(const char* data, int line, int colum)
{
    if (data == NULL)
    {
        return;
    }
    if (line > m_list_ctrl->GetItemCount())
    {
        line = m_list_ctrl->GetItemCount();
    }
    if (colum == 0)
    {
        m_list_ctrl->InsertItem(line, data);
    }
    else
    {
        m_list_ctrl->SetItemText(line, colum, data);
    }
}

void CAutoTestResult::ClearAllItem()
{
    m_list_ctrl->DeleteAllItems();
}

void CAutoTestResult::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAutoTestResult, CDialogEx)
END_MESSAGE_MAP()


// AutoTestResult 消息处理程序
