#include "u16_test_server.h"

U16TestServer::U16TestServer(int port, const char *logFileName, UINT32 maxClientNum)
:
TestTcpServer(port, logFileName, maxClientNum)
{
}

RC U16TestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    RC rc;

    printf("[Server] Thread %u executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %u - Client socket is NULL.\n", threadId);
        return OK;
    }
    UINT16 max = UINT16_MAX;
    UINT16 data;
    do
    {
        clientSocket->Recv16(data);
        printf("[Server] %u - Recieved UINT16: %u\n", threadId, data);
        m_Logger<<(UINT32)data<<endl;
        printf("[Server] %u - Sending UINT16: %u\n", threadId, data);
        clientSocket->Send16(data);
    }
    while (data != max);

    clientSocket->Shut();
    return OK;
}
