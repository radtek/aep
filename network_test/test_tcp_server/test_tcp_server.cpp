#include "test_tcp_server.h"

TestTcpServer::TestTcpServer(int port, const char *logFileName, UINT32 maxClientNum)
:
m_Port(port),
m_Logger(logFileName),
m_MaxClientNum(maxClientNum)
{
    m_TcpSocket = new TcpSocket;
}

TestTcpServer::~TestTcpServer()
{
}

RC TestTcpServer::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_TcpSocket->Init());

    return rc;
}

RC TestTcpServer::Shut()
{
    RC rc;

    CHECK_RC(m_TcpSocket->Shut());

    CHECK_RC(Socket::Shut());

    m_Logger.close();

    return rc;
}

RC TestTcpServer::Listen()
{
    RC rc;

    CHECK_RC(m_TcpSocket->Listen(m_Port));

    UINT32 clientNum = 0;

    while (clientNum < m_MaxClientNum)
    {
        TcpSocket *clientSocket = new TcpSocket();

        CHECK_RC(m_TcpSocket->Accept(*clientSocket));

        HANDLE thread;
        ThreadInfo info =
        {
            0,
            this,
            clientSocket
        };
        thread = CreateThread(NULL,
            NULL,
            Dispatch,
            (LPVOID)&info,
            0,
            &info.ThreadId);
        if(thread == NULL)
        {
            return RC::THREAD_CREATE_ERROR;
        }
        ++clientNum;
    }
    return OK;
}

DWORD WINAPI TestTcpServer::Dispatch(LPVOID lparam)
{
    ThreadInfo *info = (ThreadInfo *)lparam;
    info->Server->Service(info->ClientSocket, info->ThreadId);
    return 0;
}
