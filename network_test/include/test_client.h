#ifndef __TEST_CLIENT_H__
#define __TEST_CLIENT_H__

#include "socket.h"

class TestClient
{
public:
    TestClient(const char *hostName, int port);
    ~TestClient();

private:
    Socket *m_Socket;
};

#endif // __TEST_CLIENT_H__
