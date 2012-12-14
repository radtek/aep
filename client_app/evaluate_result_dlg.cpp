// evaluate_result_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "evaluate_result_dlg.h"
#include "utility.h"

// CEvaluateResultDlg dialog

IMPLEMENT_DYNAMIC(CEvaluateResultDlg, CDialog)

CEvaluateResultDlg::CEvaluateResultDlg(const vector<AlgorithmRuntime> &algorithms,
                                       const vector<AlgorithmRuntimeResult> &algorithmResults,
                                       const vector<Factor> &factors,
                                       const vector<FactorResult> &factorResults,
                                       Engine *engine,
                                       CWnd* pParent)
	: CDialog(CEvaluateResultDlg::IDD, pParent)
    , m_Algorithms(algorithms)
    , m_AlgorithmResults(algorithmResults)
    , m_Factors(factors)
    , m_FactorResults(factorResults)
    , m_Engine(engine)
{

}

CEvaluateResultDlg::~CEvaluateResultDlg()
{
}

void CEvaluateResultDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ALGORITHM_RUNTIME_LIST, m_AlgorithmRuntimeList);
    DDX_Control(pDX, IDC_FACTOR_LIST, m_FactorList);
}


BEGIN_MESSAGE_MAP(CEvaluateResultDlg, CDialog)
    ON_NOTIFY(LVN_ITEMACTIVATE, IDC_FACTOR_LIST, &CEvaluateResultDlg::OnLvnItemActivateFactorList)
END_MESSAGE_MAP()


// CEvaluateResultDlg message handlers

BOOL CEvaluateResultDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

	LONG lStyle;
	lStyle = GetWindowLong(m_AlgorithmRuntimeList.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT;
	SetWindowLong(m_AlgorithmRuntimeList.m_hWnd, GWL_STYLE, lStyle);
	DWORD dwStyle = m_AlgorithmRuntimeList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_AlgorithmRuntimeList.SetExtendedStyle(dwStyle);
    
	m_AlgorithmRuntimeList.InsertColumn(0,_T("算法名称"),LVCFMT_CENTER, 50);
	m_AlgorithmRuntimeList.InsertColumn(1,_T("迭代次数"),LVCFMT_CENTER, 50);
	m_AlgorithmRuntimeList.InsertColumn(2,_T("CPU占用率"),LVCFMT_CENTER, 50);
	m_AlgorithmRuntimeList.InsertColumn(3,_T("内存使用"),LVCFMT_CENTER, 100);
	m_AlgorithmRuntimeList.InsertColumn(4,_T("运行时间"),LVCFMT_CENTER, 100);
	m_AlgorithmRuntimeList.EnableWindow(TRUE);

    for (UINT32 i = 0; i < m_Algorithms.size(); ++i)
    {
        AddAlgorithm(m_Algorithms[i], m_AlgorithmResults[i]);
    }

	lStyle = GetWindowLong(m_FactorList.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT;
	SetWindowLong(m_FactorList.m_hWnd, GWL_STYLE, lStyle);
	dwStyle = m_FactorList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_FactorList.SetExtendedStyle(dwStyle);
    
	m_FactorList.InsertColumn(0,_T("指标名称"),LVCFMT_CENTER, 60);

    for (UINT32 i = 0; i < m_Factors.size(); ++i)
    {
        AddFactor(m_Factors[i], m_FactorResults[i]);
    }

    return TRUE;
}

void CEvaluateResultDlg::AddAlgorithm(const AlgorithmRuntime &algorithm, const AlgorithmRuntimeResult &result)
{
    int n = m_AlgorithmRuntimeList.GetItemCount();
    m_AlgorithmRuntimeList.InsertItem(n, algorithm.Name.c_str());
    for (UINT32 i = 0; i < result.CpuPercentage.size(); ++i)
    {
        if (i > 0)
        {
            m_AlgorithmRuntimeList.InsertItem(n + i, TEXT(""));
        }

        CString temp;

        temp = TEXT("");
        temp.AppendFormat(TEXT("%u"), i + 1);
        m_AlgorithmRuntimeList.SetItemText(n + i, 1, temp);

        temp = TEXT("");
        temp.AppendFormat(TEXT("%u%%"), result.CpuPercentage[i]);
        m_AlgorithmRuntimeList.SetItemText(n + i, 2, temp);

        temp = TEXT("");
        temp.AppendFormat(TEXT("%u KB"), result.MemoryUsageKB[i]);
        m_AlgorithmRuntimeList.SetItemText(n + i, 3, temp);

        temp = TEXT("");
        temp.AppendFormat(TEXT("%llu NS"), result.NS[i]);
        m_AlgorithmRuntimeList.SetItemText(n + i, 4, temp);
    }
}

void CEvaluateResultDlg::AddFactor(const Factor &factor, const FactorResult &result)
{
    int n = m_FactorList.GetItemCount();
    m_FactorList.InsertItem(n, factor.Name.c_str());
}

void CEvaluateResultDlg::DrawFactor(const Factor &factor, const FactorResult &factorResult)
{
    mwSize size = factor.AlgorithmOutputEnd - factor.AlgorithmOutputStart + 1;
    Array *t = mxCreateDoubleMatrix(1, size, mxREAL);

    double *p = mxGetPr(t);
    for (UINT32 i = factor.AlgorithmOutputStart; i <= factor.AlgorithmOutputEnd; ++i)
    {
        p[i - factor.AlgorithmOutputStart] = i;
    }

    engPutVariable(m_Engine, "t", t);
    engPutVariable(m_Engine, "y", factorResult.Result);

    engEvalString(m_Engine, "plot(t, y);");
    engEvalString(m_Engine, "xlabel('t');");

    string cmd = "ylabel('" + Utility::Wstring2String(factor.Name) + "');";
    engEvalString(m_Engine, cmd.c_str());

    mxDestroyArray(t);
    // mxDestroyArray(factorResult.Result);
}

void CEvaluateResultDlg::OnLvnItemActivateFactorList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: Add your control notification handler code here
    if (pNMIA == NULL)
    {
        return;
    }

    const Factor &factor = m_Factors[pNMIA->iItem];
    const FactorResult &result = m_FactorResults[pNMIA->iItem];

    DrawFactor(factor, result);

    *pResult = 0;
}
