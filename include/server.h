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

    /** @brief 进入监听服务状态. */
    RC Listen();

private:
    Platform &m_Platform;

    class ServiceThread
    {
    public:
        ServiceThread(TcpSocket *clientSocket);
        ~ServiceThread();

        RC RecvCommand(CC &cc);

    public:
        RC OnLogin();
        RC OnExit();

    private:
        TcpSocket *m_ClientSocket;
    };
    /**
    * @brief 服务端程序运行函数.
    * @param clientSocket 所服务的客户端Socket.
    * @param threadId 其所在的线程ID.
    * @return 结果代码.
    *
    * 抽象的服务端程序运行函数.
    * 任何TestTcpServer实现类必须给出该函数的一个具体实现,
    * 以完成真正的服务端测试运行.
    */
    static DWORD WINAPI Service(LPVOID lparam);

    /** @brief 服务端用TcpSocket. */
    TcpSocket m_Socket;
    /** @brief 服务端主机端口. */
    int m_Port;
};

#endif // __SERVER_H__
