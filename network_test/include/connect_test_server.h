#ifndef __CONNECT_TEST_SERVER_H__
#define __CONNECT_TEST_SERVER_H__

#include "test_tcp_server.h"

class ConnectTestServer : public TestTcpServer
{
public:
    ConnectTestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __CONNECT_TEST_SERVER_H__
