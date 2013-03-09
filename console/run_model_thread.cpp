#include "run_model_thread.h"

#include "utility.h"

RunModelThread::RunModelThread(CConsoleDlg &dlg, Model2 &model, UINT32 loopCount, TcpSocket *socket)
: m_ConsoleDlg(dlg)
, m_Model(model)
, m_LoopCount(loopCount)
, m_Socket(socket)
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
    m_ConsoleDlg.m_Progress.SetRange32(0, m_Model.GetAlgorithmCount() * m_LoopCount);
    m_ConsoleDlg.m_Progress.SetPos(0);

    for (UINT32 i = 0; i < m_LoopCount; ++i)
    {
        for (UINT32 j = 0; j < m_Model.GetAlgorithmCount(); ++j)
        {
            CString text = TEXT("正在运行循环");
            text.AppendFormat(TEXT("%u算法%u..."), i + 1, j + 1);
            m_ConsoleDlg.m_Status.SetWindowTextW(text);

            m_ConsoleDlg.m_ModelCtrl.SetRunItem(j);

            RC rc;
            CHECK_RC_MSG_VOID(m_Model.RunSingleAlgorithm(j));

            m_ConsoleDlg.m_Progress.SetPos(i * m_Model.GetAlgorithmCount() + j + 1);

            text = TEXT("循环");
            text.AppendFormat(TEXT("%u算法%u运行结束."), i + 1, j + 1);
            m_ConsoleDlg.m_Status.SetWindowTextW(text);
        }
        m_ConsoleDlg.m_Model.Reset();

        if (m_Socket)
        {
            m_Socket->SendCommand(CC::EVALUATE_COMMAND);
        }
    }

    if (m_Socket)
    {
        m_Socket->SendCommand(CC::EXIT_COMMAND);
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
