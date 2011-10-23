/**
* @file
* @brief FileServerTest��cpp�ļ�.
* @author ruoxi
*
* ʵ����FileServerTest��.
*/

#include "file_server_test.h"

extern const char *serverTempFileName;

FileServerTest::FileServerTest(const char *testName, TestTcpServer *server)
:
TcpServerTest(testName, server)
{
}

NetworkTest::TestResult FileServerTest::Check()
{
    FILE *file = fopen(serverTempFileName, "r");
    if (NULL == file)
    {
        return FAIL;
    }
    remove(serverTempFileName);
    return PASS;
}
