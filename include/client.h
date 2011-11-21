#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "platform.h"
#include "tcp_socket.h"

class Client
{
public:
    ~Client();

    RC Init();
    RC Shut();

    RC Connect();
    RC Disconnect();
    bool IsConnected();

    RC Login(const wstring &name, const wstring &password);
    bool IsLogined();

    RC Register(const wstring &name, const wstring &password);

private:
    Platform &m_Platform;
    TcpSocket m_Socket;
    const char *m_HostName;
    int m_Port;
    bool m_IsConnected;
    bool m_IsLogined;

public:
    static Client &GetInstance();

private:
    Client();
    static Client *s_Instance;
    static bool s_Initialized;
};

#endif // __CLIENT_H__
