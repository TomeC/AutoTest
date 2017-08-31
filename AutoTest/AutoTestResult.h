#pragma once


// AutoTestResult 对话框

class CAutoTestResult : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoTestResult)

public:
	CAutoTestResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoTestResult();

	void Init();
	void AddList(const char* data, int line, int colum);
    void ClearAllItem();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Result };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CListCtrl* m_list_ctrl;
};
