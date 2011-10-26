/**
* @file
* @brief FileServerTest类cpp文件.
* @author ruoxi
*
* 实现了FileServerTest类.
*/

#include "file_server_test.h"

extern LPCWSTR serverTempFileName;

FileServerTest::FileServerTest(const char *testName, TestTcpServer *server)
:
TcpServerTest(testName, server)
{
}

NetworkTest::TestResult FileServerTest::Check()
{
    FILE *file = _wfopen(serverTempFileName, TEXT("r"));
    if (NULL == file)
    {
        return FAIL;
    }
    _wremove(serverTempFileName);
    return PASS;
}
