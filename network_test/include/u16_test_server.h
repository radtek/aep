#ifndef __U16_TEST_SERVER_H__
#define __U16_TEST_SERVER_H__

#include "test_tcp_server.h"

class U16TestServer : public TestTcpServer
{
public:
    U16TestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __U16_TEST_SERVER_H__
