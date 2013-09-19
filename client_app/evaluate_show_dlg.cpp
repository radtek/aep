// evaluate_show_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "evaluate_show_dlg.h"
#include "evaluate_result_dlg.h"
#include "utility.h"

#include "matlab_helper.h"

#include <fstream>
#include <iostream>

using namespace std;

// CEvaluateShowDlg dialog

IMPLEMENT_DYNAMIC(CEvaluateShowDlg, CDialog)

CEvaluateShowDlg::CEvaluateShowDlg(const vector<AlgorithmRuntime> &algorithms,
                                   const vector<Factor> &factors,
                                   const vector<ImageMonitor> &imageMonitors,
                                   Engine *engine,
                                   CWnd* pParent /*=NULL*/)
	: CDialog(CEvaluateShowDlg::IDD, pParent)
    , m_Time(_T("-"))
    , m_Cpu(_T("-"))
    , m_Memory(_T("-"))
    , m_Ns(_T("-"))
    , m_Algorithms(algorithms)
    , m_Factors(factors)
    , m_ImageMonitors(imageMonitors)
    , m_Evaluate(Evaluate::GetInstance())
    , m_Port(10088)
    , m_Engine(engine)
    , m_ImageMonitorTitle0(_T(""))
    , m_ImageMonitorTitle1(_T(""))
    , m_ImageMonitorTitle2(_T(""))
    , m_ImageMonitorTitle3(_T(""))
    , m_Param0(_T(""))
    , m_Param1(_T(""))
    , m_Param2(_T(""))
    , m_Param3(_T(""))
    , m_Param4(_T(""))
    , m_Param5(_T(""))
    , m_Param6(_T(""))
    , m_Param7(_T(""))
    , m_Param8(_T(""))
    , m_Param9(_T(""))
{
    m_Img[0] = &m_Img0;
    m_Img[1] = &m_Img1;
    m_Img[2] = &m_Img2;
    m_Img[3] = &m_Img3;

    m_ImageMonitorTitle[0] = &m_ImageMonitorTitle0;
    m_ImageMonitorTitle[1] = &m_ImageMonitorTitle1;
    m_ImageMonitorTitle[2] = &m_ImageMonitorTitle2;
    m_ImageMonitorTitle[3] = &m_ImageMonitorTitle3;

    m_Param[0] = &m_Param0;
    m_Param[1] = &m_Param1;
    m_Param[2] = &m_Param2;
    m_Param[3] = &m_Param3;
    m_Param[4] = &m_Param4;
    m_Param[5] = &m_Param5;
    m_Param[6] = &m_Param6;
    m_Param[7] = &m_Param7;
    m_Param[8] = &m_Param8;
    m_Param[9] = &m_Param9;
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
    DDX_Control(pDX, IDC_IMG_0, m_Img0);
    DDX_Control(pDX, IDC_IMG_1, m_Img1);
    DDX_Control(pDX, IDC_IMG_2, m_Img2);
    DDX_Control(pDX, IDC_IMG_3, m_Img3);
    DDX_Text(pDX, IDC_IMG0_TITLE, m_ImageMonitorTitle0);
    DDX_Text(pDX, IDC_IMG1_TITLE, m_ImageMonitorTitle1);
    DDX_Text(pDX, IDC_IMG2_TITLE, m_ImageMonitorTitle2);
    DDX_Text(pDX, IDC_IMG3_TITLE, m_ImageMonitorTitle3);
    DDX_Text(pDX, IDC_PARAM_0, m_Param0);
    DDX_Text(pDX, IDC_PARAM_1, m_Param1);
    DDX_Text(pDX, IDC_PARAM_2, m_Param2);
    DDX_Text(pDX, IDC_PARAM_3, m_Param3);
    DDX_Text(pDX, IDC_PARAM_4, m_Param4);
    DDX_Text(pDX, IDC_PARAM_5, m_Param5);
    DDX_Text(pDX, IDC_PARAM_6, m_Param6);
    DDX_Text(pDX, IDC_PARAM_7, m_Param7);
    DDX_Text(pDX, IDC_PARAM_8, m_Param8);
    DDX_Text(pDX, IDC_PARAM_9, m_Param9);
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

                // Download the 5th file.
                wstring filePath = Utility::InsertNumToFileName(m_ImageMonitors.back().Path, m_ImageMonitors.back().Start + index);
                if (!Utility::FileExists(filePath.c_str()))
                {
                    if (OK != m_Evaluate.GetModelFS().DownloadFile(filePath.c_str()))
                    {
                        // Error here.
                        continue;
                    }
                }
                wifstream ifs(filePath.c_str());
                if (!ifs)
                {
                    // Error here.
                    continue;
                }
                UINT32 dummyWidth, dummyHeight;
                ifs >> dummyWidth >> dummyHeight;
                UINT32 meCenterX, meCenterY, tarCenterX, tarCenterY;
                ifs >> meCenterX >> meCenterY >> tarCenterX >> tarCenterY;
                UINT32 n;
                ifs >> n;
                double *param = new double[n];
                for (UINT32 i = 0; i < n; ++i)
                {
                    ifs >> param[i];
                }
                ifs.close();

                for (UINT32 i = 0; i < min(10, n); ++i)
                {
                    *m_Param[i] = TEXT("");
                    m_Param[i]->AppendFormat(TEXT("%f"), param[i]);
                }

                for (UINT32 i = 0; i < min(4, m_ImageMonitors.size() - 1); ++i)
                {
                    *m_ImageMonitorTitle[i] = m_ImageMonitors[i].Title.c_str();
                    if (m_Bmp[i])
                    {
                        DeleteObject(m_Bmp[i]);
                        m_Bmp[i] = 0;
                    }
                    wstring filePath = Utility::InsertNumToFileName(m_ImageMonitors[i].Path, m_ImageMonitors[i].Start + index);
                    HBITMAP srcBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
                        filePath.c_str(),
                        IMAGE_BITMAP,
                        0,
                        0,
                        LR_LOADFROMFILE | LR_CREATEDIBSECTION);
                    HDC srcDc = CreateCompatibleDC(NULL);
                    SelectObject(srcDc, srcBmp);

                    BITMAP bmp;
                    GetObject(srcBmp, sizeof(BITMAP), &bmp);
                    int width = bmp.bmWidth, height = bmp.bmHeight > EXTRA_HEIGHT ? bmp.bmHeight - EXTRA_HEIGHT : bmp.bmHeight;

                    m_Bmp[i] = CreateCompatibleBitmap(srcDc, width, height);

                    HDC dstDc = CreateCompatibleDC(NULL);
                    HBITMAP oldBmp = (HBITMAP)SelectObject(dstDc, m_Bmp[i]);
                    BitBlt(dstDc, 0, 0, width, height, srcDc, 0, 0, SRCCOPY);
                    m_Bmp[i] = (HBITMAP)SelectObject(dstDc, oldBmp);

                    DeleteObject(srcBmp);
                    DeleteDC(srcDc);
                    DeleteDC(dstDc);

                    // FIXME: Draw me and target.
                    if (i == 0)
                    {
                        CDC drawDc;
                        drawDc.CreateCompatibleDC(NULL);
                        HBITMAP oldBmp = (HBITMAP)drawDc.SelectObject(m_Bmp[i]);

                        CPen mePen;
                        mePen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
                        CPen *oldPen = drawDc.SelectObject(&mePen);
                        drawDc.Rectangle(meCenterX - 64, meCenterY - 64, meCenterX + 64, meCenterY + 64);
                        drawDc.SelectObject(oldPen);
 
                        CPen tarPen;
                        tarPen.CreatePen(PS_DASH, 1, RGB(255, 255, 255));
                        oldPen = drawDc.SelectObject(&tarPen);
                        drawDc.Rectangle(tarCenterX - 64, tarCenterY - 64, tarCenterX + 64, tarCenterY + 64);
                        drawDc.SelectObject(oldPen);

                        m_Bmp[i] = (HBITMAP)drawDc.SelectObject(oldBmp);

                        mePen.DeleteObject();
                        tarPen.DeleteObject();
                        drawDc.DeleteDC();
                    }

                    if (m_Bmp[i])
                    {
                        m_Img[i]->SetBitmap(m_Bmp[i]);
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