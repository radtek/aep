/**
* @file
* @brief TcpSocket类头文件.
* @author ruoxi
*
* 定义了TcpSocket类.
*/

#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include "socket.h"
#include <winsock2.h>

/**
* @class TcpSocket
* @brief 基于TCP协议实现的Socket.
* @author ruoxi
*
* TcpSocket类是基于TCP协议实现的Socket.
* 包括创建, 关闭, 监听端口, 连接远程主机, 接受客户端以及在此基础上的字节流的收发.
* 使用winsock的API来实现.
*/
class TcpSocket : public Socket
{
public:
    /** @brief TcpSocket构造函数. */
    TcpSocket();
    /** @brief TcpSocket析构函数. */
    virtual ~TcpSocket();

    /** @brief TcpSocket初始化. */
    virtual RC Init();
    /** @brief TcpSocket清理. */
    virtual RC Shut();

    /** @brief 监听端口. */
    virtual RC Listen(int port);
    /** @brief 连接远程主机. */
    virtual RC Connect(const char *hostName, int port);
    /** @brief 接受一个客户端TcpSocket. */
    virtual RC Accept(TcpSocket &clientSocket);

    /** @brief 基于TCP协议的字节流接收函数. */
    virtual RC Recv(void *buf, size_t size);
    /** @brief 基于TCP协议的字节流发送函数. */
    virtual RC Send(const void *buf, size_t size);

private:
    /** @brief 真正工作的winsock SOCKET对象. */
    SOCKET m_Socket;
};

#endif // __TCP_SOCKET_H__
