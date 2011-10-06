#include "tcp_socket.h"

TcpSocket::TcpSocket()
{
}

TcpSocket::~TcpSocket()
{
}

RC TcpSocket::Init()
{
    m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_Socket == INVALID_SOCKET)
    {
        return RC::SOCK_CREATE_ERROR;
    }

    int value = 1;
    if (SOCKET_ERROR == setsockopt(m_Socket,
        IPPROTO_TCP,
        TCP_NODELAY,
        (const char *)&value,
        sizeof(value)))
    {
        return RC::SOCK_NODELAY_ERROR;
    }

    return OK;
}

RC TcpSocket::Shut()
{
    if (SOCKET_ERROR == closesocket(m_Socket))
    {
        return RC::SOCK_CLOSE_ERROR;
    }
    return OK;
}

RC TcpSocket::Listen(int port)
{
    SOCKADDR_IN serverSIN;

    // Define local address and port to listen on.
    serverSIN.sin_family = AF_INET;
    serverSIN.sin_port = htons(port);
    serverSIN.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the address "name" to the socket
    if (SOCKET_ERROR == bind(m_Socket,
        (struct sockaddr *)&serverSIN,
        sizeof(serverSIN)))
    {
        return RC::SOCK_BIND_ERROR;
    }

    // Listen for a connection; this sets the incoming queue length
    // for remote connections.  Multiple connections aren't req'd.
    if (SOCKET_ERROR == listen(m_Socket, 1))
    {
        return RC::SOCK_LISTEN_ERROR;
    }

    return OK;
}

RC TcpSocket::Connect(const char *hostname, int port)
{   
    SOCKADDR_IN serverSIN;
    struct hostent *host;
    
    host = gethostbyname(hostname);

    if (host == NULL)
    {
        return RC::SOCK_GETHOSTBYNAME_ERROR;
    }

    serverSIN.sin_family = AF_INET;
    serverSIN.sin_port = htons(port);
    memcpy(&serverSIN.sin_addr, host->h_addr, host->h_length);

    if (SOCKET_ERROR == connect(m_Socket,
        (struct sockaddr *)&serverSIN,
        sizeof(serverSIN)))
    {
        return RC::SOCK_CONNECT_ERROR;
    }

    return OK;
}

RC TcpSocket::Accept(TcpSocket &clientSocket)
{
    SOCKADDR_IN clientSIN;
    int clientSINLen = sizeof(clientSIN);

    clientSocket.m_Socket = accept(m_Socket,
        (struct sockaddr *)&clientSIN,
        &clientSINLen);

    if (clientSocket.m_Socket == INVALID_SOCKET)
    {
        return RC::SOCK_ACCEPT_ERROR;
    }

    return OK;
}

RC TcpSocket::Recv(void *buf, size_t size)
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
            return RC::SOCK_RECV_ERROR;
        }

        totalLen += retLen;
    }
    return OK;
}

RC TcpSocket::Send(const void *buf, size_t size)
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
            return RC::SOCK_SEND_ERROR;
        }
        totalLen += retLen;
    }
    return OK;
}
