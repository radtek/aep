#include "batch_model_thread.h"

#include "utility.h"

BatchModelThread::BatchModelThread(CConsoleDlg &dlg, Model2 &model, const wstring &batchFile)
: m_ConsoleDlg(dlg)
, m_Model(model)
, m_Batch(model)
, m_BatchFile(batchFile)
{
}

HANDLE BatchModelThread::Start()
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

void BatchModelThread::Run()
{
    RC rc;

    CHECK_RC_MSG_VOID(m_Batch.Parse(m_BatchFile));

    m_ConsoleDlg.m_Progress.SetRange32(0, m_Batch.GetCount() * m_Model.GetAlgorithmCount());
    m_ConsoleDlg.m_Progress.SetPos(0);

    for (UINT32 i = 1; i <= m_Batch.GetCount(); ++i)
    {
        CHECK_RC_MSG_VOID(m_Batch.ConfigModel(i));

        for (UINT32 j = 0; j < m_Model.GetAlgorithmCount(); ++j)
        {
            CHECK_RC_MSG_VOID(m_Model.RunSingleAlgorithm(j));
            m_ConsoleDlg.m_Progress.SetPos(i * m_Model.GetAlgorithmCount() + j + 1);
        }
    }
}

void BatchModelThread::Stop()
{
    m_ConsoleDlg.OnBatchThreadEnd();
}

DWORD WINAPI BatchModelThread::Run(LPVOID lparam)
{
    BatchModelThread *batchModelThread = (BatchModelThread *)lparam;
    if (!batchModelThread)
    {
        return -1;
    }

    batchModelThread->Run();

    batchModelThread->Stop();

    delete batchModelThread;

    return 0;
}
