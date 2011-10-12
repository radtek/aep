/**
* @file
* @brief TcpSocket��ͷ�ļ�.
* @author ruoxi
*
* ������TcpSocket��.
*/

#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include "socket.h"
#include <winsock2.h>

/**
* @class TcpSocket
* @brief ����TCPЭ��ʵ�ֵ�Socket.
* @author ruoxi
*
* TcpSocket���ǻ���TCPЭ��ʵ�ֵ�Socket.
* ��������, �ر�, �����˿�, ����Զ������, ���ܿͻ����Լ��ڴ˻����ϵ��ֽ������շ�.
* ʹ��winsock��API��ʵ��.
*/
class TcpSocket : public Socket
{
public:
    /** @brief TcpSocket���캯��. */
    TcpSocket();
    /** @brief TcpSocket��������. */
    virtual ~TcpSocket();

    /** @brief TcpSocket��ʼ��. */
    virtual RC Init();
    /** @brief TcpSocket����. */
    virtual RC Shut();

    /** @brief �����˿�. */
    virtual RC Listen(int port);
    /** @brief ����Զ������. */
    virtual RC Connect(const char *hostName, int port);
    /** @brief ����һ���ͻ���TcpSocket. */
    virtual RC Accept(TcpSocket &clientSocket);

    /** @brief ����TCPЭ����ֽ������պ���. */
    virtual RC Recv(void *buf, size_t size);
    /** @brief ����TCPЭ����ֽ������ͺ���. */
    virtual RC Send(const void *buf, size_t size);

private:
    /** @brief ����������winsock SOCKET����. */
    SOCKET m_Socket;
};

#endif // __TCP_SOCKET_H__
