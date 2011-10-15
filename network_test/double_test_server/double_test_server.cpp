/**
* @file
* @brief DoubleTestServer类cpp文件.
* @author ruoxi
*
* 实现了DoubleTestServer类.
*/

#include "double_test_server.h"
#include <iomanip>
#include <math.h>

DoubleTestServer::DoubleTestServer(int port, const char *logFileName, UINT32 maxClientNum)
:
TestTcpServer(port, logFileName, maxClientNum)
{
}

RC DoubleTestServer::Service(TcpSocket *clientSocket, DWORD threadId)
{
    RC rc;

    printf("[Server] Thread %u executing...\n", threadId);
    if (!clientSocket)
    {
        printf("[Server] %u - Client socket is NULL.\n", threadId);
        return OK;
    }

    UINT32 digitNumMax = 5;
    double max = 9.9, positiveBase = 9, minusBase = 0.9;
    for (UINT32 digit = 1; digit < digitNumMax; ++digit)
    {
        positiveBase *= 10;
        minusBase /= 10;
        max += positiveBase + minusBase;
    }

    double data;
    do
    {
        clientSocket->RecvDouble(data);
        printf("[Server] %u - Recieved double: %f\n", threadId, data);
        m_Logger<<setprecision(digitNumMax * 2)<<data<<endl;
        printf("[Server] %u - Sending double: %f\n", threadId, data);
        clientSocket->SendDouble(data);
    }
    while (data != max);

    clientSocket->Shut();
    return OK;
}
