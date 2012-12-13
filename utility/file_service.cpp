#include "utility.h"
#include "file_service.h"

FileService::FileService()
: m_RootPath(TEXT("."))
, m_RemoteHost("localhost")
, m_Port(10086)
, m_IsConnected(false)
, m_ListenThreadHandle(NULL)
{
}

FileService::~FileService()
{
}

RC FileService::Init(LPCWSTR rootPath, const char *remoteHost, int port)
{
    RC rc;

    m_RootPath = rootPath;

    m_RemoteHost = remoteHost;
    m_Port = port;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_ServerSocket.Init());
    CHECK_RC(m_ClientSocket.Init());

    return rc;
}

RC FileService::Shut()
{
    RC rc;

    if (m_ListenThreadHandle != NULL)
    {
        TerminateThread(m_ListenThreadHandle, 0);
    }
    for (UINT32 i = 0; i < m_ServiceThreadHandles.size(); ++i)
    {
        if (m_ServiceThreadHandles[i] != NULL)
        {
            TerminateThread(m_ListenThreadHandle, 0);
        }
    }

    return rc;
}

RC FileService::Listen()
{
    RC rc;

    m_ListenThreadHandle = CreateThread(NULL,
        NULL,
        ThreadListen,
        (LPVOID)this,
        0,
        0);

    if(m_ListenThreadHandle == NULL)
    {
        return RC::THREAD_CREATE_ERROR;
    }

    return OK;
}

RC FileService::RealListen()
{
    RC rc;

    CHECK_RC(m_ServerSocket.Listen(m_Port));

    while (true)
    {
        TcpSocket *clientSocket = new TcpSocket();
        CHECK_RC(m_ServerSocket.Accept(*clientSocket));
        ServiceThread *thread = new ServiceThread(clientSocket, m_RootPath);
        HANDLE handle;
        handle = CreateThread(NULL,
            NULL,
            ThreadService,
            (LPVOID)thread,
            0,
            0);
        if(handle == INVALID_HANDLE_VALUE)
        {
            return RC::THREAD_CREATE_ERROR;
        }
        m_ServiceThreadHandles.push_back(handle);
    }

    return OK;
}

RC FileService::DownloadFile(LPCWSTR filePath)
{
    wchar_t buf[1024];
    GetCurrentDirectory(1024, buf);
    if (!SetCurrentDirectory(m_RootPath.c_str()))
    {
        Utility::PromptLastErrorMessage();
        return RC::FILE_DIRECTORY_NOT_EXIST;
    }

    RC rc;

    if (!m_IsConnected)
    {
        CHECK_RC(m_ClientSocket.Connect(m_RemoteHost.c_str(), m_Port));
        m_IsConnected = true;
    }

    CHECK_RC(m_ClientSocket.SendWString(filePath));
    
    RC _rc;
    CHECK_RC(m_ClientSocket.RecvRC(_rc));
    CHECK_RC(_rc);

    CHECK_RC(m_ClientSocket.RecvFile(filePath));

    SetCurrentDirectory(buf);

    return rc;
}

FileService::ServiceThread::ServiceThread(TcpSocket *clientSocket, const wstring &rootPath)
: m_ClientSocket(clientSocket)
, m_RootPath(rootPath)
{
}

FileService::ServiceThread::~ServiceThread()
{
    m_ClientSocket->Shut();
    delete m_ClientSocket;
}

RC FileService::ServiceThread::RealService()
{
    RC rc;

    while (true)
    {
        wstring filePath;
        CHECK_RC(m_ClientSocket->RecvWString(filePath));

        wchar_t buf[1024];
        GetCurrentDirectory(1024, buf);
        if (!SetCurrentDirectory(m_RootPath.c_str()))
        {
            Utility::PromptLastErrorMessage();
            return RC::FILE_DIRECTORY_NOT_EXIST;
        }

        RC _rc;
        if (!Utility::FileExists(filePath.c_str()))
        {
            _rc = RC::DOWNLOAD_UNEXISTEFD_FILE_ERROR;
            CHECK_RC(m_ClientSocket->SendRC(_rc));
            return _rc;
        }
        CHECK_RC(m_ClientSocket->SendRC(_rc));

        CHECK_RC(m_ClientSocket->SendFile(filePath.c_str()));

        SetCurrentDirectory(buf);
    }

    return rc;
}

DWORD WINAPI FileService::ThreadListen(LPVOID lparam)
{
    FileService *fs = (FileService *)lparam;

    fs->RealListen();

    return 0;
}

DWORD WINAPI FileService::ThreadService(LPVOID lparam)
{
    ServiceThread *st = (ServiceThread *)lparam;

    st->RealService();

    delete st;

    return 0;
}
