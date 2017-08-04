
// AutoTestDlg.h : ͷ�ļ�
//

#pragma once

#include <string>
#include "AutoTestResult.h"

// CAutoTestDlg �Ի���
class CAutoTestDlg : public CDialogEx
{
// ����
public:
	CAutoTestDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CAutoTestDlg()
	{
		delete m_result_form;
	}

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
