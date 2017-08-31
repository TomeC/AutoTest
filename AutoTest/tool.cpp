#include "stdafx.h"
#include "tool.h"

vector<CString> CTool::split_msg(CString& msg)
{
    vector<CString> vResult;
    if (msg.GetLength() == 0)
    {
        return vResult;
    }
    int pos = msg.Find('#');
    if (pos == -1)
    {
        msg.Trim();
        vResult.push_back(msg);
        vResult.push_back(CString(""));
    }
    else
    {
        vResult.push_back(msg.Left(pos).Trim());
        vResult.push_back(msg.Right(msg.GetLength() - pos - 1).Trim());
    }
    
    return vResult;
}
