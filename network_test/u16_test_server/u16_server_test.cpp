#include "u16_server_test.h"

U16ServerTest::U16ServerTest(const char *testName, TestTcpServer *server)
:
TcpServerTest(testName, server)
{
}

NetworkTest::TestResult U16ServerTest::Check()
{
    TestResult result = PASS;

    ifstream ifs(m_Server->GetLogFileName());
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
