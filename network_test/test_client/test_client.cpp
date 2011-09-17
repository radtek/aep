#include "test_client.h"

TestClient::TestClient(const char *hostName, int port)
{
    m_Socket = CreateClientNetSocket(hostName, port);
    if (!m_Socket)
    {
        printf("[sockchip] Could not open network connection to %s:%d\n", hostName, port);
    }
    else
    {
        printf("[sockchip] Connected to %s:%d\n", hostName, port);
    }
}

TestClient::~TestClient()
{
    delete m_Socket;
    m_Socket = NULL;
}
