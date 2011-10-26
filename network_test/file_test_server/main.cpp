/**
* @file
* @brief TCP服务端收发文件功能测试主函数.
* @author ruoxi
*/

#include "file_test_server.h"
#include "file_server_test.h"
#include "massert.h"

LPCWSTR serverTempFileName = TEXT("file_test_server_temp.txt");

MAKE_SERVER_TEST(FileTestServer, FileServerTest, file_test_server, 1)
