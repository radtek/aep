#ifndef __TEST_TCP_CLIENT_H__
#define __TEST_TCP_CLIENT_H__

#include "tcp_socket.h"

class TestTcpClient
{
public:
    TestTcpClient();
    ~TestTcpClient();

    RC Init();
    RC Shut();

    RC Connect(const char *hostName, int port);

    virtual RC Run() = 0;

protected:
    TcpSocket *m_TcpSocket;
};

#endif // __TEST_TCP_CLIENT_H__
