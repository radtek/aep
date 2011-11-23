#pragma once


// CRegisterPage dialog

class CRegisterPage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CRegisterPage)

public:
	CRegisterPage();
	virtual ~CRegisterPage();

// Dialog Data
	enum { IDD = IDD_REGISTER_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
