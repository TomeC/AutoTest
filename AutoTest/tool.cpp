#include "stdafx.h"
#include "tool.h"

vector<CString> CTool::split_msg(const CString& msg)
{
    vector<CString> vResult;
    CString temp = msg;
    if (msg.GetLength() == 0)
    {
        return vResult;
    }
    temp.Trim();
    int pos = msg.Find('#');
    if (pos == -1)
    {
        vResult.push_back(temp);
        vResult.push_back(CString(""));
    }
    else
    {
        vResult.push_back(temp.Left(pos));
        vResult.push_back(temp.Right(temp.GetLength() - pos - 1));
    }
    
    return vResult;
}
