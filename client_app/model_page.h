#pragma once

#include "client.h"

// CModelPage dialog

class CModelPage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CModelPage)

public:
	CModelPage();   // standard constructor
	virtual ~CModelPage();

// Dialog Data
	enum { IDD = IDD_MODEL_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedTransfer();

private:
    Client &m_Client;
    afx_msg void OnBnClickedModel();
};
