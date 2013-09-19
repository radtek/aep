// evaluate_page.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "evaluate_page.h"
#include "utility.h"

#include "evaluate_result_dlg.h"
#include "evaluate_show_dlg.h"

#include <fstream>
#include <iostream>

using namespace std;

// CEvaluatePage dialog

IMPLEMENT_DYNAMIC(CEvaluatePage, CBCGPPropertyPage)

CEvaluatePage::CEvaluatePage()
	: CBCGPPropertyPage(CEvaluatePage::IDD)
    , m_AlgorithmName(_T(""))
    , m_AlgorithmFile(_T(""))
    , m_Evaluate(Evaluate::GetInstance())
    , m_FactorName(_T(""))
    , m_DllPath(_T(""))
    , m_AlgorithmOutputStart(0)
    , m_AlgorithmOutputEnd(0)
    , m_OriginEnd(0)
    , m_OriginStart(0)
    , m_Origin(_T(""))
    , m_TrueValue(_T(""))
    , m_WindowCenter(_T(""))
    , m_ImageMonitorPath(_T(""))
    , m_ImageMonitorStart(0)
    , m_ImageMonitorEnd(0)
    , m_ImageMonitorTitle(_T(""))
{

}

CEvaluatePage::~CEvaluatePage()
{
}

void CEvaluatePage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ALGORITHM_NAME, m_AlgorithmName);
    DDX_Text(pDX, IDC_ALGORITHM_FILE_PATH, m_AlgorithmFile);
    DDX_Control(pDX, IDC_ALGORITHM_LIST, m_AlgorithmListCtrl);
    DDX_Text(pDX, IDC_FACTOR_NAME, m_FactorName);
    DDX_Text(pDX, IDC_FACTOR_DLL_PATH, m_DllPath);
    DDX_Text(pDX, IDC_FACTOR_ALGORITHM_OUTPUT, m_AlgorithmOutput);
    DDX_Text(pDX, IDC_FACTOR_ALGORITHM_OUTPUT_START, m_AlgorithmOutputStart);
    DDX_Text(pDX, IDC_FACTOR_ALGORITHM_OUTPUT_END, m_AlgorithmOutputEnd);
    DDX_Text(pDX, IDC_FACTOR_ORIGIN, m_Origin);
    DDX_Text(pDX, IDC_FACTOR_ORIGIN_END, m_OriginEnd);
    DDX_Text(pDX, IDC_FACTOR_ORIGIN_START, m_OriginStart);
    DDX_Control(pDX, IDC_FACTOR_LIST, m_FactorListCtrl);
    DDX_Text(pDX, IDC_FACTOR_TRUE_VALUE, m_TrueValue);
    DDX_Text(pDX, IDC_FACTOR_WINDOW_CENTER, m_WindowCenter);
    DDX_Text(pDX, IDC_IMG_PATH, m_ImageMonitorPath);
    DDX_Text(pDX, IDC_IMG_START, m_ImageMonitorStart);
    DDX_Text(pDX, IDC_IMG_END, m_ImageMonitorEnd);
    DDX_Control(pDX, IDC_IMG_LIST, m_ImageMonitorListCtrl);
    DDX_Text(pDX, IDC_IMG_TITLE, m_ImageMonitorTitle);
}


BEGIN_MESSAGE_MAP(CEvaluatePage, CBCGPPropertyPage)
    ON_BN_CLICKED(IDC_ALGORITHM_ADD_UPDATE, &CEvaluatePage::OnBnClickedAlgorithmAddUpdate)
    ON_BN_CLICKED(IDC_ALGORITHM_DELETE, &CEvaluatePage::OnBnClickedAlgorithmDelete)
    ON_NOTIFY(LVN_ITEMACTIVATE, IDC_ALGORITHM_LIST, &CEvaluatePage::OnLvnItemActivateAlgorithmList)
    ON_BN_CLICKED(IDOK, &CEvaluatePage::OnBnClickedOk)
    ON_BN_CLICKED(IDC_FACTOR_ADD_UPDATE, &CEvaluatePage::OnBnClickedFactorAddUpdate)
    ON_BN_CLICKED(IDC_FACTOR_DELETE, &CEvaluatePage::OnBnClickedFactorDelete)
    ON_NOTIFY(LVN_ITEMACTIVATE, IDC_FACTOR_LIST, &CEvaluatePage::OnLvnItemActivateFactorList)
    ON_BN_CLICKED(IDC_LOAD, &CEvaluatePage::OnBnClickedLoad)
    ON_BN_CLICKED(IDC_SAVE, &CEvaluatePage::OnBnClickedSave)
    ON_BN_CLICKED(IDC_IMG_ADD_UPDATE, &CEvaluatePage::OnBnClickedImgAddUpdate)
    ON_BN_CLICKED(IDC_IMG_DELETE, &CEvaluatePage::OnBnClickedImgDelete)
END_MESSAGE_MAP()


// CEvaluatePage message handlers

BOOL CEvaluatePage::OnInitDialog() 
{
    CBCGPPropertyPage::OnInitDialog();

    if (!(m_Engine = engOpen(NULL)))
    {
        Utility::PromptErrorMessage(TEXT("Matlab��ͼ�����ʼ��ʧ��."));
        return FALSE;
    }

	LONG lStyle;
	lStyle = GetWindowLong(m_AlgorithmListCtrl.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT;
	SetWindowLong(m_AlgorithmListCtrl.m_hWnd, GWL_STYLE, lStyle);
	DWORD dwStyle = m_AlgorithmListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_AlgorithmListCtrl.SetExtendedStyle(dwStyle);
    
	m_AlgorithmListCtrl.InsertColumn(0,_T("�㷨����"),LVCFMT_CENTER, 60);
	m_AlgorithmListCtrl.InsertColumn(1,_T("�ļ�·��"),LVCFMT_CENTER, 60);
	m_AlgorithmListCtrl.EnableWindow(TRUE);

	lStyle = GetWindowLong(m_FactorListCtrl.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT;
	SetWindowLong(m_FactorListCtrl.m_hWnd, GWL_STYLE, lStyle);
	dwStyle = m_FactorListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_FactorListCtrl.SetExtendedStyle(dwStyle);
    
	m_FactorListCtrl.InsertColumn(0,_T("ָ������"),LVCFMT_CENTER, 60);
	m_FactorListCtrl.InsertColumn(1,_T("DLL·��"),LVCFMT_CENTER, 60);
	m_FactorListCtrl.InsertColumn(2,_T("�㷨���"),LVCFMT_CENTER, 60);
	m_FactorListCtrl.InsertColumn(3,_T("��ʼID"),LVCFMT_CENTER, 60);
	m_FactorListCtrl.InsertColumn(4,_T("����ID"),LVCFMT_CENTER, 60);
	m_FactorListCtrl.InsertColumn(5,_T("ԭʼ�ļ�"),LVCFMT_CENTER, 60);
	m_FactorListCtrl.InsertColumn(6,_T("��ʼID"),LVCFMT_CENTER, 60);
	m_FactorListCtrl.InsertColumn(7,_T("����ID"),LVCFMT_CENTER, 60);
	m_FactorListCtrl.InsertColumn(8,_T("��ʵֵ"),LVCFMT_CENTER, 60);
	m_FactorListCtrl.InsertColumn(9,_T("��������"),LVCFMT_CENTER, 60);
	m_FactorListCtrl.EnableWindow(TRUE);

    lStyle = GetWindowLong(m_ImageMonitorListCtrl.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT;
	SetWindowLong(m_ImageMonitorListCtrl.m_hWnd, GWL_STYLE, lStyle);
	dwStyle = m_ImageMonitorListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_ImageMonitorListCtrl.SetExtendedStyle(dwStyle);
    
	m_ImageMonitorListCtrl.InsertColumn(0,_T("���ͼ��·��"),LVCFMT_CENTER, 60);
	m_ImageMonitorListCtrl.InsertColumn(1,_T("��ʼID"),LVCFMT_CENTER, 60);
	m_ImageMonitorListCtrl.InsertColumn(2,_T("����ID"),LVCFMT_CENTER, 60);
    m_ImageMonitorListCtrl.InsertColumn(3,_T("����"),LVCFMT_CENTER, 60);
	m_ImageMonitorListCtrl.EnableWindow(TRUE);

    return TRUE;
}

void CEvaluatePage::AddAlgorithmItem()
{
    if (m_AlgorithmName == TEXT("") || m_AlgorithmFile == TEXT(""))
    {
        return;
    }
    int n = m_AlgorithmListCtrl.GetItemCount();
    m_AlgorithmListCtrl.InsertItem(n, m_AlgorithmName);
    m_AlgorithmListCtrl.SetItemText(n, 1, m_AlgorithmFile);
}

void CEvaluatePage::UpdateAlgorithmItem(int row)
{
    if (m_AlgorithmName == TEXT("") || m_AlgorithmFile == TEXT(""))
    {
        return;
    }
    m_AlgorithmListCtrl.SetItemText(row, 0, m_AlgorithmName);
    m_AlgorithmListCtrl.SetItemText(row, 1, m_AlgorithmFile);
}

void CEvaluatePage::DeleteAlgorithmItem(int row)
{
    m_AlgorithmListCtrl.DeleteItem(row);
}

void CEvaluatePage::AddFactorItem()
{
    if (m_FactorName == TEXT("")
        || m_DllPath == TEXT("")
        || m_AlgorithmOutput == TEXT("")
        || m_Origin == TEXT(""))
    {
        return;
    }
    int n = m_FactorListCtrl.GetItemCount();
    m_FactorListCtrl.InsertItem(n, m_FactorName);
    CString temp;
    m_FactorListCtrl.SetItemText(n, 1, m_DllPath);
    m_FactorListCtrl.SetItemText(n, 2, m_AlgorithmOutput);
    temp = TEXT("");
    temp.AppendFormat(TEXT("%u"), m_AlgorithmOutputStart);
    m_FactorListCtrl.SetItemText(n, 3, temp);
    temp = TEXT("");
    temp.AppendFormat(TEXT("%u"), m_AlgorithmOutputEnd);
    m_FactorListCtrl.SetItemText(n, 4, temp);
    m_FactorListCtrl.SetItemText(n, 5, m_Origin);
    temp = TEXT("");
    temp.AppendFormat(TEXT("%u"), m_OriginStart);
    m_FactorListCtrl.SetItemText(n, 6, temp);
    temp = TEXT("");
    temp.AppendFormat(TEXT("%u"), m_OriginEnd);
    m_FactorListCtrl.SetItemText(n, 7, temp);
    m_FactorListCtrl.SetItemText(n, 8, m_TrueValue);
    m_FactorListCtrl.SetItemText(n, 9, m_WindowCenter);
}

void CEvaluatePage::UpdateFactorItem(int row)
{
    if (m_FactorName == TEXT("")
        || m_DllPath == TEXT("")
        || m_AlgorithmOutput == TEXT("")
        || m_Origin == TEXT(""))
    {
        return;
    }
    CString temp;
    m_FactorListCtrl.SetItemText(row, 0, m_FactorName);
    m_FactorListCtrl.SetItemText(row, 1, m_DllPath);
    m_FactorListCtrl.SetItemText(row, 2, m_AlgorithmOutput);
    temp = TEXT("");
    temp.AppendFormat(TEXT("%u"), m_AlgorithmOutputStart);
    m_FactorListCtrl.SetItemText(row, 3, temp);
    temp = TEXT("");
    temp.AppendFormat(TEXT("%u"), m_AlgorithmOutputEnd);
    m_FactorListCtrl.SetItemText(row, 4, temp);
    m_FactorListCtrl.SetItemText(row, 5, m_Origin);
    temp = TEXT("");
    temp.AppendFormat(TEXT("%u"), m_OriginStart);
    m_FactorListCtrl.SetItemText(row, 6, temp);
    temp = TEXT("");
    temp.AppendFormat(TEXT("%u"), m_OriginEnd);
    m_FactorListCtrl.SetItemText(row, 7, temp);
    m_FactorListCtrl.SetItemText(row, 8, m_TrueValue);
    m_FactorListCtrl.SetItemText(row, 9, m_WindowCenter);
}

void CEvaluatePage::DeleteFactorItem(int row)
{
    m_FactorListCtrl.DeleteItem(row);
}

void CEvaluatePage::AddImageMonitorItem()
{
    if (m_ImageMonitorPath == TEXT(""))
    {
        return;
    }
    int n = m_ImageMonitorListCtrl.GetItemCount();
    m_ImageMonitorListCtrl.InsertItem(n, m_ImageMonitorPath);
    CString temp;
    temp.AppendFormat(TEXT("%u"), m_ImageMonitorStart);
    m_ImageMonitorListCtrl.SetItemText(n, 1, temp);
    temp = TEXT("");
    temp.AppendFormat(TEXT("%u"), m_ImageMonitorEnd);
    m_ImageMonitorListCtrl.SetItemText(n, 2, temp);
    m_ImageMonitorListCtrl.SetItemText(n, 3, m_ImageMonitorTitle);
}

void CEvaluatePage::UpdateImageMonitorItem(int row)
{
    if (m_ImageMonitorPath == TEXT(""))
    {
        return;
    }
    CString temp;
    m_ImageMonitorListCtrl.SetItemText(row, 0, m_ImageMonitorPath);
    temp = TEXT("");
    temp.AppendFormat(TEXT("%u"), m_ImageMonitorStart);
    m_ImageMonitorListCtrl.SetItemText(row, 1, temp);
    temp = TEXT("");
    temp.AppendFormat(TEXT("%u"), m_ImageMonitorEnd);
    m_ImageMonitorListCtrl.SetItemText(row, 2, temp);
    m_ImageMonitorListCtrl.SetItemText(row, 3, m_ImageMonitorTitle);
}

void CEvaluatePage::DeleteImageMonitorItem(int row)
{
    m_ImageMonitorListCtrl.DeleteItem(row);
}

void CEvaluatePage::OnBnClickedAlgorithmAddUpdate()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    POSITION pos = m_AlgorithmListCtrl.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        AddAlgorithmItem();
    }
    else
    {
        int row = (int)m_AlgorithmListCtrl.GetNextSelectedItem(pos);
        UpdateAlgorithmItem(row);
    }
}

void CEvaluatePage::OnBnClickedAlgorithmDelete()
{
    // TODO: Add your control notification handler code here
    POSITION pos = m_AlgorithmListCtrl.GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        int row = (int)m_AlgorithmListCtrl.GetNextSelectedItem(pos);
        DeleteAlgorithmItem(row);
    }
}

void CEvaluatePage::OnLvnItemActivateAlgorithmList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    if (pNMIA == NULL)
    {
        return;
    }
    // TODO: Add your control notification handler code here
    m_AlgorithmName = m_AlgorithmListCtrl.GetItemText(pNMIA->iItem, 0);
    m_AlgorithmFile = m_AlgorithmListCtrl.GetItemText(pNMIA->iItem, 1);
    UpdateData(0);
    *pResult = 0;
}

void CEvaluatePage::OnBnClickedFactorAddUpdate()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    POSITION pos = m_FactorListCtrl.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        AddFactorItem();
    }
    else
    {
        int row = (int)m_FactorListCtrl.GetNextSelectedItem(pos);
        UpdateFactorItem(row);
    }
}

void CEvaluatePage::OnBnClickedFactorDelete()
{
    // TODO: Add your control notification handler code here
    POSITION pos = m_FactorListCtrl.GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        int row = (int)m_FactorListCtrl.GetNextSelectedItem(pos);
        DeleteFactorItem(row);
    }
}

void CEvaluatePage::OnLvnItemActivateFactorList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    if (pNMIA == NULL)
    {
        return;
    }
    // TODO: Add your control notification handler code here
    m_FactorName = m_FactorListCtrl.GetItemText(pNMIA->iItem, 0);
    m_DllPath = m_FactorListCtrl.GetItemText(pNMIA->iItem, 1);
    m_AlgorithmOutput = m_FactorListCtrl.GetItemText(pNMIA->iItem, 2);
    m_AlgorithmOutputStart = _ttoi(m_FactorListCtrl.GetItemText(pNMIA->iItem, 3));
    m_AlgorithmOutputEnd = _ttoi(m_FactorListCtrl.GetItemText(pNMIA->iItem, 4));
    m_Origin = m_FactorListCtrl.GetItemText(pNMIA->iItem, 5);
    m_OriginStart = _ttoi(m_FactorListCtrl.GetItemText(pNMIA->iItem, 6));
    m_OriginEnd = _ttoi(m_FactorListCtrl.GetItemText(pNMIA->iItem, 7));
    m_TrueValue = m_FactorListCtrl.GetItemText(pNMIA->iItem, 8);
    m_WindowCenter = m_FactorListCtrl.GetItemText(pNMIA->iItem, 9);
    UpdateData(0);
    *pResult = 0;
}

void CEvaluatePage::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    vector<AlgorithmRuntime> algorithms;
    for (int i = 0; i < m_AlgorithmListCtrl.GetItemCount(); ++i)
    {
        AlgorithmRuntime algorithm;
        algorithm.Name = m_AlgorithmListCtrl.GetItemText(i, 0);
        algorithm.FilePath = m_AlgorithmListCtrl.GetItemText(i, 1);
        algorithms.push_back(algorithm);
    }
    vector<Factor> factors;
    for (int i = 0; i < m_FactorListCtrl.GetItemCount(); ++i)
    {
        Factor factor;
        factor.Name = m_FactorListCtrl.GetItemText(i, 0);
        factor.DllPath = m_FactorListCtrl.GetItemText(i, 1);
        factor.AlgorithmOutput = m_FactorListCtrl.GetItemText(i, 2);
        factor.AlgorithmOutputStart = _ttoi(m_FactorListCtrl.GetItemText(i, 3));
        factor.AlgorithmOutputEnd = _ttoi(m_FactorListCtrl.GetItemText(i, 4));
        factor.Origin = m_FactorListCtrl.GetItemText(i, 5);
        factor.OriginStart = _ttoi(m_FactorListCtrl.GetItemText(i, 6));
        factor.OriginEnd = _ttoi(m_FactorListCtrl.GetItemText(i, 7));
        factor.TrueValue = m_FactorListCtrl.GetItemText(i, 8);
        factor.WindowCenter = m_FactorListCtrl.GetItemText(i, 9);
        factors.push_back(factor);
    }
    vector<ImageMonitor> imageMonitors;
    for (int i = 0; i < m_ImageMonitorListCtrl.GetItemCount(); ++i)
    {
        ImageMonitor imageMonitor;
        imageMonitor.Path = m_ImageMonitorListCtrl.GetItemText(i, 0);
        imageMonitor.Start = _ttoi(m_ImageMonitorListCtrl.GetItemText(i, 1));
        imageMonitor.End = _ttoi(m_ImageMonitorListCtrl.GetItemText(i, 2));
        imageMonitor.Title = m_ImageMonitorListCtrl.GetItemText(i, 3);
        imageMonitors.push_back(imageMonitor);
    }

    CEvaluateShowDlg dlg(algorithms, factors, imageMonitors, m_Engine);
    dlg.DoModal();

#if 0
    vector<AlgorithmRuntimeResult> algorithmResults;
    vector<FactorResult> factorResults;

    if (OK != m_Evaluate.DoEvaluate(algorithms, factors, algorithmResults, factorResults))
    {
        Utility::PromptErrorMessage(TEXT("��������."));
    }

    CEvaluateResultDlg dlg(algorithms, algorithmResults, factors, factorResults, m_Engine);
    dlg.DoModal();

    for (UINT32 i = 0; i < factorResults.size(); ++i)
    {
        mxDestroyArray(factorResults[i].Result);
    }
#endif
}

void CEvaluatePage::OnBnClickedLoad()
{
    // TODO: Add your control notification handler code here
    CFileDialog dlg(TRUE, NULL, NULL, OFN_NOCHANGEDIR | OFN_FILEMUSTEXIST, TEXT("Evaluate Files (*.eva)|*.eva|All Files (*.*)|*.*||"));
    INT_PTR ret = dlg.DoModal();
    if (IDOK == ret)
    {
        CString filePath = dlg.GetPathName();
        wifstream ifs(filePath);
        ifs.imbue(locale("chs"));
        if (!ifs)
        {
            Utility::PromptErrorMessage(TEXT("���ļ�ʧ��."));
            return;
        }
        m_AlgorithmListCtrl.DeleteAllItems();
        m_FactorListCtrl.DeleteAllItems();
        int n = 0;
        ifs >> n;
        for (int i = 0; i < n; ++i)
        {
            wstring name, file;
            ifs >> name >> file;
            m_AlgorithmListCtrl.InsertItem(i, name.c_str());
            m_AlgorithmListCtrl.SetItemText(i, 1, file.c_str());
        }

        ifs >> n;
        for (int i = 0; i < n; ++i)
        {
            wstring name, path, output, outputStart, outputEnd, origin, originStart, originEnd, trueValue, windowCenter;
            ifs >> name >> path >> output >> outputStart >> outputEnd >> origin >> originStart >> originEnd >> trueValue >> windowCenter;
            m_FactorListCtrl.InsertItem(i, name.c_str());
            m_FactorListCtrl.SetItemText(i, 1, path.c_str());
            m_FactorListCtrl.SetItemText(i, 2, output.c_str());
            m_FactorListCtrl.SetItemText(i, 3, outputStart.c_str());
            m_FactorListCtrl.SetItemText(i, 4, outputEnd.c_str());
            m_FactorListCtrl.SetItemText(i, 5, origin.c_str());
            m_FactorListCtrl.SetItemText(i, 6, originStart.c_str());
            m_FactorListCtrl.SetItemText(i, 7, originEnd.c_str());
            m_FactorListCtrl.SetItemText(i, 8, trueValue.c_str());
            m_FactorListCtrl.SetItemText(i, 9, windowCenter.c_str());
        }

#if 0
        ifs >> n;
        for (int i = 0; i < n; ++i)
        {
            wstring path, start, end, title;
            ifs >> path >> start >> end >> title;
            m_ImageMonitorListCtrl.InsertItem(i, path.c_str());
            m_ImageMonitorListCtrl.SetItemText(i, 1, start.c_str());
            m_ImageMonitorListCtrl.SetItemText(i, 2, end.c_str());
            m_ImageMonitorListCtrl.SetItemText(i, 3, title.c_str());
        }
#endif
    }
    else
    {
        return;
    }
}

void CEvaluatePage::OnBnClickedSave()
{
    // TODO: Add your control notification handler code here
    CFileDialog dlg(FALSE, NULL, NULL, OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT, TEXT("Evaluate Files (*.eva)|*.eva|All Files (*.*)|*.*||"));
    INT_PTR ret = dlg.DoModal();
    if (IDOK == ret)
    {
        CString filePath = dlg.GetPathName();
        wofstream ofs(filePath);
        ofs.imbue(locale("chs"));
        if (!ofs)
        {
            Utility::PromptErrorMessage(TEXT("���ļ�ʧ��."));
        }
        ofs << m_AlgorithmListCtrl.GetItemCount() << endl;
        for (int i = 0; i < m_AlgorithmListCtrl.GetItemCount(); ++i)
        {
            ofs << wstring(m_AlgorithmListCtrl.GetItemText(i, 0)) << TEXT(" ");
            ofs << wstring(m_AlgorithmListCtrl.GetItemText(i, 1)) << endl;
        }
        ofs << endl;
        ofs << m_FactorListCtrl.GetItemCount() << endl;
        for (int i = 0; i < m_FactorListCtrl.GetItemCount(); ++i)
        {
            ofs << wstring(m_FactorListCtrl.GetItemText(i, 0)) << TEXT(" ");
            ofs << wstring(m_FactorListCtrl.GetItemText(i, 1)) << TEXT(" ");
            ofs << wstring(m_FactorListCtrl.GetItemText(i, 2)) << TEXT(" ");
            ofs << wstring(m_FactorListCtrl.GetItemText(i, 3)) << TEXT(" ");
            ofs << wstring(m_FactorListCtrl.GetItemText(i, 4)) << TEXT(" ");
            ofs << wstring(m_FactorListCtrl.GetItemText(i, 5)) << TEXT(" ");
            ofs << wstring(m_FactorListCtrl.GetItemText(i, 6)) << TEXT(" ");
            ofs << wstring(m_FactorListCtrl.GetItemText(i, 7)) << TEXT(" ");
            ofs << wstring(m_FactorListCtrl.GetItemText(i, 8)) << TEXT(" ");
            ofs << wstring(m_FactorListCtrl.GetItemText(i, 9)) << endl;
        }
        ofs << endl;
        ofs << m_ImageMonitorListCtrl.GetItemCount() << endl;
        for (int i = 0; i < m_ImageMonitorListCtrl.GetItemCount(); ++i)
        {
            ofs << wstring(m_ImageMonitorListCtrl.GetItemText(i, 0)) << TEXT(" ");
            ofs << wstring(m_ImageMonitorListCtrl.GetItemText(i, 1)) << TEXT(" ");
            ofs << wstring(m_ImageMonitorListCtrl.GetItemText(i, 2)) << TEXT(" ");
            ofs << wstring(m_ImageMonitorListCtrl.GetItemText(i, 3)) << endl;
        }
        ofs.close();
    }
    else
    {
        return;
    }
}

void CEvaluatePage::OnBnClickedImgAddUpdate()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData();
    POSITION pos = m_ImageMonitorListCtrl.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        AddImageMonitorItem();
    }
    else
    {
        int row = (int)m_ImageMonitorListCtrl.GetNextSelectedItem(pos);
        UpdateImageMonitorItem(row);
    }
}

void CEvaluatePage::OnBnClickedImgDelete()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    POSITION pos = m_ImageMonitorListCtrl.GetFirstSelectedItemPosition();
    if (pos != NULL)
    {
        int row = (int)m_ImageMonitorListCtrl.GetNextSelectedItem(pos);
        DeleteImageMonitorItem(row);
    }
}
