#include "net_socket.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#define socklen_t int

static void Error(const char *fmt, ...)
{
    static char buffer[1024];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    va_end(ap);

    fprintf(stderr, "Error: %s\n", buffer);
    exit(EXIT_FAILURE);
}

NetSocket::NetSocket()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(1,1), &wsaData);

    m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_Socket == INVALID_SOCKET)
    {
        Error("Could not create network socket!");
    }

    int value = 1;
    int sock_err = setsockopt(m_Socket,
                              IPPROTO_TCP, TCP_NODELAY,
                              (const char *)&value, sizeof(value));
    if (sock_err == SOCKET_ERROR)
    {
        Error("Could not set TCP_NODELAY on socket!");
    }
}

NetSocket::~NetSocket()
{
    closesocket(m_Socket);
    WSACleanup();
}

void NetSocket::Listen(int port)
{
    SOCKADDR_IN serverSockIn;

    // Define local address and port to listen on.
    serverSockIn.sin_family = AF_INET;
    serverSockIn.sin_port = htons(port);
    serverSockIn.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the address "name" to the socket
    int sock_err = bind(m_Socket,
                        (struct sockaddr *)&serverSockIn,
                        sizeof(serverSockIn));
    if (sock_err == SOCKET_ERROR)
    {
        Error("Could not bind network socket!");
        return;
    }

    // Listen for a connection; this sets the incoming queue length
    // for remote connections.  Multiple connections aren't req'd.
    sock_err = listen(m_Socket, 1);
    if (sock_err == SOCKET_ERROR)
    {
        Error("Could not listen for a connection!");
    }
}

void NetSocket::Connect(const char *hostname, int port)
{   
    SOCKADDR_IN serverSockIn;
    struct hostent *host;
    
    host = gethostbyname(hostname);

    if (host == NULL)
    {
        Error("Could not find ip address for %s!", hostname);
    }

    serverSockIn.sin_family = AF_INET;
    serverSockIn.sin_port = htons(port);
    memcpy(&serverSockIn.sin_addr, host->h_addr, host->h_length);
    int sock_err = connect(m_Socket,
                           (struct sockaddr *)&serverSockIn,
                           sizeof(serverSockIn));
    if (sock_err == SOCKET_ERROR)
    {
        Error("Could not connect to remote server!");
    }
}

int NetSocket::GetPortNumber()
{
    SOCKADDR_IN serverSockIn = {0};
    socklen_t namelen = sizeof(serverSockIn);

    int sock_err = getsockname(m_Socket,
                               (struct sockaddr *)&serverSockIn,
                               &namelen);
    if (sock_err == SOCKET_ERROR)
    {
        Error("Could not get port number!");
    }

    return ntohs(serverSockIn.sin_port);
}

void NetSocket::WaitForConnection()
{
    SOCKADDR_IN clientSockIn;
    SOCKET clientSock;

    int clientSockInLen;

    clientSockInLen = sizeof(clientSockIn);
    clientSock = accept(m_Socket,
                        (struct sockaddr *)&clientSockIn,
                        &clientSockInLen);
    if (clientSock == INVALID_SOCKET)
    {
        Error("Could not wait for a connection!");
        return;
    }

    // Throw away the original server socket
    closesocket(m_Socket);
    m_Socket = clientSock;
}

void NetSocket::Recv(void *buf, size_t size)
{
    size_t total_recv_len = 0;
    while (total_recv_len < size)
    {
        int ret_len = recv(m_Socket, (char *)buf+total_recv_len, int(size-total_recv_len), MSG_WAITALL);
        if (ret_len == SOCKET_ERROR)
        {
            CallErrorHandler();
            Error("Could not receive %d bytes!", size);
        }
        else if (ret_len == 0)
        {
            CallErrorHandler();
            Error("Connection closed!");
        }
        total_recv_len += ret_len;
    }

#if VERBOSE_SEND_RECV
    printf("[net] Recieved %d/%lu bytes:", total_recv_len, size);

    if (size == 1)
    {
        printf("\n[net]   %02x", *(UINT08 *)buf);
    }
    else if (size == 2)
    {
        printf("\n[net]   %04x", UINT16(*(UINT16 *)buf));
    }
    else
    {
        UINT32 *ptr = (UINT32 *) buf;

        for (size_t ii = 0; ii < size / 4; ii++)
        {
            if ((ii & 7) == 0) {
                printf("\n[net]  ");
            }
            printf(" %08x", UINT32(ptr[ii]));
        }
    }

    printf("\n");
#endif
}

void NetSocket::Send(const void *buf, size_t size)
{
    size_t total_send_len = 0;
    while (total_send_len < size)
    {
        int ret_len = send(m_Socket, (const char *)buf+total_send_len, int(size-total_send_len), MSG_WAITALL);
        if (ret_len == SOCKET_ERROR)
        {
            CallErrorHandler();
            Error("Could not send %d bytes!", size);
        }
        total_send_len += ret_len;
    }

#if VERBOSE_SEND_RECV
    printf("[net] Sent %d/%lu bytes:", total_send_len, size);

    if (size == 1)
    {
        printf("\n[net]   %02x", *(const UINT08 *)buf);
    }
    else if (size == 2)
    {
        printf("\n[net]   %04x", UINT16(*(const UINT16 *)buf));
    }
    else
    {
        const UINT32 *ptr = (const UINT32 *) buf;

        for (size_t ii = 0; ii < size / 4; ii++)
        {
            if ((ii & 7) == 0) {
                printf("\n[net]  ");
            }
            printf(" %08x", UINT32(ptr[ii]));
        }
    }

    printf("\n");
#endif
}

Socket *CreateServerNetSocket(int port)
{
    NetSocket *pSocket = new NetSocket;
    pSocket->Listen(port);
    return pSocket;
}

Socket *CreateClientNetSocket(const char *hostname, int port)
{
    NetSocket *pSocket = new NetSocket;
    pSocket->Connect(hostname, port);
    return pSocket;
}
