#include "server.h"
#include "utility.h"

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

    // FIXME
    m_Port = 10086;

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

        ServiceThread *thread = new ServiceThread(clientSocket);

        HANDLE handle;
        handle = CreateThread(NULL,
            NULL,
            Service,
            (LPVOID)thread,
            0,
            0);
        if(handle == NULL)
        {
            return RC::THREAD_CREATE_ERROR;
        }
    }
    return OK;
}

Server::ServiceThread::ServiceThread(TcpSocket *clientSocket)
:
m_ClientSocket(clientSocket)
{
}

Server::ServiceThread::~ServiceThread()
{
    m_ClientSocket->Shut();
    delete m_ClientSocket;
}

RC Server::ServiceThread::RecvCommand(CC &cc)
{
    return m_ClientSocket->RecvCommand(cc);
}

RC Server::ServiceThread::OnLogin()
{
    // FIXME
    RC rc;

    wstring name, password;
    CHECK_RC(m_ClientSocket->RecvWString(name));
    CHECK_RC(m_ClientSocket->RecvWString(password));

    if (name == TEXT("test"))
    {
        if (password == TEXT("1234"))
        {
            CHECK_RC(m_ClientSocket->SendRC(OK));
        }
        else
        {
            CHECK_RC(m_ClientSocket->SendRC(RC::LOGIN_WRONG_PASSWORD_ERROR));
        }
    }
    else
    {
        CHECK_RC(m_ClientSocket->SendRC(RC::LOGIN_UNEXISTS_USER_ERROR));
    }

    return rc;
}

RC Server::ServiceThread::OnExit()
{
    return OK;
}

DWORD WINAPI Server::Service(LPVOID lparam)
{
    ServiceThread *thread = (ServiceThread *)lparam;

    CC cc;
    while (true)
    {
        RC rc;
        CHECK_RC_MSG_NR(thread->RecvCommand(cc));
        switch (cc.Get())
        {
        case CC::LOGIN_COMMAND:
            thread->OnLogin();
            break;
        case CC::EXIT_COMMAND:
            thread->OnExit();
            break;
        default:
            break;
        }
        if (CC::EXIT_COMMAND == cc.Get())
        {
            break;
        }
    }

    return 0;
}
