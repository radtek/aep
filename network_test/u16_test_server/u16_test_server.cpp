#include "u16_test_server.h"

U16TestServer::U16TestServer(int port, const char *logFileName, UINT32 maxClientNum)
:
TestTcpServer(port, logFileName, maxClientNum)
{
}

RC U16TestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    RC rc;

    printf("[Server] Thread %ul executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %ul - Client socket is NULL.\n", threadId);
        return OK;
    }
    UINT16 max = UINT16_MAX;
    UINT16 data;
    do
    {
        clientSocket->Recv16(data);
        printf("[Server] %ul - Recieved UINT16: %u\n", threadId, data);
        m_Logger<<data<<endl;
        printf("[Server] %ul - Sending UINT16: %u\n", threadId, data);
        clientSocket->Send16(data);
    }
    while (data != max);

    clientSocket->Shut();
    return OK;
}
