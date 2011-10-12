#include "tcp_socket.h"

TcpSocket::TcpSocket()
{
}

TcpSocket::~TcpSocket()
{
}

/**
* @return �������.
*
* TcpSocket��ʼ��.
* ����������winsock SOCKET����,
* ���������ñ�Ҫ������.
*/
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

/**
* @return �������.
*
* TcpSocket����.
* �ر�������winsock SOCKET����.
*/
RC TcpSocket::Shut()
{
    if (SOCKET_ERROR == closesocket(m_Socket))
    {
        return RC::SOCK_CLOSE_ERROR;
    }
    return OK;
}

/**
* @param port Ҫ�����Ķ˿ں�.
* @return �������.
*
* �󶨸�TcpSocket��port�˿�,
* ֮��������״̬.
*/
RC TcpSocket::Listen(int port)
{
    SOCKADDR_IN serverSIN;

    serverSIN.sin_family = AF_INET;
    serverSIN.sin_port = htons(port);
    serverSIN.sin_addr.s_addr = htonl(INADDR_ANY);

    if (SOCKET_ERROR == bind(m_Socket,
        (struct sockaddr *)&serverSIN,
        sizeof(serverSIN)))
    {
        return RC::SOCK_BIND_ERROR;
    }

    if (SOCKET_ERROR == listen(m_Socket, 1))
    {
        return RC::SOCK_LISTEN_ERROR;
    }

    return OK;
}

/**
* @param hostName Ҫ���ӵ�Զ��������.
* @param port Ҫ�����Ķ˿ں�.
* @return �������.
*
* ����Զ���������Ͷ˿ںŻ��Զ��������ַ��Ϣ,
* Ȼ����������Զ������.
*/
RC TcpSocket::Connect(const char *hostName, int port)
{   
    SOCKADDR_IN serverSIN;
    struct hostent *host;
    
    host = gethostbyname(hostName);

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

/**
* @param clientSocket �����洢���ܵ��Ŀͻ���TcpSocket.
* @return �������.
*
* ����һ���ͻ���TcpSocket.
* ���пͻ���TcpSocket���ӳɹ���,
* ����˴���һ�����ڷ���ÿͻ��˵�TcpSocket,
* �洢��clientSocket.
*/
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

/**
* @param buf Ҫ���յ����ݻ�����ָ��.
* @param size Ҫ���յ������ֽ���.
* @return �������.
*
* ����TCPЭ����ֽ������պ���.
* ʹ��winsock SOCKET����ʵ����Socket�еĴ��麯��Recv.
*/
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

/**
* @param buf Ҫ���͵����ݻ�����ָ��.
* @param size Ҫ���͵������ֽ���.
* @return �������.
*
* ����TCPЭ����ֽ������ͺ���.
* ʹ��winsock SOCKET����ʵ����Socket�еĴ��麯��Send.
*/
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
