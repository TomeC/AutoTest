#pragma once


// AutoTestResult �Ի���

class CAutoTestResult : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoTestResult)

public:
	CAutoTestResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutoTestResult();

	void Init();
	void AddList(const char* data);

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Result };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CListBox* m_list_box;
};