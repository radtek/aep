#pragma once
#include "afxwin.h"

#include "tcp_socket.h"
#include "evaluate.h"
#include "engine.h"

// CEvaluateShowDlg dialog

class CEvaluateShowDlg : public CDialog
{
	DECLARE_DYNAMIC(CEvaluateShowDlg)

public:
	CEvaluateShowDlg(const vector<AlgorithmRuntime> &algorithms,
        const vector<Factor> &factors,
        const vector<ImageMonitor> &imageMonitors,
        Engine *engine,
        CWnd* pParent = NULL);   // standard constructor
	virtual ~CEvaluateShowDlg();

// Dialog Data
	enum { IDD = IDD_EVALUTE_SHOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    const vector<AlgorithmRuntime> &m_Algorithms;
    const vector<Factor> &m_Factors;
    const vector<ImageMonitor> &m_ImageMonitors;

	DECLARE_MESSAGE_MAP()

protected:
    TcpSocket m_Socket;
    int m_Port;

    Evaluate &m_Evaluate;
    Engine *m_Engine;

    RC Listen();
    virtual RC RealListen();
    static DWORD WINAPI ThreadListen(LPVOID lparam);

    HANDLE m_Handle;

    HBITMAP m_Bmp[4];

public:
    BOOL OnInitDialog();
	afx_msg LRESULT OnUpdateAll(WPARAM wParam, LPARAM lParam);

    CString m_Time;
    CString m_Cpu;
    CString m_Memory;
    CString m_Ns;
    CStatic m_Img0;
    CStatic m_Img1;
    CStatic m_Img2;
    CStatic m_Img3;

    CStatic *m_Img[4];
    enum
    {
        WM_UPDATE_ALL = WM_USER + 1,
    };
    CString m_ImageMonitorTitle0;
    CString m_ImageMonitorTitle1;
    CString m_ImageMonitorTitle2;
    CString m_ImageMonitorTitle3;

    CString *m_ImageMonitorTitle[4];

    CString m_Param0;
    CString m_Param1;
    CString m_Param2;
    CString m_Param3;
    CString m_Param4;
    CString m_Param5;
    CString m_Param6;
    CString m_Param7;
    CString m_Param8;
    CString m_Param9;

    CString *m_Param[10];
};
