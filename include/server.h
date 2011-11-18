#ifndef __SERVER_H__
#define __SERVER_H__

#include "platform.h"
#include "tcp_socket.h"

class Server
{
public:
    Server();
    ~Server();

    RC Init();
    RC Shut();

private:
    Platform &m_Platform;
    TcpSocket m_Socket;
};

#endif // __SERVER_H__
