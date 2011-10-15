/**
* @file
* @brief DoubleTestClient类cpp文件.
* @author ruoxi
*
* 实现了DoubleTestClient类.
*/

#include "double_test_client.h"
#include <iomanip>
#include <math.h>

DoubleTestClient::DoubleTestClient(const char *hostName, int port, const char *logFileName, UINT32 id)
:
TestTcpClient(hostName, port, logFileName, id)
{
}

RC DoubleTestClient::Run()
{
    RC rc;

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
            printf("[Client] %u - Sending double: %f\n", m_Id, data);
            CHECK_RC(m_TcpSocket->SendDouble(data));
            double temp;
            CHECK_RC(m_TcpSocket->RecvDouble(temp));
            printf("[Client] %u - Recieved double: %f\n", m_Id, temp);
            m_Logger<<setprecision(digitNumMax * 2)<<temp<<endl;
        }
    }

    return OK;
}
