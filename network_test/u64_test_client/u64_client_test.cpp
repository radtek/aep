/**
* @file
* @brief U64ClientTest类cpp文件.
* @author ruoxi
*
* 实现了U64ClientTest类.
*/

#include "u64_client_test.h"

U64ClientTest::U64ClientTest(const char *testName, TestTcpClient *client)
:
TcpClientTest(testName, client)
{
}

NetworkTest::TestResult U64ClientTest::Check()
{
    TestResult result = PASS;

    ifstream ifs(m_Client->GetLogFileName());
    UINT64 min = UINT64_MAX - UINT16_MAX, max = UINT64_MAX;
    UINT64 data = min;
    while (true)
    {
        UINT64 temp;
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
