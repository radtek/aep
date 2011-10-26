/**
* @file
* @brief TCP客户端收发文件功能测试主函数.
* @author ruoxi
*/

#include "file_test_client.h"
#include "file_client_test.h"
#include "massert.h"

LPCWSTR clientSendFileName = TEXT("file_test_client_send.txt");
LPCWSTR clientRecvFileName = TEXT("file_test_client_recv.txt");

MAKE_CLIENT_TEST(FileTestClient, FileClientTest, file_test_client, 0)
