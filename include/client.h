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

    RC Connect();

    RC Login(const wstring &name, const wstring &password);

private:
    Platform &m_Platform;
    TcpSocket m_Socket;
    const char *m_HostName;
    int m_Port;
};

#endif // __CLIENT_H__
