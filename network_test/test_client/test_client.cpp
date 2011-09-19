#include "test_client.h"

TestClient::TestClient()
{
    m_ClientSocket = new NetSocket();
    m_ClientSocket->InstallErrorHandler((ErrorHandlerFunc)(Print));
}

TestClient::~TestClient()
{
}

int TestClient::Initialize()
{
    if (0 != NetSocket::WSInitialize())
    {
        return SOCKET_ERROR;
    }

    if (0 != m_ClientSocket->Initialize())
    {
        return SOCKET_ERROR;
    }
    return 0;
}

int TestClient::Shutdown()
{
    if (0 != m_ClientSocket->Shutdown())
    {
        return SOCKET_ERROR;
    }

    if (0 != NetSocket::WSShutdown())
    {
        return SOCKET_ERROR;
    }
    return 0;
}

int TestClient::Run(const char *hostName, int port)
{
    if (0 != m_ClientSocket->Connect(hostName, port))
    {
        return SOCKET_ERROR;
    }

    for (UINT32 i = 0; i <= 10; ++i)
    {
        m_ClientSocket->Send32(10 - i);
        printf("[Client] Sent: %u.\n", 10 - i);
        UINT32 temp = m_ClientSocket->Recv32();
        printf("[Client] Recieved back: %u.\n", temp);
    }
    return 0;
}

void TestClient::Print(NetSocket *socket)
{
    const NetError &error = socket->GetError();
    printf("[Client] Error code: %d.\n", error.ErrorCode);
    printf("[Client] Error message: %s.\n", error.ErrorMsg);
    printf("[Client] Appending message: %s.\n", error.AppendMsg);
}
