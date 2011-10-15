/**
* @file
* @brief TestTcpServer��cpp�ļ�.
* @author ruoxi
*
* ʵ����TestTcpServer��.
*/

#include "test_tcp_server.h"

/**
* @param port ����������˿�.
* @param logFileName ��־�ļ���.
* @param maxClientNum �ɷ�������ͻ�����, Ĭ��ֵΪ1.
*
* TestTcpServer���캯��. ���ܷ���������˿�, ��־�ļ������ɷ�������ͻ�����.
*/
TestTcpServer::TestTcpServer(int port, const char *logFileName, UINT32 maxClientNum)
:
m_Port(port),
m_LogFileName(logFileName),
m_Logger(logFileName),
m_MaxClientNum(maxClientNum),
m_RunningClientNum(0)
{
    m_TcpSocket = new TcpSocket;
}

TestTcpServer::~TestTcpServer()
{
}

/**
* @return �������.
*
* TestTcpServer��ʼ��. ��ʼ��Socket����, ��ʼ���������TcpSocket.
*/
RC TestTcpServer::Init()
{
    RC rc;

    CHECK_RC(Socket::Init());

    CHECK_RC(m_TcpSocket->Init());

    return rc;
}

/**
* @return �������.
*
* TestTcpServer����. ����������TcpSocket, ����Socket����.
*/
RC TestTcpServer::Shut()
{
    RC rc;

    CHECK_RC(m_TcpSocket->Shut());

    CHECK_RC(Socket::Shut());

    m_Logger.close();

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
RC TestTcpServer::Listen()
{
    RC rc;

    CHECK_RC(m_TcpSocket->Listen(m_Port));

    UINT32 clientNum = 0;

    while (clientNum < m_MaxClientNum)
    {
        TcpSocket *clientSocket = new TcpSocket();

        CHECK_RC(m_TcpSocket->Accept(*clientSocket));

        HANDLE thread;
        ThreadInfo *info = new ThreadInfo;
        info->ThreadId = 0;
        info->Server = this;
        info->ClientSocket = clientSocket;
        m_RunningClientNum++;
        thread = CreateThread(NULL,
            NULL,
            Dispatch,
            (LPVOID)info,
            0,
            &info->ThreadId);
        if(thread == NULL)
        {
            return RC::THREAD_CREATE_ERROR;
        }
        ++clientNum;
    }
    return OK;
}

/**
* @return �������.
*
* �ȴ�ȫ�������߳��˳�.
* �ڷ�������߳����Listen����������, ͨ�����Զ��˳�..
* �����������߳���Ϊ�Ǹ����̵߳����߳�, ��һ����ֹ���˳�, �������з���δ��ɵ��������.
* �ú���ʵ���������̵߳ȴ����з����߳���ɷ���.
* ͨ����¼��ά����ǰ���ڷ���Ŀͻ�����, ���ͻ�����Ϊ0ʱ, ��������.
* ��ʱ���߳̿ɰ�ȫ�˳�.
*/
RC TestTcpServer::Hold()
{
    while (m_RunningClientNum > 0);
    return OK;
}

/**
* @return ��־�ļ���.
*/
const char *TestTcpServer::GetLogFileName()
{
    return m_LogFileName;
}

/**
* @param lparam ʵ������ӦΪThreadInfo, �����߳���Ϣ.
*
* �����߳��ɷ�����. ʵ��Ϊ�����ķ���˳������к���Service�İ�װ����.
* ��Windowsϵͳ���̺߳�������Ϊȫ�ֺ�����̬����, ������Ա����Service����ֱ����Ϊ�̺߳��������̴߳�������.
* ��������ͨ����ʵ�ʵ�thisָ����Ϊ��������ð�װ����, ��ɶ������ĳ�Ա�����ĵ���.
* �ú�������ThreadInfo�е�Server��Ա��Ϊ��thisָ��.
* ������Ȼ����ͨ��ֻ��д�麯��Service��ʵ�־���ķ���˷�����.
*/
DWORD WINAPI TestTcpServer::Dispatch(LPVOID lparam)
{
    ThreadInfo *info = (ThreadInfo *)lparam;

    info->Server->Service(info->ClientSocket, info->ThreadId);

    info->Server->m_RunningClientNum--;

    delete info->ClientSocket;
    delete info;

    return 0;
}
