/**
* @file
* @brief ConnectServerTest��ͷ�ļ�.
* @author ruoxi
*
* ������ConnectClientTest��.
*/

#ifndef __CONNECT_SERVER_TEST_H__
#define __CONNECT_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class ConnectServerTest
* @brief TCP��������Ӳ�����.
*
* ConnectServerTest����������TCP��������ӹ���.
* ����һ�������÷���˽���Զ�̿ͻ�������.
*/
class ConnectServerTest : public TcpServerTest
{
public:
    ConnectServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __CONNECT_SERVER_TEST_H__
