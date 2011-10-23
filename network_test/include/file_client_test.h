/**
* @file
* @brief FileClientTest��ͷ�ļ�.
* @author ruoxi
*
* ������FileClientTest��.
*/

#ifndef __FILE_CLIENT_TEST_H__
#define __FILE_CLIENT_TEST_H__

#include "tcp_client_test.h"

/**
* @class FileClientTest
* @brief TCP�ͻ����շ��ļ�������.
*
* FileClientTest����������TCP�ͻ����շ��ļ�����.
* ����һ�����ļ��ÿͻ����������շ�����.
*/
class FileClientTest : public TcpClientTest
{
public:
    FileClientTest(const char *testName, TestTcpClient *client);
    virtual TestResult Check();
};

#endif // __U64_CLIENT_TEST_H__
