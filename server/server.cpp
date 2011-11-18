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
