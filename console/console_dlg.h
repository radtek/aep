#pragma once
#include "Resource.h"

#include "model_ctrl.h"

#include "model.h"

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

	DECLARE_MESSAGE_MAP()
public:
    CModelCtrl m_ModelCtrl;
    Model &m_Model;
};

void __declspec(dllexport) ShowConsoleDlg(Model &model);
