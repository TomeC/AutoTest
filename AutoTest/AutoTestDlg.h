
// AutoTestDlg.h : 头文件
//

#pragma once

#include <string>
#include "AutoTestResult.h"

// CAutoTestDlg 对话框
class CAutoTestDlg : public CDialogEx
{
// 构造
public:
	CAutoTestDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CAutoTestDlg()
	{
		delete m_result_form;
	}

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();

private:
	bool GetMsgFromNet();
	bool GetMsgFromNet(CString& req_msg);

private:
	CListBox* m_list_box;
	CProgressCtrl* m_progress;
	CAutoTestResult* m_result_form;

public:
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnLbnSclkList1();
};
