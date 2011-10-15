/**
* @file
* @brief U64TestClient类cpp文件.
* @author ruoxi
*
* 实现了U64TestClient类.
*/

#include "u64_test_client.h"

U64TestClient::U64TestClient(const char *hostName, int port, const char *logFileName, UINT32 id)
:
TestTcpClient(hostName, port, logFileName, id)
{
}

RC U64TestClient::Run()
{
    RC rc;

    printf("[Client] Client %u executing...\n", m_Id);
    UINT64 min = UINT64_MAX - UINT16_MAX, max = UINT64_MAX;
    UINT64 data = min;
    while (true)
    {
        printf("[Client] %u - Sending UINT64: %llu\n", m_Id, data);
        CHECK_RC(m_TcpSocket->Send64(data));
        UINT64 temp;
        CHECK_RC(m_TcpSocket->Recv64(temp));
        printf("[Client] %u - Recieved UINT64: %llu\n", m_Id, temp);
        m_Logger<<temp<<endl;
        if (data == max)
        {
            break;
        }
        ++data;
    }

    return OK;
}
