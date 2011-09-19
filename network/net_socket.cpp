#include "net_socket.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define socklen_t int

#define HANDLE_WS_ERROR(m) \
    m_Error.ErrorCode = WSAGetLastError(); \
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, \
        NULL, \
        m_Error.ErrorCode, \
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), \
        (LPTSTR)&m_Error.ErrorMsg, \
        ERROR_MSG_MAX_LEN, \
        NULL); \
    m_Error.AppendMsg = m; \
    CallErrorHandler((void *)this); \
    return SOCKET_ERROR

#define CHECK_WS_CALL(f, m) \
    if (SOCKET_ERROR == (f)) \
    { \
        HANDLE_WS_ERROR(m); \
    }

int NetSocket::WSInitialize()
{
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2,2), &wsaData);
}

int NetSocket::WSShutdown()
{
    return WSACleanup();
}

NetSocket::NetSocket()
{
}

NetSocket::~NetSocket()
{
}

int NetSocket::Initialize()
{
    m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_Socket == INVALID_SOCKET)
    {
        HANDLE_WS_ERROR("Could not create network socket.");
    }

    int value = 1;
    CHECK_WS_CALL(setsockopt(m_Socket,
                             IPPROTO_TCP,
                             TCP_NODELAY,
                             (const char *)&value,
                             sizeof(value)),
                  "Could not set set TCP_NODELAY on socket.");
    return 0;
}

int NetSocket::Shutdown()
{
    CHECK_WS_CALL(closesocket(m_Socket),
        "Could not close network socket.");
    return 0;
}

int NetSocket::Listen(int port)
{
    SOCKADDR_IN serverSIN;

    // Define local address and port to listen on.
    serverSIN.sin_family = AF_INET;
    serverSIN.sin_port = htons(port);
    serverSIN.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the address "name" to the socket
    CHECK_WS_CALL(bind(m_Socket,
                       (struct sockaddr *)&serverSIN,
                       sizeof(serverSIN)),
                  "Could not bind network socekt.");

    // Listen for a connection; this sets the incoming queue length
    // for remote connections.  Multiple connections aren't req'd.
    CHECK_WS_CALL(listen(m_Socket,
                         1),
                  "Could not listen for a connection");
    return 0;
}

int NetSocket::Connect(const char *hostname, int port)
{   
    SOCKADDR_IN serverSIN;
    struct hostent *host;
    
    host = gethostbyname(hostname);

    if (host == NULL)
    {
        HANDLE_WS_ERROR("Could not find the host ip address!");
    }

    serverSIN.sin_family = AF_INET;
    serverSIN.sin_port = htons(port);
    memcpy(&serverSIN.sin_addr, host->h_addr, host->h_length);
    CHECK_WS_CALL(connect(m_Socket,
                          (struct sockaddr *)&serverSIN,
                          sizeof(serverSIN)),
                  "Could not connect to remote server.");
    return 0;
}

int NetSocket::Accept(Socket &clientSocket)
{
    NetSocket &netClientSocket = dynamic_cast<NetSocket &>(clientSocket);
    SOCKADDR_IN clientSIN;

    int clientSINLen;

    clientSINLen = sizeof(clientSIN);
    netClientSocket.m_Socket = accept(m_Socket,
                                   (struct sockaddr *)&clientSIN,
                                   &clientSINLen);
    if (netClientSocket.m_Socket == INVALID_SOCKET)
    {
        HANDLE_WS_ERROR("Could not accept for a connection.");
    }
    return 0;
}

int NetSocket::Recv(void *buf, size_t size)
{
    size_t totalLen = 0;
    while (totalLen < size)
    {
        int retLen = recv(m_Socket,
                          (char *)buf + totalLen,
                          int(size - totalLen),
                          0);
        if (retLen == SOCKET_ERROR ||
            retLen == 0)
        {
            HANDLE_WS_ERROR("Could not receive data.");
        }

        totalLen += retLen;
    }
    return 0;
}

int NetSocket::Send(const void *buf, size_t size)
{
    size_t totalLen = 0;
    while (totalLen < size)
    {
        int retLen = send(m_Socket,
                          (const char *)buf + totalLen,
                          int(size - totalLen),
                          0);
        if (retLen == SOCKET_ERROR)
        {
            HANDLE_WS_ERROR("Could not send data.");
        }
        totalLen += retLen;
    }
    return 0;
}

const NetError &NetSocket::GetError()
{
    return m_Error;
}
/*
int NetSocket::GetPortNumber()
{
    SOCKADDR_IN serverSIN = {0};
    socklen_t namelen = sizeof(serverSIN);

    int sock_err = getsockname(m_Socket,
                               (struct sockaddr *)&serverSIN,
                               &namelen);
    if (sock_err == SOCKET_ERROR)
    {
        // Error("Could not get port number!");
    }

    return ntohs(serverSIN.sin_port);
}*/
