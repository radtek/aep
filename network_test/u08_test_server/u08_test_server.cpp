#include "u08_test_server.h"

RC U08TestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    printf("[Server] Thread %ul executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %ul - Client socket is NULL.\n", threadId);
        return OK;
    }
    UINT08 max = 255;
    UINT08 data;
    do
    {
        clientSocket->Recv08(data);
        printf("[Server] %ul - Recieved UINT08: %u\n", threadId, data);
        printf("[Server] %ul - Sending UINT08: %u\n", threadId, data);
        clientSocket->Send08(data);
    }
    while (data != max);

    clientSocket->Shut();
    return OK;
}
