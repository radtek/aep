#include "step_model_thread.h"

#include "utility.h"

StepModelThread::StepModelThread(CConsoleDlg &dlg, Model &model, UINT32 algorithmId)
: m_ConsoleDlg(dlg)
, m_Model(model)
, m_AlgorithmId(algorithmId)
{
}

HANDLE StepModelThread::Start()
{
    HANDLE handle;
    handle = CreateThread(NULL,
        NULL,
        Run,
        (LPVOID)this,
        0,
        0);
    return handle;
}

void StepModelThread::Run()
{
    m_ConsoleDlg.m_Progress.SetRange32(m_AlgorithmId, m_AlgorithmId + 1);
    m_ConsoleDlg.m_Progress.SetPos(m_AlgorithmId);

    m_ConsoleDlg.m_ModelCtrl.SetRunItem(m_AlgorithmId);

    RC rc;
    CHECK_RC_MSG_VOID(m_Model.RunSingleAlgorithm(m_AlgorithmId));

    m_ConsoleDlg.m_Progress.SetPos(m_AlgorithmId + 1);
}

void StepModelThread::Stop()
{
    m_ConsoleDlg.OnStepThreadEnd();
}

DWORD WINAPI StepModelThread::Run(LPVOID lparam)
{
    StepModelThread *stepModelThread = (StepModelThread *)lparam;
    if (!stepModelThread)
    {
        return -1;
    }

    stepModelThread->Run();

    stepModelThread->Stop();

    delete stepModelThread;

    return 0;
}
