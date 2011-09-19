#ifndef __TEST_CLIENT_H__
#define __TEST_CLIENT_H__

#include "net_socket.h"

class TestClient
{
public:
    TestClient();
    ~TestClient();

    int Initialize();
    int Shutdown();

    int Run(const char *hostName, int port);

    static void Print(NetSocket *socket);

private:
    Socket *m_ClientSocket;
};

#endif // __TEST_CLIENT_H__
