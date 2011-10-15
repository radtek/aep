/**
* @file
* @brief U16ClientTest��cpp�ļ�.
* @author ruoxi
*
* ʵ����U16ClientTest��.
*/

#include "u16_client_test.h"

U16ClientTest::U16ClientTest(const char *testName, TestTcpClient *client)
:
TcpClientTest(testName, client)
{
}

NetworkTest::TestResult U16ClientTest::Check()
{
    TestResult result = PASS;

    ifstream ifs(m_Client->GetLogFileName());
    UINT16 min = 0, max = UINT16_MAX;
    UINT32 data = min;
    while (true)
    {
        UINT32 temp;
        ifs>>temp;
        if (temp != data)
        {
            result = FAIL;
            break;
        }
        if (data == max)
        {
            break;
        }
        ++data;
    }
    ifs.close();

    return result;
}
