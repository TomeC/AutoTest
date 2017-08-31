#include "stdafx.h"
#include "Net.h"

UINT CTimeOutSocket::m_TimeOut = 3000;
CTimeOutSocket::~CTimeOutSocket()
{
}

BOOL CTimeOutSocket::OnMessagePending()
{
    MSG msg;
    if (::PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_NOREMOVE))
    {
        if (msg.wParam == (UINT)m_nTimerID)
        {
            ::PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_REMOVE);
            CancelBlockingCall();
            return FALSE;
        };
    };
    return CSocket::OnMessagePending();
}

int CTimeOutSocket::Receive(void* lpBuf, int nBufLen, int nFlags)
{
    //m_nTimerID = m_dlg->SetTimer(1, m_TimeOut, NULL);
    //m_nTimerID = SetTimer(NULL, 1234, 3000, NULL);
    int nRecv = CSocket::Receive(lpBuf, nBufLen, nFlags);
    //KillTimer(NULL, m_nTimerID);
    //m_dlg->KillTimer(1);
    
    return nRecv;
}

int CTimeOutSocket::Send(const void* lpBuf, int nBufLen, int nFlags)
{
    //m_nTimerID = m_dlg->SetTimer(1, m_TimeOut, NULL);
    int nSend = CSocket::Send(lpBuf, nBufLen, nFlags);
    //m_dlg->KillTimer(1);
    return nSend;
}
