/**
* @file
* @brief ConnectServerTest类cpp文件.
* @author ruoxi
*
* 实现了ConnectServerTest类.
*/

#include "connect_server_test.h"

ConnectServerTest::ConnectServerTest(const char *testName, TestTcpServer *server)
:
TcpServerTest(testName, server)
{
}

NetworkTest::TestResult ConnectServerTest::Check()
{
    ifstream ifs(m_Server->GetLogFileName());
    string data;
    ifs>>data;
    ifs.close();
    if (data == "Yes!")
    {
        return PASS;
    }
    else
    {
        return FAIL;
    }
}
