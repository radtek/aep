#include "u08_test_server.h"

U08TestServer::U08TestServer(int port, const char *logFileName, UINT32 maxClientNum)
:
TestTcpServer(port, logFileName, maxClientNum)
{
}

RC U08TestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    RC rc;

    printf("[Server] Thread %ul executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %ul - Client socket is NULL.\n", threadId);
        return OK;
    }
    UINT08 max = UINT08_MAX;
    UINT08 data;
    do
    {
        clientSocket->Recv08(data);
        printf("[Server] %ul - Recieved UINT08: %u\n", threadId, data);
        m_Logger<<data<<endl;
        printf("[Server] %ul - Sending UINT08: %u\n", threadId, data);
        clientSocket->Send08(data);
    }
    while (data != max);

    clientSocket->Shut();
    return OK;
}
