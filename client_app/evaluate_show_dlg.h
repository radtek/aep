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
        Engine *engine,
        CWnd* pParent = NULL);   // standard constructor
	virtual ~CEvaluateShowDlg();

// Dialog Data
	enum { IDD = IDD_EVALUTE_SHOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    const vector<AlgorithmRuntime> &m_Algorithms;
    const vector<Factor> &m_Factors;

	DECLARE_MESSAGE_MAP()

protected:
    TcpSocket m_Socket;
    int m_Port;

    Evaluate &m_Evaluate;
    Engine *m_Engine;

    RC Listen();
    RC RealListen();
    static DWORD WINAPI ThreadListen(LPVOID lparam);

    HANDLE m_Handle;

    HBITMAP m_OrigBmp[2];
    HBITMAP m_OutputBmp[2];

public:
    BOOL OnInitDialog();
	afx_msg LRESULT OnUpdateAll(WPARAM wParam, LPARAM lParam);

    CString m_Time;
    CString m_Cpu;
    CString m_Memory;
    CString m_Ns;
    CStatic m_Img00;
    CStatic m_Img01;
    CStatic m_Img10;
    CStatic m_Img11;

    CStatic *m_OrigImg[2];
    CStatic *m_OutputImg[2];
    enum
    {
        WM_UPDATE_ALL = WM_USER + 1,
    };
};
