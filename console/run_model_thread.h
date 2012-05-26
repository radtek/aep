#ifndef __RUN_MODEL_THREAD_H__
#define __RUN_MODEL_THREAD_H__

#include "console_dlg.h"

class RunModelThread
{
public:
    RunModelThread(CConsoleDlg &dlg, Model &model, UINT32 startId = 0);

    HANDLE Start();

    void Stop();

private:
    void Run();

private:
    CConsoleDlg &m_ConsoleDlg;
    Model &m_Model;
    UINT32 m_StartId;

private:
    static DWORD WINAPI Run(LPVOID lparam);
};

#endif // __RUN_MODEL_THREAD_H__
