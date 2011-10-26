/**
* @file
* @brief FileTestServer类cpp文件.
* @author ruoxi
*
* 实现了FileTestServer类.
*/

#include "file_test_server.h"

extern LPCWSTR serverTempFileName;

FileTestServer::FileTestServer(int port, const char *logFileName, UINT32 maxClientNum)
:
TestTcpServer(port, logFileName, maxClientNum)
{
}

RC FileTestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    RC rc;

    printf("[Server] Thread %u executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %u - Client socket is NULL.\n", threadId);
        return OK;
    }

    CHECK_RC(clientSocket->RecvFile(serverTempFileName));
    printf("[Server] %u - Recieved file: %s.\n", threadId, serverTempFileName);
    printf("[Server] %u - Sending file: %s\n", threadId, serverTempFileName);
    CHECK_RC(clientSocket->SendFile(serverTempFileName));

    clientSocket->Shut();
    return OK;
}
