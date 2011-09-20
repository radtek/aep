#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include "socket.h"

class TcpSocket : public Socket
{
    TcpSocket();
    virtual ~TcpSocket();

    virtual RC Listen(int port);
    virtual RC Connect(const char *hostName, int port);
    virtual RC Accept(TcpSocket &clientSocket);

    virtual RC Send(const void *buf, size_t size);
	virtual RC Recv(void *buf, size_t size, RECVMODEL mode = NONBLOCK, UINT32 timeOut = 0);
};