
// AutoTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoTest.h"
#include "AutoTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	AfxSocketInit();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAutoTestDlg 对话框



CAutoTestDlg::CAutoTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTOTEST_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CAutoTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAutoTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAutoTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoTestDlg::OnBnClickedButton1)
	ON_LBN_DBLCLK(IDC_LIST1, &CAutoTestDlg::OnLbnDblclkList1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CAutoTestDlg::OnLbnSclkList1)
//	ON_WM_MOUSEMOVE()
ON_WM_MOUSEMOVE()
//ON_WM_LBUTTONUP()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CAutoTestDlg 消息处理程序

BOOL CAutoTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_list_box = (CListBox*)GetDlgItem(IDC_LIST1);
	GetDlgItem(IDC_EDIT1)->SetWindowText("19900");
	GetDlgItem(IDC_IPADDRESS1)->SetWindowText("10.100.120.71");
	m_progress = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
	m_progress->SetRange(0, 1000);

	m_result_form = new CAutoTestResult();
	m_result_form->Create(IDD_DIALOG_Result, this);
	m_result_form->Init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAutoTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAutoTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAutoTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAutoTestDlg::OnBnClickedOk()
{
	GetMsgFromNet();
}

void CAutoTestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL isOpen = TRUE;
	CString filter = "文件 (*.txt; *.dat)|*.txt; *.dat||";
	CFileDialog openFileDlg(isOpen, NULL, NULL, OFN_HIDEREADONLY | OFN_READONLY, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath;
	if (result != IDOK) 
	{
		return;
	}
	filePath = openFileDlg.GetPathName();
	CStdioFile file;
	BOOL ret = file.Open(filePath, CFile::modeRead | CFile::shareDenyNone);
	if (!ret)
	{
		AfxMessageBox("打开文件失败");
		return;
	}
	file.SeekToBegin();

	// 循环读取文件
	CString cstrLine;
	while (file.ReadString(cstrLine))
	{
		m_list_box->InsertString(m_list_box->GetCount(), cstrLine);
	}
	m_progress->SetStep(1000 / m_list_box->GetCount());
}

bool CAutoTestDlg::GetMsgFromNet()
{
	CSocket aSocket;
	CString strIP;
	CString strPort;
	CString strText;
	GetDlgItem(IDC_IPADDRESS1)->GetWindowTextA(strIP);
	GetDlgItem(IDC_EDIT1)->GetWindowTextA(strPort);

	if (!aSocket.Create())
	{
		MessageBox("create failed");
		return false;
	}

	int nPort;
	sscanf_s(strPort, "%d", &nPort);
	if (aSocket.Connect(strIP, nPort))
	{
		char szRecValue[1024];
		for (int i = 0; i < m_list_box->GetCount(); ++i)
		{
			memset(szRecValue, 0, sizeof(szRecValue));
			m_list_box->GetText(i, strText);
			if (strText.GetLength() == 0 || strText[0] == '#')
			{
				continue;
			}
			aSocket.Send(strText.GetBuffer(strText.GetLength()), strText.GetLength());
			aSocket.Receive((void *)szRecValue, 1024);
			int nLen = MultiByteToWideChar(CP_UTF8, 0, szRecValue, -1, NULL, 0);
			WCHAR* pWstr = new WCHAR[nLen + 1];
			ZeroMemory(pWstr, sizeof(WCHAR) * (nLen + 1));
			::MultiByteToWideChar(CP_UTF8, 0, szRecValue, -1, pWstr, nLen);
			std::string strAnsi(_bstr_t((wchar_t*)pWstr));
			delete[] pWstr;
			m_result_form->AddList(strAnsi.c_str());
			m_progress->StepIt();
		}
	}
	else
	{
		MessageBox("connect failed");
	}

	//关闭
	aSocket.Close();
	m_progress->SetPos(0);

	m_result_form->ShowWindow(SW_SHOW);
	return true;
}

bool CAutoTestDlg::GetMsgFromNet(CString& req_msg)
{
	if (req_msg.GetLength() == 0 || req_msg[0] == '#')
	{
		return true;
	}
	CSocket aSocket;
	CString strIP;
	CString strPort;
	GetDlgItem(IDC_IPADDRESS1)->GetWindowTextA(strIP);
	GetDlgItem(IDC_EDIT1)->GetWindowTextA(strPort);

	if (!aSocket.Create())
	{
		MessageBox("create failed");
		return false;
	}

	int nPort;
	sscanf_s(strPort, "%d", &nPort);
	if (aSocket.Connect(strIP, nPort))
	{
		char szRecValue[1024];

		memset(szRecValue, 0, sizeof(szRecValue));
		aSocket.Send(req_msg.GetBuffer(req_msg.GetLength()), req_msg.GetLength());
		aSocket.Receive((void *)szRecValue, 1024);
		int nLen = MultiByteToWideChar(CP_UTF8, 0, szRecValue, -1, NULL, 0);
		WCHAR* pWstr = new WCHAR[nLen + 1];
		ZeroMemory(pWstr, sizeof(WCHAR) * (nLen + 1));
		::MultiByteToWideChar(CP_UTF8, 0, szRecValue, -1, pWstr, nLen);
		std::string strAnsi(_bstr_t((wchar_t*)pWstr));
		delete[] pWstr;

		MessageBox(strAnsi.c_str());
	}
	else
	{
		MessageBox("connect failed");
	}

	//关闭
	aSocket.Close();
	return true;
}

// 上级list中的item
void CAutoTestDlg::OnLbnDblclkList1()
{
	// TODO: 在此添加控件通知处理程序代码
	int pos = m_list_box->GetCurSel();
	if (pos >= 0)
	{
		CString req_msg;
		m_list_box->GetText(pos, req_msg);
		GetMsgFromNet(req_msg);
	}
}

// 单击某个list中的item
void CAutoTestDlg::OnLbnSclkList1()
{
	int pos = m_list_box->GetCurSel();
	if (pos >= 0)
	{
		CString content;
		m_list_box->GetText(pos, content);
		GetDlgItem(IDC_EDIT2)->SetWindowTextA(content);
	}
}

