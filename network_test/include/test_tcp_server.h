/**
* @file
* @brief TestTcpServer��ͷ�ļ�.
* @author ruoxi
*
* ������TestTcpServer��.
*/

#ifndef __TEST_TCP_SERVER_H__
#define __TEST_TCP_SERVER_H__

#include "tcp_socket.h"
#include <fstream>

using namespace std;

/**
* @class TestTcpServer
* @brief ������TCP�������.
*
* TestTcpServer���ǲ�����TCP����˻���.
* ʹ��TcpSocket, ���ܲ�����TCP�ͻ��˵�����, ����һС�η���˳��򲢼�¼��־.
*/
class TestTcpServer
{
public:
    /** @brief TestTcpServer���캯��. */
    TestTcpServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    /** @brief TestTcpServer��������. */
    virtual ~TestTcpServer();

    /** @brief TestTcpServer��ʼ��. */
    RC Init();
    /** @brief TestTcpServer����. */
    RC Shut();

    /** @brief �����������״̬. */
    RC Listen();
    /** @brief �ȴ�ȫ�������߳��˳�. */
    RC Hold();

    /** @brief �õ���־�ļ���. */
    const char *GetLogFileName();

protected:
    /**
    * @class ThreadInfo
    * @brief �����߳���Ϣ.
    *
    * ThreadInfo�Ǵ������˷����̵߳��߳���Ϣ.
    * ��֮�����߳����߳�ID, ���������ķ����ʵ������������Ŀͻ���Socket.
    */
    struct ThreadInfo
    {
        /** @brief �߳�ID. */
        DWORD ThreadId;
        /** @brief �������ķ����ʵ��. */
        TestTcpServer *Server;
        /** @brief ������Ŀͻ���Socket. */
        TcpSocket *ClientSocket;
    };
    /** @brief �����߳��ɷ�����. */
    static DWORD WINAPI Dispatch(LPVOID lparam);
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
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0) = 0;

    /** @brief �������TcpSocket. */
    TcpSocket *m_TcpSocket;
    /** @brief ����������˿�. */
    int m_Port;
    /** @brief �ɷ�������ͻ�����. */
    UINT32 m_MaxClientNum;
    /** @brief ��ǰ�����еĿͻ�����. */
    volatile UINT32 m_RunningClientNum;
    /** @brief ��־�ļ���. */
    const char *m_LogFileName;
    /** @brief ��־�ļ���. */
    ofstream m_Logger;
};

#endif // __TEST_TCP_SERVER_H__
