#include "test_server.h"
#include "net_socket.h"

TestServer::TestServer()
:
m_Continue(true),
m_Listening(false)
{
    m_ListenSocket = new NetSocket;
    m_ListenSocket->InstallErrorHandler((ErrorHandlerFunc)(Print));
}

TestServer::~TestServer()
{
}

int TestServer::Initialize()
{
    if (0 != NetSocket::WSInitialize())
    {
        return SOCKET_ERROR;
    }

    if (0 != m_ListenSocket->Initialize())
    {
        return SOCKET_ERROR;
    }
    return 0;
}

int TestServer::Shutdown()
{
    if (0 != m_ListenSocket->Shutdown())
    {
        return SOCKET_ERROR;
    }

    if (0 != NetSocket::WSShutdown())
    {
        return SOCKET_ERROR;
    }
    return 0;
}

int TestServer::Service(int port)
{
    if (0 != m_ListenSocket->Listen(port))
    {
        return SOCKET_ERROR;
    }
    m_Listening = true;
    while (m_Continue)
    {
        Socket *clientSocket = new NetSocket();
        int result;
        do
        {
            result = m_ListenSocket->Accept(*clientSocket);
        }
        while ( 0 != result);

        DWORD threadId;
        HANDLE thread;
        thread = CreateThread(NULL,
                              NULL,
                              ServiceThread,
                              (LPVOID)clientSocket,
                              0,
                              &threadId);
        if(thread == NULL)
        {
            printf("[Server] CreatThread ServiceThread() failed.\n");
        }
        else
        {
            printf("[Server] CreateThread OK.\n");
        }
    }
    return 0;
}

void TestServer::Stop()
{
    m_Continue = false;
}

bool TestServer::IsListening()
{
    return m_Listening;
}

DWORD WINAPI TestServer::ServiceThread(LPVOID lparam)
{
    Socket *clientSocket = (Socket *)lparam;

    UINT32 i;
    do
    {
        i = clientSocket->Recv32();
        printf("[Server] Recieved: %u.\n", i);
        clientSocket->Send32(i);
        printf("[Server] Sent back: %u.\n", i);
    }
    while (i > 0);
    if (0 != clientSocket->Shutdown())
    {
        return SOCKET_ERROR;
    }

    delete clientSocket;
    return 0;
}

void TestServer::Print(NetSocket *socket)
{
    const NetError &error = socket->GetError();
    printf("[Server] Error code: %d.\n", error.ErrorCode);
    printf("[Server] Error message: %s.\n", error.ErrorMsg);
    printf("[Server] Appending message: %s.\n", error.AppendMsg);
}
