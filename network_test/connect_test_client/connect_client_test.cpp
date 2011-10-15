/**
* @file
* @brief ConnectClientTest类cpp文件.
* @author ruoxi
*
* 实现了ConnectClientTest类.
*/

#include "connect_client_test.h"

ConnectClientTest::ConnectClientTest(const char *testName, TestTcpClient *client)
:
TcpClientTest(testName, client)
{
}

NetworkTest::TestResult ConnectClientTest::Check()
{
    ifstream ifs(m_Client->GetLogFileName());
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
