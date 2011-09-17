#ifndef __TEST_SERVER_H__
#define __TEST_SERVER_H__

#include "socket.h"

class TestServer
{
public:
    TestServer(int port);
    ~TestServer();

private:
    Socket *m_Socket;
};

#endif // __TEST_SERVER_H__
