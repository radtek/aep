#pragma once
#include "afxcmn.h"

#include "evaluate.h"
#include "afxwin.h"

// CEvaluatePage dialog

class CEvaluatePage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CEvaluatePage)

public:
	CEvaluatePage();   // standard constructor
	virtual ~CEvaluatePage();

// Dialog Data
	enum { IDD = IDD_EVALUATE_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    CString m_AlgorithmName;
    CString m_AlgorithmFile;
    afx_msg void OnBnClickedAlgorithmAddUpdate();
    afx_msg void OnBnClickedAlgorithmDelete();
    CListCtrl m_AlgorithmListCtrl;

private:
    void AddAlgorithmItem();
    void UpdateAlgorithmItem(int row);
    void DeleteAlgorithmItem(int row);
    void AddFactorItem();
    void UpdateFactorItem(int row);
    void DeleteFactorItem(int row);
    Evaluate &m_Evaluate;
public:
    afx_msg void OnLvnItemActivateAlgorithmList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedOk();
    CString m_FactorName;
    CString m_DllPath;
    CString m_AlgorithmOutput;
    UINT m_AlgorithmOutputStart;
    UINT m_AlgorithmOutputEnd;
    CString m_Origin;
    UINT m_OriginStart;
    UINT m_OriginEnd;
    CListCtrl m_FactorListCtrl;
    afx_msg void OnBnClickedFactorAddUpdate();
    afx_msg void OnBnClickedFactorDelete();
    afx_msg void OnLvnItemActivateFactorList(NMHDR *pNMHDR, LRESULT *pResult);
};
