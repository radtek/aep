#ifndef __CONNECT_TEST_SERVER_H__
#define __CONNECT_TEST_SERVER_H__

#include "test_tcp_server.h"

class ConnectTestServer : public TestTcpServer
{
public:
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __CONNECT_TEST_SERVER_H__
