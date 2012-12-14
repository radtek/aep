#pragma once

#include "evaluate.h"
#include "afxcmn.h"

#include <engine.h>

// CEvaluateResultDlg dialog

class CEvaluateResultDlg : public CDialog
{
	DECLARE_DYNAMIC(CEvaluateResultDlg)

public:
	CEvaluateResultDlg(const vector<AlgorithmRuntime> &algorithms,
        const vector<AlgorithmRuntimeResult> &algorithmResults,
        const vector<Factor> &factors,
        const vector<FactorResult> &factorResults,
        Engine *engine,
        CWnd* pParent = NULL);   // standard constructor
	virtual ~CEvaluateResultDlg();

// Dialog Data
	enum { IDD = IDD_EVALUTE_RESULT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    const vector<AlgorithmRuntime> &m_Algorithms;
    const vector<AlgorithmRuntimeResult> &m_AlgorithmResults;
    const vector<Factor> &m_Factors;
    const vector<FactorResult> &m_FactorResults;

    Engine *m_Engine;

	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_AlgorithmRuntimeList;
    CListCtrl m_FactorList;

    BOOL OnInitDialog();
    void AddAlgorithm(const AlgorithmRuntime &algorithm, const AlgorithmRuntimeResult &result);
    void AddFactor(const Factor &factor, const FactorResult &result);

    void DrawFactor(const Factor &factor, const FactorResult &factorResult);
    afx_msg void OnLvnItemActivateFactorList(NMHDR *pNMHDR, LRESULT *pResult);
};
