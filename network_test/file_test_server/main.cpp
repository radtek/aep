/**
* @file
* @brief TCP������շ��ļ����ܲ���������.
* @author ruoxi
*/

#include "file_test_server.h"
#include "file_server_test.h"
#include "massert.h"

LPCWSTR serverTempFileName = TEXT("file_test_server_temp.txt");

MAKE_SERVER_TEST(FileTestServer, FileServerTest, file_test_server, 1)
