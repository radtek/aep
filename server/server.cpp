#include "server.h"

Server::Server()
:
m_Platform(Platform::GetInstance())
{
}

Server::~Server()
{
}

RC Server::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_Platform.Init());
    CHECK_RC(m_Socket.Init());

    return rc;
}

RC Server::Shut()
{
    RC rc;

    CHECK_RC(m_Socket.Shut());
    CHECK_RC(m_Platform.Shut());

    CHECK_RC(Socket::Shut());

    return rc;
}

/**
* @return 结果代码.
*
* 进入监听服务状态. 能够监听并服务1或多个客户端.
* 当有客户端连入, 接受连接, 得到客户端Socket.
* 然后创建一个服务线程信息ThreadInfo, 将线程ID, 服务端及客户端Socket填充好.
* 再通过系统调用创建出一个服务线程用于服务该客户端.
* 该线程运行函数Dispatch, 并将ThreadInfo作为参入传入Dispatch函数.
* 并由Dispatch函数完成最终对服务端程序运行函数Service的调用, 服务该客户端.
* 在服务了的客户端打到可服务的最大客户端数后, 函数退出.
*/
RC Server::Listen()
{
    RC rc;

    CHECK_RC(m_Socket.Listen(m_Port));

    while (true)
    {
        TcpSocket *clientSocket = new TcpSocket();

        CHECK_RC(m_Socket.Accept(*clientSocket));

        HANDLE thread;

        thread = CreateThread(NULL,
            NULL,
            Service,
            (LPVOID)clientSocket,
            0,
            0);
        if(thread == NULL)
        {
            return RC::THREAD_CREATE_ERROR;
        }
    }
    return OK;
}

DWORD WINAPI Server::Service(LPVOID lparam)
{
    TcpSocket *clientSocket = (TcpSocket *)lparam;


    clientSocket->Shut();
    delete clientSocket;

    return 0;
}
