/**
* @file
* @brief TestTcpClient��ͷ�ļ�.
* @author ruoxi
*
* ������TestTcpClient��.
*/

#ifndef __TEST_TCP_CLIENT_H__
#define __TEST_TCP_CLIENT_H__

#include "tcp_socket.h"
#include <fstream>

using namespace std;

/**
* @class TestTcpClient
* @brief ������TCP�ͻ�����.
*
* TestTcpClient���ǲ�����TCP�ͻ��˻���.
* ʹ��TcpSocket, ������������TCP�����, ����һС�οͻ��˳��򲢼�¼��־.
*/
class TestTcpClient
{
public:
    /** @brief TestTcpClient���캯��. */
    TestTcpClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    /** @brief TestTcpClient��������. */
    virtual ~TestTcpClient();

    /** @brief TestTcpClient��ʼ��. */
    RC Init();
    /** @brief TestTcpClient����. */
    RC Shut();

    /** @brief ������������TCP�����. */
    RC Connect();

    /**
    * @brief �ͻ��˳������к���.
    * @return �������.
    *
    * ����Ŀͻ��˳������к���.
    * �κ�TestTcpClientʵ�����������ú�����һ������ʵ��,
    * ����������Ŀͻ��˲�������.
    */
    virtual RC Run() = 0;

    /** @brief �õ���־�ļ���. */
    const char *GetLogFileName();

protected:
    /** @brief �ͻ�����TcpSocket. */
    TcpSocket *m_TcpSocket;
    /** @brief ������TCP�����������. */
    const char *m_HostName;
    /** @brief ������TCP����������˿�. */
    int m_Port;
    /** @brief ��־�ļ���. */
    const char *m_LogFileName;
    /** @brief ��־�ļ���. */
    ofstream m_Logger;
    /** @brief �ͻ���ID. */
    UINT32 m_Id;
};

#endif // __TEST_TCP_CLIENT_H__
