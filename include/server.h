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

    /** @brief �����������״̬. */
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
    * @brief ����˳������к���.
    * @param clientSocket ������Ŀͻ���Socket.
    * @param threadId �����ڵ��߳�ID.
    * @return �������.
    *
    * ����ķ���˳������к���.
    * �κ�TestTcpServerʵ�����������ú�����һ������ʵ��,
    * ����������ķ���˲�������.
    */
    static DWORD WINAPI Service(LPVOID lparam);

    /** @brief �������TcpSocket. */
    TcpSocket m_Socket;
    /** @brief ����������˿�. */
    int m_Port;
};

#endif // __SERVER_H__
