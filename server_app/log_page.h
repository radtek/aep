#pragma once

#include "server.h"
#include "logger.h"

// CLogPage dialog

class CLogPage : public CBCGPPropertyPage,
    public Logger
{
	DECLARE_DYNAMIC(CLogPage)

public:
	CLogPage();
	virtual ~CLogPage();

// Dialog Data
	enum { IDD = IDD_LOG_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedLogControl();

protected:
    bool m_IsLogging;
    void StartLog();
    void StopLog();
public:
    CButton m_LogControlButton;
public:
    CEdit m_LogEdit;
public:
    afx_msg void OnBnClickedLogClear();
public:
    virtual void Log(LPCWSTR msg);
private:
    Server &m_Server;
};
