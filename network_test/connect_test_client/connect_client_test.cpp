/**
* @file
* @brief ConnectClientTest��cpp�ļ�.
* @author ruoxi
*
* ʵ����ConnectClientTest��.
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
