/**
* @file
* @brief U32ServerTest类cpp文件.
* @author ruoxi
*
* 实现了U32ServerTest类.
*/

#include "u32_server_test.h"

U32ServerTest::U32ServerTest(const char *testName, TestTcpServer *server)
:
TcpServerTest(testName, server)
{
}

NetworkTest::TestResult U32ServerTest::Check()
{
    TestResult result = PASS;

    ifstream ifs(m_Server->GetLogFileName());
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
