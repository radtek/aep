#ifndef __NET_SOCKET_H__
#define __NET_SOCKET_H__

#include <winsock2.h>
#include "socket.h"

#define ERROR_MSG_MAX_LEN 1024

struct NetError
{
    int ErrorCode;
    char ErrorMsg[ERROR_MSG_MAX_LEN];
    const char *AppendMsg;
};

class NetSocket: public Socket
{
public:
    static int WSInitialize();
    static int WSShutdown();

    NetSocket();
    virtual ~NetSocket();

    virtual int Initialize();
    virtual int Shutdown();

    virtual int Listen(int port);
    virtual int Connect(const char *hostname, int port);
    virtual int Accept(Socket &clientSocket);
    virtual int Recv(void *buf, size_t size);
    virtual int Send(const void *buf, size_t size);

    const NetError &GetError();

private:
    SOCKET m_Socket;
    NetError m_Error;
};

#endif // __NET_SOCKET_H__
