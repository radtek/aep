#include "u08_client_test.h"

U08ClientTest::U08ClientTest(const char *testName, TestTcpClient *client)
:
TcpClientTest(testName, client)
{
}

NetworkTest::TestResult U08ClientTest::Check()
{
    TestResult result = PASS;

    ifstream ifs(m_Client->GetLogFileName());
    UINT08 min = 0, max = UINT08_MAX;
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
