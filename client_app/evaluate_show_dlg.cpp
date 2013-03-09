// evaluate_show_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "evaluate_show_dlg.h"
#include "evaluate_result_dlg.h"
#include "utility.h"

// CEvaluateShowDlg dialog

IMPLEMENT_DYNAMIC(CEvaluateShowDlg, CDialog)

CEvaluateShowDlg::CEvaluateShowDlg(const vector<AlgorithmRuntime> &algorithms,
                                   const vector<Factor> &factors,
                                   Engine *engine,
                                   CWnd* pParent /*=NULL*/)
	: CDialog(CEvaluateShowDlg::IDD, pParent)
    , m_Time(_T("-"))
    , m_Cpu(_T("-"))
    , m_Memory(_T("-"))
    , m_Ns(_T("-"))
    , m_Algorithms(algorithms)
    , m_Factors(factors)
    , m_Evaluate(Evaluate::GetInstance())
    , m_Port(10088)
    , m_Engine(engine)
{
    m_OrigImg[0] = &m_Img00;
    m_OutputImg[0] = &m_Img01;
    m_OrigImg[1] = &m_Img10;
    m_OutputImg[1] = &m_Img11;

    m_OrigBmp[0] = 0;
    m_OrigBmp[1] = 0;
    m_OutputBmp[0] = 0;
    m_OutputBmp[1] = 0;
}

CEvaluateShowDlg::~CEvaluateShowDlg()
{
    if (m_Handle != INVALID_HANDLE_VALUE)
    {
    }
}

void CEvaluateShowDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TIME_TEXT, m_Time);
    DDX_Text(pDX, IDC_CPU_TEXT, m_Cpu);
    DDX_Text(pDX, IDC_MEMORY_TEXT, m_Memory);
    DDX_Text(pDX, IDC_NS_TEXT, m_Ns);
    DDX_Control(pDX, IDC_IMG_0_0, m_Img00);
    DDX_Control(pDX, IDC_IMG_0_1, m_Img01);
    DDX_Control(pDX, IDC_IMG_1_0, m_Img10);
    DDX_Control(pDX, IDC_IMG_1_1, m_Img11);
}

RC CEvaluateShowDlg::Listen()
{
    RC rc;

    m_Handle = CreateThread(NULL,
        NULL,
        ThreadListen,
        (LPVOID)this,
        0,
        0);

    if(m_Handle == INVALID_HANDLE_VALUE)
    {
        return RC::THREAD_CREATE_ERROR;
    }

    return OK;
}

RC CEvaluateShowDlg::RealListen()
{
    RC rc;

    CHECK_RC(m_Socket.Listen(m_Port));

    while (true)
    {
        TcpSocket clientSocket;

        CHECK_RC(m_Socket.Accept(clientSocket));

        // Utility::PromptMessage(TEXT("¼àÌý³É¹¦."));
        UINT32 index = 0;
        while (true)
        {
            CC cc;
            CHECK_RC(clientSocket.RecvCommand(cc));
            if (cc == CC::EVALUATE_COMMAND)
            {
                vector<AlgorithmRuntimeResult> algorithmResults;
                if (OK != m_Evaluate.DoSingleEvaluate(m_Algorithms, m_Factors, algorithmResults, index))
                {
                    Utility::PromptErrorMessage(TEXT("ÆÀ¹À´íÎó."));
                }
                m_Cpu.Empty();
                m_Cpu.AppendFormat(TEXT("%u%%"), algorithmResults[0].CpuPercentage.back());
                m_Memory.Empty();
                m_Memory.AppendFormat(TEXT("%uKB"), algorithmResults[0].MemoryUsageKB.back());
                m_Ns.Empty();
                m_Ns.AppendFormat(TEXT("%uNS"), algorithmResults[0].NS.back());

                for (UINT32 i = 0; i < min(m_Factors.size(), 2); ++i)
                {
                    if (m_OrigBmp[i])
                    {
                        DeleteObject(m_OrigBmp[i]);
                    }
                    if (m_OutputBmp[i])
                    {
                        DeleteObject(m_OutputBmp[i]);
                    }
                    wstring filePath = Utility::InsertNumToFileName(m_Factors[i].AlgorithmOutput, m_Factors[i].AlgorithmOutputStart + index);
                    m_OrigBmp[i] = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
                        filePath.c_str(),
                        IMAGE_BITMAP,
                        0,
                        0,
                        LR_LOADFROMFILE | LR_CREATEDIBSECTION);
                    if (m_OrigBmp[i])
                    {
                        m_OrigImg[i]->SetBitmap(m_OrigBmp[i]);
                    }
                    filePath = Utility::InsertNumToFileName(m_Factors[i].AlgorithmOutput, m_Factors[i].AlgorithmOutputStart + index);
                    m_OutputBmp[i] = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
                        filePath.c_str(),
                        IMAGE_BITMAP,
                        0,
                        0,
                        LR_LOADFROMFILE | LR_CREATEDIBSECTION);
                    if (m_OutputBmp[i])
                    {
                        m_OutputImg[i]->SetBitmap(m_OutputBmp[i]);
                    }
                }

                LRESULT result = ::SendMessage(m_hWnd, WM_UPDATE_ALL, 0, NULL);

                ++index;
            }
            else if (cc == CC::EXIT_COMMAND)
            {
                vector<AlgorithmRuntimeResult> algorithmResults;
                vector<FactorResult> factorResults;

                if (OK != m_Evaluate.DoEvaluate(m_Algorithms, m_Factors, algorithmResults, factorResults))
                {
                    Utility::PromptErrorMessage(TEXT("ÆÀ¹À´íÎó."));
                }

                CEvaluateResultDlg dlg(m_Algorithms, algorithmResults, m_Factors, factorResults, m_Engine);
                dlg.DoModal();

                for (UINT32 i = 0; i < factorResults.size(); ++i)
                {
                    mxDestroyArray(factorResults[i].Result);
                }
                break;;
            }
        }
    }
    return OK;
}

DWORD WINAPI CEvaluateShowDlg::ThreadListen(LPVOID lparam)
{
    CEvaluateShowDlg *dlg = (CEvaluateShowDlg *)lparam;

    if (OK != dlg->RealListen())
    {
        Utility::PromptErrorMessage(TEXT("¼àÌýÊ§°Ü."));
    }

    return 0;
}

BEGIN_MESSAGE_MAP(CEvaluateShowDlg, CDialog)
    ON_MESSAGE(CEvaluateShowDlg::WM_UPDATE_ALL, OnUpdateAll)
END_MESSAGE_MAP()

BOOL CEvaluateShowDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

    if (OK != m_Socket.Init())
    {
        Utility::PromptErrorMessage(TEXT("Ì×½Ó×Ö³õÊ¼»¯Ê§°Ü."));
        m_Socket.Init();
        return FALSE;
    }

    if (OK != Listen())
    {
        Utility::PromptErrorMessage(TEXT("¼àÌýÊ§°Ü."));
        return FALSE;
    }

    return TRUE;
}

LRESULT CEvaluateShowDlg::OnUpdateAll(WPARAM wParam, LPARAM lParam)
{
    UpdateData(0);
    Invalidate();
    return 0;
}