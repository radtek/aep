/**
* @file
* @brief ConnectClientTest��ͷ�ļ�.
* @author ruoxi
*
* ������ConnectClientTest��.
*/

#ifndef __CONNECT_CLIENT_TEST_H__
#define __CONNECT_CLIENT_TEST_H__

#include "tcp_client_test.h"

/**
* @class ConnectClientTest
* @brief TCP�ͻ������Ӳ�����.
*
* ConnectClientTest����������TCP�ͻ������ӹ���.
* ����һ�������ÿͻ���������Զ�̷����.
*/
class ConnectClientTest : public TcpClientTest
{
public:
    ConnectClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __CONNECT_CLIENT_TEST_H__
