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
* @return �������.
*
* �����������״̬. �ܹ�����������1�����ͻ���.
* ���пͻ�������, ��������, �õ��ͻ���Socket.
* Ȼ�󴴽�һ�������߳���ϢThreadInfo, ���߳�ID, ����˼��ͻ���Socket����.
* ��ͨ��ϵͳ���ô�����һ�������߳����ڷ���ÿͻ���.
* ���߳����к���Dispatch, ����ThreadInfo��Ϊ���봫��Dispatch����.
* ����Dispatch����������նԷ���˳������к���Service�ĵ���, ����ÿͻ���.
* �ڷ����˵Ŀͻ��˴򵽿ɷ�������ͻ�������, �����˳�.
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
