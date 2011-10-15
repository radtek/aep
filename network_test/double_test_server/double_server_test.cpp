#include "double_server_test.h"
#include <math.h>

DoubleServerTest::DoubleServerTest(const char *testName, TestTcpServer *server)
:
TcpServerTest(testName, server)
{
}

NetworkTest::TestResult DoubleServerTest::Check()
{
    TestResult result = PASS;

    ifstream ifs(m_Server->GetLogFileName());
    UINT32 digitNumMin = 1, digitNumMax = 5;
    for (UINT32 digitNum = digitNumMin; digitNum <= digitNumMax; ++digitNum)
    {
        double step = 1.1, positiveBase = 1, minusBase = 0.1;
        for (UINT32 digit = 1; digit < digitNum; ++digit)
        {
            positiveBase *= 10;
            minusBase /= 10;
            step += positiveBase + minusBase;
        }

        double data = step;
        for (UINT32 i = 0; i < 9; data += step, ++i)
        {
            double temp;
            ifs>>temp;
            if (temp - data > minusBase / 10)
            {
                result = FAIL;
                break;
            }
        }
    }
    ifs.close();

    return result;
}
