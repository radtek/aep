/**
* @file
* @brief FileClientTest类cpp文件.
* @author ruoxi
*
* 实现了FileClientTest类.
*/

#include "file_client_test.h"

extern const char *clientSendFileName;
extern const char *clientRecvFileName;

FileClientTest::FileClientTest(const char *testName, TestTcpClient *client)
:
TcpClientTest(testName, client)
{
}

NetworkTest::TestResult FileClientTest::Check()
{
    TestResult result = PASS;

    FILE *sendFile = fopen(clientSendFileName, "r"), *recvFile = fopen(clientRecvFileName, "r");
    if (NULL == sendFile || NULL == recvFile)
    {
        return FAIL;
    }

    char sendChar = fgetc(sendFile), recvChar = fgetc(recvFile);
    while (true)
    {
        if (sendChar != recvChar)
        {
            result = FAIL;
            break;
        }
        else if (EOF == sendChar)
        {
            break;
        }
        sendChar = fgetc(sendFile);
        recvChar = fgetc(recvFile);
    }

    fclose(sendFile);
    fclose(recvFile);

    return result;
}
