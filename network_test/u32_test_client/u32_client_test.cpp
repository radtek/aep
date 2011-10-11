#include "u32_client_test.h"

U32ClientTest::U32ClientTest(const char *testName, TestTcpClient *client)
:
TcpClientTest(testName, client)
{
}

NetworkTest::TestResult U32ClientTest::Check()
{
    TestResult result = PASS;

    ifstream ifs(m_Client->GetLogFileName());
    UINT32 min = UINT32_MAX - UINT16_MAX, max = UINT32_MAX;
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
