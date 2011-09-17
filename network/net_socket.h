#ifndef __NET_SOCKET_H__
#define __NET_SOCKET_H__

#include <winsock2.h>
#include "socket.h"

class NetSocket: public Socket
{
public:
    NetSocket();
    virtual ~NetSocket();

    void Listen(int port);
    void Connect(const char *hostname, int port);
    int GetPortNumber();

    virtual void WaitForConnection();
    virtual void Recv(void *buf, size_t size);
    virtual void Send(const void *buf, size_t size);

private:
    SOCKET m_Socket;
};

#endif // __NET_SOCKET_H__
