// console_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "console.h"
#include "console_dlg.h"

#include "utility.h"
#include "massert.h"

#include "run_model_thread.h"
#include "step_model_thread.h"
#include "batch_model_thread.h"

// CConsoleDlg dialog

IMPLEMENT_DYNAMIC(CConsoleDlg, CDialog)

CConsoleDlg::CConsoleDlg(Model &model, CWnd* pParent /*=NULL*/)
	: CDialog(CConsoleDlg::IDD, pParent)
    , m_Model(model)
    , m_ModelCtrl(model)
    , m_CurrentAlgorithmId(0)
    , m_Paused(false)
    , m_CurrentThreadHandle(NULL)
{

}

CConsoleDlg::~CConsoleDlg()
{
}

void CConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MODEL_CTRL, m_ModelCtrl);
    DDX_Control(pDX, IDC_RUN_BUTTON, m_RunButton);
    DDX_Control(pDX, IDC_PAUSE_BUTTON, m_PauseButton);
    DDX_Control(pDX, IDC_STEP_BUTTON, m_StepButton);
    DDX_Control(pDX, IDC_PROGRESS, m_Progress);
    DDX_Control(pDX, IDC_RESET_BUTTON, m_ResetButton);
    DDX_Control(pDX, IDC_BATCH_BUTTON, m_BatchButton);
}

BOOL CConsoleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
    CRect rect;
    m_ModelCtrl.GetClientRect(&rect);
    m_ModelCtrl.Init(rect);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CConsoleDlg, CDialog)
    ON_BN_CLICKED(IDC_RUN_BUTTON, &CConsoleDlg::OnBnClickedRunButton)
    ON_BN_CLICKED(IDC_STEP_BUTTON, &CConsoleDlg::OnBnClickedStepButton)
    ON_BN_CLICKED(IDC_RESET_BUTTON, &CConsoleDlg::OnBnClickedResetButton)
    ON_BN_CLICKED(IDC_PAUSE_BUTTON, &CConsoleDlg::OnBnClickedPauseButton)
    ON_BN_CLICKED(IDC_BATCH_BUTTON, &CConsoleDlg::OnBnClickedBatchButton)
END_MESSAGE_MAP()

// CConsoleDlg message handlers

void __declspec(dllexport) ShowConsoleDlg(Model &model)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CConsoleDlg dlg(model);
    dlg.DoModal();
}

void CConsoleDlg::OnRunThreadEnd()
{
    m_CurrentAlgorithmId = 0;
    m_ModelCtrl.UnSetAllRunItem(true);

    m_CurrentThreadHandle = NULL;

    m_RunButton.EnableWindow(true);
    m_StepButton.EnableWindow(true);
    m_ResetButton.EnableWindow(true);
    m_BatchButton.EnableWindow(true);
}

void CConsoleDlg::OnStepThreadEnd()
{
    ++m_CurrentAlgorithmId;
    m_ModelCtrl.UnSetAllRunItem(true);

    m_CurrentThreadHandle = NULL;

    m_RunButton.EnableWindow(true);
    m_StepButton.EnableWindow(true);
    m_ResetButton.EnableWindow(true);
    m_BatchButton.EnableWindow(true);
}

void CConsoleDlg::OnBatchThreadEnd()
{
    m_ModelCtrl.UnSetAllRunItem(true);

    m_CurrentThreadHandle = NULL;

    m_RunButton.EnableWindow(true);
    m_StepButton.EnableWindow(true);
    m_ResetButton.EnableWindow(true);
    m_BatchButton.EnableWindow(true);
}

void CConsoleDlg::OnBnClickedRunButton()
{
    // TODO: Add your control notification handler code here
    m_RunButton.EnableWindow(false);
    m_StepButton.EnableWindow(false);
    m_ResetButton.EnableWindow(false);
    m_BatchButton.EnableWindow(false);

    if (m_CurrentAlgorithmId == m_Model.GetAlgorithmCount())
    {
        m_CurrentAlgorithmId = 0;
    }

    RunModelThread *runModelThread = new RunModelThread(*this, m_Model, m_CurrentAlgorithmId);

    m_CurrentThreadHandle = runModelThread->Start();
    if (!m_CurrentThreadHandle)
    {
        delete runModelThread;
        Utility::PromptErrorMessage(TEXT("模型运行线程启动失败."));
    }
}

void CConsoleDlg::OnBnClickedStepButton()
{
    // TODO: Add your control notification handler code here
    m_RunButton.EnableWindow(false);
    m_StepButton.EnableWindow(false);
    m_ResetButton.EnableWindow(false);
    m_BatchButton.EnableWindow(false);

    if (m_CurrentAlgorithmId == m_Model.GetAlgorithmCount())
    {
        m_CurrentAlgorithmId = 0;
    }

    StepModelThread *stepModelThread = new StepModelThread(*this, m_Model, m_CurrentAlgorithmId);

    m_CurrentThreadHandle = stepModelThread->Start();
    if (!m_CurrentThreadHandle)
    {
        delete stepModelThread;
        Utility::PromptErrorMessage(TEXT("模型单步线程启动失败."));
    }
}

void CConsoleDlg::OnBnClickedResetButton()
{
    // TODO: Add your control notification handler code here
    m_CurrentAlgorithmId = 0;
    m_Progress.SetRange32(0, 0);
    m_Progress.SetPos(0);
    m_Model.Reset();
}

void CConsoleDlg::OnBnClickedPauseButton()
{
    // TODO: Add your control notification handler code here
    if (m_Paused)
    {
        MASSERT(m_CurrentThreadHandle);
        ResumeThread(m_CurrentThreadHandle);
        m_Paused = false;
        m_PauseButton.SetWindowTextW(TEXT("暂停"));
    }
    else
    {
        if (!m_CurrentThreadHandle)
        {
            return;
        }
        SuspendThread(m_CurrentThreadHandle);
        m_Paused = true;
        m_PauseButton.SetWindowTextW(TEXT("继续"));
    }
}

void CConsoleDlg::OnBnClickedBatchButton()
{
    // TODO: Add your control notification handler code here
    wstring batchFile;
    CFileDialog dlg(TRUE, TEXT("batch"), TEXT("Untitiled.batch"), 0, TEXT("Batch Files (*.batch)|*.batch|All Files (*.*)|*.*||"));
    if(dlg.DoModal() == IDOK)
    {
        batchFile = dlg.GetPathName();
    }
    else
    {
        return;
    }

    m_RunButton.EnableWindow(false);
    m_StepButton.EnableWindow(false);
    m_ResetButton.EnableWindow(false);
    m_BatchButton.EnableWindow(false);

    BatchModelThread *batchModelThread = new BatchModelThread(*this, m_Model, batchFile);

    m_CurrentThreadHandle = batchModelThread->Start();
    if (!m_CurrentThreadHandle)
    {
        delete batchModelThread;
        Utility::PromptErrorMessage(TEXT("模型运行线程启动失败."));
    }
}
