#include "u64_test_server.h"

U64TestServer::U64TestServer(int port, const char *logFileName, UINT32 maxClientNum)
:
TestTcpServer(port, logFileName, maxClientNum)
{
}

RC U64TestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    RC rc;

    printf("[Server] Thread %ul executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %ul - Client socket is NULL.\n", threadId);
        return OK;
    }
    UINT64 max = UINT64_MAX;
    UINT64 data;
    do
    {
        clientSocket->Recv64(data);
        printf("[Server] %ul - Recieved UINT64: %u\n", threadId, data);
        m_Logger<<data<<endl;
        printf("[Server] %ul - Sending UINT64: %u\n", threadId, data);
        clientSocket->Send64(data);
    }
    while (data != max);

    clientSocket->Shut();
    return OK;
}
