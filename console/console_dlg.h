#pragma once
#include "Resource.h"

#include "model_ctrl.h"
#include "model.h"
#include "afxwin.h"
#include "afxcmn.h"

// CConsoleDlg dialog

class __declspec(dllexport) CConsoleDlg : public CDialog
{
	DECLARE_DYNAMIC(CConsoleDlg)

public:
	CConsoleDlg(Model &model, CWnd* pParent = NULL);   // standard constructor
	virtual ~CConsoleDlg();

// Dialog Data
	enum { IDD = IDD_CONSOLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
    UINT32 m_CurrentAlgorithmId;
    HANDLE m_CurrentThreadHandle;

    bool m_Paused;

public:
    void OnRunThreadEnd();
    void OnStepThreadEnd();
    void OnBatchThreadEnd();

public:
    CModelCtrl m_ModelCtrl;
    Model &m_Model;
    CButton m_RunButton;
    CButton m_StepButton;
    CButton m_ResetButton;
    CButton m_PauseButton;
    CProgressCtrl m_Progress;

    afx_msg void OnBnClickedRunButton();
    afx_msg void OnBnClickedStepButton();
    afx_msg void OnBnClickedResetButton();
    afx_msg void OnBnClickedPauseButton();
    CButton m_BatchButton;
    afx_msg void OnBnClickedBatchButton();
};

void __declspec(dllexport) ShowConsoleDlg(Model &model);
