#include "run_model_thread.h"

#include "utility.h"

RunModelThread::RunModelThread(CConsoleDlg &dlg, Model &model, UINT32 startId)
: m_ConsoleDlg(dlg)
, m_Model(model)
, m_StartId(startId)
{
}

HANDLE RunModelThread::Start()
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

void RunModelThread::Run()
{
    m_ConsoleDlg.m_Progress.SetRange32(m_StartId, m_Model.GetAlgorithmCount());
    m_ConsoleDlg.m_Progress.SetPos(m_StartId);

    for (UINT32 i = m_StartId; i < m_Model.GetAlgorithmCount(); ++i)
    {
        m_ConsoleDlg.m_ModelCtrl.SetRunItem(i);

        RC rc;
        CHECK_RC_MSG_VOID(m_Model.RunSingleAlgorithm(i));

        m_ConsoleDlg.m_Progress.SetPos(i + 1);
    }
}

void RunModelThread::Stop()
{
    m_ConsoleDlg.OnRunThreadEnd();
}

DWORD WINAPI RunModelThread::Run(LPVOID lparam)
{
    RunModelThread *runModelThread = (RunModelThread *)lparam;
    if (!runModelThread)
    {
        return -1;
    }

    runModelThread->Run();

    runModelThread->Stop();

    delete runModelThread;

    return 0;
}
