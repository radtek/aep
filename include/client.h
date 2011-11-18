#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "platform.h"
#include "tcp_socket.h"

class Client
{
public:
    Client();
    ~Client();

    RC Init();
    RC Shut();

private:
    Platform &m_Platform;
    TcpSocket m_Socket;
};

#endif // __CLIENT_H__
