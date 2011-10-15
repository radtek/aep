/**
* @file
* @brief U32TestServer类cpp文件.
* @author ruoxi
*
* 实现了U32TestServer类.
*/

#include "u32_test_server.h"

U32TestServer::U32TestServer(int port, const char *logFileName, UINT32 maxClientNum)
:
TestTcpServer(port, logFileName, maxClientNum)
{
}

RC U32TestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    RC rc;

    printf("[Server] Thread %u executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %u - Client socket is NULL.\n", threadId);
        return OK;
    }
    UINT32 max = UINT32_MAX;
    UINT32 data;
    do
    {
        clientSocket->Recv32(data);
        printf("[Server] %u - Recieved UINT32: %u\n", threadId, data);
        m_Logger<<data<<endl;
        printf("[Server] %u - Sending UINT32: %u\n", threadId, data);
        clientSocket->Send32(data);
    }
    while (data != max);

    clientSocket->Shut();
    return OK;
}
