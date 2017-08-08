
// AutoTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoTest.h"
#include "AutoTestDlg.h"
#include "afxdialogex.h"
#include "conf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CAutoTestDlg �Ի���



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
//    ON_WM_MOUSEMOVE()
ON_WM_MOUSEMOVE()
//ON_WM_LBUTTONUP()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CAutoTestDlg ��Ϣ�������

BOOL CAutoTestDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

    SetIcon(m_hIcon, TRUE);            // ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);        // ����Сͼ��

    m_list_box = (CListBox*)GetDlgItem(IDC_LIST1);
    Conf cf;
    if (cf.LoadConf("server.conf") != 0)
    {
        AfxMessageBox("�������������ʧ��");
        return FALSE;
    }
    GetDlgItem(IDC_EDIT1)->SetWindowText(cf.getString("server", "port").c_str());
    GetDlgItem(IDC_IPADDRESS1)->SetWindowText(cf.getString("server", "ip").c_str());
    m_progress = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
    m_progress->SetRange(0, 1000);

    m_result_form = new CAutoTestResult();
    m_result_form->Create(IDD_DIALOG_Result, this);
    m_result_form->Init();

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

void CAutoTestDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // ʹͼ���ڹ����������о���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // ����ͼ��
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    BOOL isOpen = TRUE;
    CString filter = "�ļ� (*.txt; *.dat)|*.txt; *.dat||";
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
        AfxMessageBox("���ļ�ʧ��");
        return;
    }
    file.SeekToBegin();

    // ѭ����ȡ�ļ�
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

    //�ر�
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

    //�ر�
    aSocket.Close();
    return true;
}

// �ϼ�list�е�item
void CAutoTestDlg::OnLbnDblclkList1()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    int pos = m_list_box->GetCurSel();
    if (pos >= 0)
    {
        CString req_msg;
        m_list_box->GetText(pos, req_msg);
        GetMsgFromNet(req_msg);
    }
}

// ����ĳ��list�е�item
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

