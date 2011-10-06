#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include "socket.h"
#include <winsock2.h>

class TcpSocket : public Socket
{
public:
    TcpSocket();
    virtual ~TcpSocket();

    virtual RC Init();
    virtual RC Shut();

    virtual RC Listen(int port);
    virtual RC Connect(const char *hostName, int port);
    virtual RC Accept(TcpSocket &clientSocket);

    virtual RC Recv(void *buf, size_t size);
    virtual RC Send(const void *buf, size_t size);

private:
    SOCKET m_Socket;
};

#endif // __TCP_SOCKET_H__
