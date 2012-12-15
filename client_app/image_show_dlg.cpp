// image_show_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "image_show_dlg.h"
#include "utility.h"

// CImageShowDlg dialog

IMPLEMENT_DYNAMIC(CImageShowDlg, CBCGPPropertyPage)

CImageShowDlg::CImageShowDlg()
	: CBCGPPropertyPage(CImageShowDlg::IDD)
    , m_FileName(_T("."))
    , m_Path(_T("."))
    , m_CurrentId(0)
    , m_Interval(1000)
    , m_Timer(0)
    , m_Started(false)
    , m_Bitmap(0)
{

}

CImageShowDlg::~CImageShowDlg()
{
    if (m_Bitmap)
    {
        DeleteObject(m_Bitmap);
    }
}

void CImageShowDlg::DoDataExchange(CDataExchange* pDX)
{
    CBCGPPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_IMAGE, m_ImageCtrl);
    DDX_Text(pDX, IDC_FILE_NAME_STATIC, m_FileName);
    DDX_Text(pDX, IDC_INTERVAL, m_Interval);
}

BOOL CImageShowDlg::OnInitDialog() 
{
    CBCGPPropertyPage::OnInitDialog();

    m_Path = TEXT(".");

    return TRUE;
}

void CImageShowDlg::ShowImage(const CString &fileName)
{
    if (m_Bitmap)
    {
        DeleteObject(m_Bitmap);
    }

    m_Bitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
        fileName,
        IMAGE_BITMAP,
        0,
        0,
        LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    if (!m_Bitmap)
    {
        Utility::PromptErrorMessage(TEXT("打开图像文件失败."));
    }
    m_ImageCtrl.SetBitmap(m_Bitmap);
    m_FileName = fileName;
    UpdateData(FALSE);
    Invalidate();
}

BEGIN_MESSAGE_MAP(CImageShowDlg, CPropertyPage)
    ON_BN_CLICKED(IDC_SELECT_PATH, &CImageShowDlg::OnBnClickedSelectPath)
    ON_BN_CLICKED(IDC_START_PAUSE_BUTTON, &CImageShowDlg::OnBnClickedStartPauseButton)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_PREV_BUTTON, &CImageShowDlg::OnBnClickedPrevButton)
    ON_BN_CLICKED(IDC_NEXT_BUTTON, &CImageShowDlg::OnBnClickedNextButton)
END_MESSAGE_MAP()


// CImageShowDlg message handlers

void CImageShowDlg::OnBnClickedSelectPath()
{
    // TODO: Add your control notification handler code here
    m_Started = false;
    KillTimer(m_Timer);

    LPITEMIDLIST pidlPath;
    TCHAR pszDplName[MAX_PATH];

    BROWSEINFO biFile;
    IMalloc *pDllMlc;

    biFile.hwndOwner = m_hWnd;
    biFile.pidlRoot = NULL;
    biFile.pszDisplayName = NULL;
    biFile.lpszTitle = _T("请选择要打开的文件夹:");
    biFile.ulFlags = BIF_RETURNFSANCESTORS;
    biFile.lpfn = NULL;
    biFile.lParam = NULL;
    biFile.iImage = 0;

    if (SUCCEEDED(SHGetMalloc(&pDllMlc)))   
    {
        pidlPath = SHBrowseForFolder(&biFile);   
        if(pidlPath != NULL)   
        {
            SHGetPathFromIDList(pidlPath, pszDplName);
            // this->MessageBox(pszDplName);
            m_Path = pszDplName;
        }
        else 
        {
            return;
        }
        pDllMlc->Free(NULL);   
        pDllMlc->Release(); 
    }

    m_FileName = m_Path;
    UpdateData(FALSE);

    m_FileNames.clear();
    m_CurrentId = 0;

    CFileFind szFind;
    wchar_t szTempFileFind[MAX_PATH];
    wsprintf(szTempFileFind, TEXT("%s//*.*"), m_Path);
    BOOL IsFind = szFind.FindFile(szTempFileFind);
    while (IsFind)
    {
        IsFind = szFind.FindNextFile();
        if (!szFind.IsDots())
        {
            if (!szFind.IsDirectory())	//不是目录
            {
                wchar_t szFoundFileName[MAX_PATH] = TEXT("/0");
                lstrcpy(szFoundFileName, szFind.GetFileName().GetBuffer(MAX_PATH));

                if (szFoundFileName[0])
                {
                    //处理这个文件
                    CString ext = Utility::GetExtName(wstring(szFoundFileName)).c_str();
                    ext.MakeLower();
                    if (ext == TEXT("bmp"))
                    {
                        m_FileNames.push_back(CString(szFoundFileName));
                    }
                }
            }
        }
    }
    szFind.Close();
}

void CImageShowDlg::OnBnClickedStartPauseButton()
{
    // TODO: Add your control notification handler code here
    if (!m_Started)
    {
        m_Started = true;
        UpdateData();
        SetTimer(0, m_Interval, NULL);
    }
    else
    {
        m_Started = false;
        KillTimer(m_Timer);
    }
}

void CImageShowDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default

    CBCGPPropertyPage::OnTimer(nIDEvent);

    OnBnClickedNextButton();
}

void CImageShowDlg::OnBnClickedPrevButton()
{
    // TODO: Add your control notification handler code here
    if (m_FileNames.size() == 0)
    {
        return;
    }

    if (m_CurrentId >= m_FileNames.size())
    {
        m_CurrentId = 0;
    }

    const CString &currentFileName = m_FileNames[m_CurrentId];
    CString fileName = m_Path + TEXT("\\") + currentFileName;

    ShowImage(fileName);

    if (m_CurrentId == 0)
    {
        m_CurrentId = m_FileNames.size() - 1;
    }
    else
    {
        --m_CurrentId;
    }
}

void CImageShowDlg::OnBnClickedNextButton()
{
    // TODO: Add your control notification handler code here
    if (m_FileNames.size() == 0)
    {
        return;
    }

    if (m_CurrentId >= m_FileNames.size())
    {
        m_CurrentId = 0;
    }

    const CString &currentFileName = m_FileNames[m_CurrentId];
    CString fileName = m_Path + TEXT("\\") + currentFileName;

    ShowImage(fileName);

    ++m_CurrentId;
}
