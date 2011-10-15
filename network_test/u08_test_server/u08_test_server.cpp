/**
* @file
* @brief U08TestServer类cpp文件.
* @author ruoxi
*
* 实现了U08TestServer类.
*/

#include "u08_test_server.h"

U08TestServer::U08TestServer(int port, const char *logFileName, UINT32 maxClientNum)
:
TestTcpServer(port, logFileName, maxClientNum)
{
}

RC U08TestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    RC rc;

    printf("[Server] Thread %u executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %u - Client socket is NULL.\n", threadId);
        return OK;
    }
    UINT08 max = UINT08_MAX;
    UINT08 data;
    do
    {
        clientSocket->Recv08(data);
        printf("[Server] %u - Recieved UINT08: %u\n", threadId, data);
        m_Logger<<(UINT32)data<<endl;
        printf("[Server] %u - Sending UINT08: %u\n", threadId, data);
        clientSocket->Send08(data);
    }
    while (data != max);

    clientSocket->Shut();
    return OK;
}
