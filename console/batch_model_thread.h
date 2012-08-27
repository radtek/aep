#ifndef __BATCH_MODEL_THREAD_H__
#define __BATCH_MODEL_THREAD_H__

#include "console_dlg.h"

#include "batch.h"

class BatchModelThread
{
public:
    BatchModelThread(CConsoleDlg &dlg, Model2 &model, const wstring &batchFile);

    HANDLE Start();

    void Stop();

private:
    void Run();

private:
    CConsoleDlg &m_ConsoleDlg;
    Model2 &m_Model;
    Batch m_Batch;
    wstring m_BatchFile;

private:
    static DWORD WINAPI Run(LPVOID lparam);
};

#endif // __BATCH_MODEL_THREAD_H__
