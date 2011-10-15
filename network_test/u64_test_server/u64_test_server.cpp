/**
* @file
* @brief U64TestServer类cpp文件.
* @author ruoxi
*
* 实现了U64TestServer类.
*/

#include "u64_test_server.h"

U64TestServer::U64TestServer(int port, const char *logFileName, UINT32 maxClientNum)
:
TestTcpServer(port, logFileName, maxClientNum)
{
}

RC U64TestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    RC rc;

    printf("[Server] Thread %u executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %u - Client socket is NULL.\n", threadId);
        return OK;
    }
    UINT64 max = UINT64_MAX;
    UINT64 data;
    do
    {
        clientSocket->Recv64(data);
        printf("[Server] %u - Recieved UINT64: %llu\n", threadId, data);
        m_Logger<<data<<endl;
        printf("[Server] %u - Sending UINT64: %llu\n", threadId, data);
        clientSocket->Send64(data);
    }
    while (data != max);

    clientSocket->Shut();
    return OK;
}
