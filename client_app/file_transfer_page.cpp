// file_transfer_page.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "file_transfer_page.h"

#include "utility.h"


// CFileTransferPage dialog

IMPLEMENT_DYNAMIC(CFileTransferPage, CPropertyPage)

CFileTransferPage::CFileTransferPage()
	: CBCGPPropertyPage(CFileTransferPage::IDD)
    , m_Client(Client::GetInstance())
{

}

CFileTransferPage::~CFileTransferPage()
{
}

void CFileTransferPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_FILE_LIST, m_FileList);
    DDX_Control(pDX, IDC_FILE_TRANSFER_PROGRESS, m_FileTransferProgress);
}


BEGIN_MESSAGE_MAP(CFileTransferPage, CPropertyPage)
    ON_BN_CLICKED(IDC_UPLOAD_BUTTON, &CFileTransferPage::OnBnClickedUploadButton)
    ON_BN_CLICKED(IDC_DOWNLOAD_BUTTON, &CFileTransferPage::OnBnClickedDownloadButton)
    ON_BN_CLICKED(IDC_UPDATE_FILE_LIST_BUTTON, &CFileTransferPage::OnBnClickedUpdateFileListButton)
END_MESSAGE_MAP()


// CFileTransferPage message handlers

BOOL CFileTransferPage::OnInitDialog() 
{
    CBCGPPropertyPage::OnInitDialog();

    return TRUE;
}

void CFileTransferPage::OnBnClickedUploadButton()
{
    // TODO: Add your control notification handler code here
    if (!m_Client.IsLogined())
    {
        Utility::PromptErrorMessage(TEXT("您尚未登录."));
        return;
    }

    CFileDialog dlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, TEXT("Model Files (*.mod)|*.mod|Data Files (*.dat)|*.dat|Dll Files (*.dll)|*.dll|All Files (*.*)|*.*||"));
    const DWORD MAXFILE = 255;
    dlg.m_ofn.nMaxFile = MAXFILE;
    wchar_t *buf = new wchar_t[MAXFILE];
    dlg.m_ofn.lpstrFile = buf;
    dlg.m_ofn.lpstrFile[0] = NULL;

    vector<wstring> fileList;
    if (IDOK == dlg.DoModal())
    {
        POSITION pos = dlg.GetStartPosition();
        while (pos != NULL)
        {
            wstring fileName(dlg.GetNextPathName(pos));
            fileList.push_back(fileName);
        }
    }

    m_FileTransferProgress.SetPos(0);
    m_FileTransferProgress.SetRange32(0, fileList.size());

    for (UINT32 i = 0; i < fileList.size(); ++i)
    {
        wstring &fileName = fileList[i];
        if (OK != m_Client.UploadFile(fileName))
        {
            Utility::PromptErrorMessage(TEXT("上传文件失败."));
        }
        else
        {
            m_FileTransferProgress.SetPos(i + 1);
        }
    }

    GetFileList();

    UpdateData(0);
}

void CFileTransferPage::OnBnClickedDownloadButton()
{
    // TODO: Add your control notification handler code here
    if (!m_Client.IsLogined())
    {
        Utility::PromptErrorMessage(TEXT("您尚未登录."));
        return;
    }

    UINT32 count = m_FileList.GetSelectedCount();
    POSITION pos= m_FileList.GetFirstSelectedItemPosition();

    m_FileTransferProgress.SetPos(0);
    m_FileTransferProgress.SetRange32(0, count);
    for(UINT32 i = 0; i < count; ++i)
    {
        int index = m_FileList.GetNextSelectedItem(pos);
        wstring fileName(m_FileList.GetItemText(index, 0));
        CFileDialog dlg(FALSE, NULL, fileName.c_str());
        if (IDOK == dlg.DoModal())
        {
            wstring pathName(dlg.GetPathName());
            RC rc = m_Client.DownLoadFile(fileName, pathName);
            if (RC::DOWNLOAD_UNEXISTEFD_FILE_ERROR == rc)
            {
                Utility::PromptErrorMessage(TEXT("文件不存在."));
            }
            else if (OK != rc)
            {
                Utility::PromptErrorMessage(TEXT("下载文件失败."));
            }
        }
        m_FileTransferProgress.SetPos(i + 1);
    }
}

void CFileTransferPage::OnBnClickedUpdateFileListButton()
{
    // TODO: Add your control notification handler code here
    if (!m_Client.IsLogined())
    {
        Utility::PromptErrorMessage(TEXT("您尚未登录."));
        return;
    }

    GetFileList();

    UpdateData(0);
}

void CFileTransferPage::GetFileList()
{
    vector<wstring> fileList;
    if (OK != m_Client.GetFileList(fileList))
    {
        Utility::PromptErrorMessage(TEXT("获取服务器文件列表失败."));
    }

    m_FileList.DeleteAllItems();

    for (UINT32 i = 0; i < fileList.size(); ++i)
    {
        m_FileList.InsertItem(i, fileList[i].c_str());
    }
}
