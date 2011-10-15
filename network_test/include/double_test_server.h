#ifndef __DOUBLE_TEST_SERVER_H__
#define __DOUBLE_TEST_SERVER_H__

#include "test_tcp_server.h"

class DoubleTestServer : public TestTcpServer
{
public:
    DoubleTestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __DOUBLE_TEST_SERVER_H__
