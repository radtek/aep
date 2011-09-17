#include "test_server.h"

TestServer::TestServer(int port)
{
    m_Socket = CreateServerNetSocket(port);
    if (!m_Socket)
    {
        printf("[sockchip] Could not create network server on port:%d\n", port);
    }
}

TestServer::~TestServer()
{
    delete m_Socket;
    m_Socket = NULL;
}
