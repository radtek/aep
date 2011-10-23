/**
* @file
* @brief FileServerTest��ͷ�ļ�.
* @author ruoxi
*
* ������FileServerTest��.
*/

#ifndef __FILE_SERVER_TEST_H__
#define __FILE_SERVER_TEST_H__

#include "tcp_server_test.h"

/**
* @class FileServerTest
* @brief TCP������շ��ļ�������.
*
* FileServerTest����������TCP������շ��ļ�����.
* ����һ���շ��ļ��÷������ͻ����շ�����.
*/
class FileServerTest : public TcpServerTest
{
public:
    FileServerTest(const char *testName, TestTcpServer *server);
    virtual TestResult Check();
};

#endif // __FILE_SERVER_TEST_H__
