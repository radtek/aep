#ifndef __STEP_MODEL_THREAD_H__
#define __STEP_MODEL_THREAD_H__

#include "console_dlg.h"

class StepModelThread
{
public:
    StepModelThread(CConsoleDlg &dlg, Model &model, UINT32 algorithmId);

    HANDLE Start();

    void Stop();

private:
    void Run();

private:
    CConsoleDlg &m_ConsoleDlg;
    Model &m_Model;
    UINT32 m_AlgorithmId;

private:
    static DWORD WINAPI Run(LPVOID lparam);
};

#endif // __STEP_MODEL_THREAD_H__
