#include "u08_server_test.h"

U08ServerTest::U08ServerTest(const char *testName, TestTcpServer *server)
:
TcpServerTest(testName, server)
{
}

NetworkTest::TestResult U08ServerTest::Check()
{
    TestResult result = PASS;

    ifstream ifs(m_Server->GetLogFileName());
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
