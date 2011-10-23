/**
* @file
* @brief TcpSocket类cpp文件.
* @author ruoxi
*
* 实现了TcpSocket类.
*/

#include "tcp_socket.h"
#include <mswsock.h>

TcpSocket::TcpSocket()
{
}

TcpSocket::~TcpSocket()
{
}

/**
* @return 结果代码.
*
* TcpSocket初始化.
* 创建真正的winsock SOCKET对象,
* 并对其设置必要的属性.
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
* @return 结果代码.
*
* TcpSocket清理.
* 关闭真正的winsock SOCKET对象.
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
* @param port 要监听的端口号.
* @return 结果代码.
*
* 绑定该TcpSocket至port端口,
* 之后进入监听状态.
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
* @param hostName 要连接的远程主机名.
* @param port 要监听的端口号.
* @return 结果代码.
*
* 根据远程主机名和端口号获得远程主机地址信息,
* 然后连接至该远程主机.
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
* @param clientSocket 用来存储接受到的客户端TcpSocket.
* @return 结果代码.
*
* 接受一个客户端TcpSocket.
* 在有客户端TcpSocket连接成功后,
* 服务端创建一个用于服务该客户端的TcpSocket,
* 存储至clientSocket.
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
* @param buf 要接收的数据缓冲区指针.
* @param size 要接收的数据字节数.
* @return 结果代码.
*
* 基于TCP协议的字节流接收函数.
* 使用winsock SOCKET对象实现了Socket中的纯虚函数Recv.
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
* @param buf 要发送的数据缓冲区指针.
* @param size 要发送的数据字节数.
* @return 结果代码.
*
* 基于TCP协议的字节流发送函数.
* 使用winsock SOCKET对象实现了Socket中的纯虚函数Send.
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

/**
* @param fileName 将接收到的文件内容保存到的文件名.
* @return 结果代码.
*/
RC TcpSocket::RecvFile(const char *fileName)
{
    RC rc;
    FILE *file = fopen(fileName, "wb");
    if (NULL == file)
    {
        return RC::FILE_OPEN_ERROR;
    }
    UINT32 length;
    CHECK_RC(Recv32(length));
    char *buf = new char[length];
    CHECK_RC(Recv(buf, length));
    if (fwrite(buf, 1, length, file) != length)
    {
        return RC::FILE_WRITE_ERROR;
    }
    delete[] buf;
    fclose(file);
    return rc;
}

/**
* @param fileName 要发送文件的文件名.
* @return 结果代码.
*/

RC TcpSocket::SendFile(const char *fileName)
{
    RC rc;
    UINT32 length = strlen(fileName) + 1;
    wchar_t *wFileName = (wchar_t *)malloc(length * sizeof(wchar_t));
    UINT32 converted;
    mbstowcs_s(&converted, wFileName, length, fileName, _TRUNCATE);
    HANDLE file = CreateFile(
        wFileName,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (file == INVALID_HANDLE_VALUE)
    {
        INT32 e = GetLastError();
        return RC::FILE_OPEN_ERROR;
    }
    length = GetFileSize(file, NULL);
    CHECK_RC(Send32(length));
    if (!TransmitFile(
        m_Socket,
        file,
        0,
        0,
        NULL,
        NULL,
        TF_USE_KERNEL_APC
        ))
    {
        return RC::SOCK_SEND_FILE_ERROR;
    }
    CloseHandle(file);
    return rc;
}
