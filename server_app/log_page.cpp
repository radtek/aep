// log_page.cpp : implementation file
//

#include "stdafx.h"
#include "server_app.h"
#include "log_page.h"


// CLogPage dialog

IMPLEMENT_DYNAMIC(CLogPage, CBCGPPropertyPage)

CLogPage::CLogPage()
	: CBCGPPropertyPage(CLogPage::IDD)
    , m_Server(Server::GetInstance())
{
}

CLogPage::~CLogPage()
{
}

void CLogPage::DoDataExchange(CDataExchange* pDX)
{
    CBCGPPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDB_LOG_CONTROL, m_LogControlButton);
    DDX_Control(pDX, IDC_LOG, m_LogEdit);
}


BEGIN_MESSAGE_MAP(CLogPage, CBCGPPropertyPage)
    ON_BN_CLICKED(IDB_LOG_CONTROL, &CLogPage::OnBnClickedLogControl)
    ON_BN_CLICKED(IDC_LOG_CLEAR, &CLogPage::OnBnClickedLogClear)
END_MESSAGE_MAP()


// CLogPage message handlers

BOOL CLogPage::OnInitDialog() 
{
    CBCGPPropertyPage::OnInitDialog();

    m_LogEdit.SetReadOnly();

    StartLog();
    m_Server.SetLogger(this);

    return TRUE;
}

void CLogPage::OnBnClickedLogControl()
{
    // TODO: Add your control notification handler code here
    if (m_IsLogging)
    {
        StopLog();
    }
    else
    {
        StartLog();
    }
}

void CLogPage::StartLog()
{
    m_LogControlButton.SetWindowTextW(TEXT("Í£Ö¹"));
    m_IsLogging = true;
}

void CLogPage::StopLog()
{
    m_LogControlButton.SetWindowTextW(TEXT("¿ªÊ¼"));
    m_IsLogging = false;
}

void CLogPage::OnBnClickedLogClear()
{
    // TODO: Add your control notification handler code here
    m_LogEdit.SetWindowTextW(TEXT(""));
}

void CLogPage::Log(LPCWSTR msg)
{
    if (!m_IsLogging)
    {
        return;
    }

    CString oldMsg;
    m_LogEdit.GetWindowTextW(oldMsg);
    CString newMsg = oldMsg + msg + TEXT("\r\n");

    m_LogEdit.SetRedraw(FALSE);
    m_LogEdit.SetWindowTextW(newMsg);
    int line = m_LogEdit.GetLineCount();
    m_LogEdit.LineScroll(line, 0);
    int count = newMsg.GetLength();
    m_LogEdit.SetSel(count, count);
    m_LogEdit.SetRedraw(TRUE);
}
