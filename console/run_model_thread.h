#ifndef __RUN_MODEL_THREAD_H__
#define __RUN_MODEL_THREAD_H__

#include "console_dlg.h"

class RunModelThread
{
public:
    RunModelThread(CConsoleDlg &dlg, Model2 &model, UINT32 loopCount, TcpSocket *socket);

    HANDLE Start();

    void Stop();

private:
    void Run();

private:
    CConsoleDlg &m_ConsoleDlg;
    Model2 &m_Model;
    UINT32 m_LoopCount;

    TcpSocket *m_Socket;

private:
    static DWORD WINAPI Run(LPVOID lparam);
};

#endif // __RUN_MODEL_THREAD_H__
