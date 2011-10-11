#include "u64_server_test.h"

U64ServerTest::U64ServerTest(const char *testName, TestTcpServer *server)
:
TcpServerTest(testName, server)
{
}

NetworkTest::TestResult U64ServerTest::Check()
{
    TestResult result = PASS;

    ifstream ifs(m_Server->GetLogFileName());
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
