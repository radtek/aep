/**
* @file
* @brief ConnectTestServer��ͷ�ļ�.
* @author ruoxi
*
* ������ConnectTestServer��.
*/

#ifndef __CONNECT_TEST_SERVER_H__
#define __CONNECT_TEST_SERVER_H__

#include "test_tcp_server.h"

/**
* @class ConnectTestServer
* @brief �������ӵ�TC�����.
*
* ConnectTestServer������������TCP���ӹ��ܵķ����.
* �������ӽ���TCP�ͻ��˲��շ�һС����Ϣ.
*/
class ConnectTestServer : public TestTcpServer
{
public:
    ConnectTestServer(int port, const char *logFileName, UINT32 maxClientNum = 1);
    virtual RC Service(TcpSocket *clientSocket, DWORD threadId = 0);
};

#endif // __CONNECT_TEST_SERVER_H__
