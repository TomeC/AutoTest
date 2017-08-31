#pragma once
#include "afxsock.h"
#include "AutoTestDlg.h"

class CTimeOutSocket :public CSocket
{
public:
    CTimeOutSocket(CAutoTestDlg* dlg):m_dlg(dlg) { }
    ~CTimeOutSocket();

public:
    virtual BOOL OnMessagePending();
    virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
    virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
private:
    BOOL KillTimeOut();
    BOOL SetTimeOut(int nTimeOut);

private:
    UINT_PTR m_nTimerID;
    CAutoTestDlg* m_dlg;

public:
    static UINT m_TimeOut;
};
