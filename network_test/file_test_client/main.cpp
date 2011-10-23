/**
* @file
* @brief TCP�ͻ����շ��ļ����ܲ���������.
* @author ruoxi
*/

#include "file_test_client.h"
#include "file_client_test.h"
#include "massert.h"

const char *clientSendFileName = "file_test_client_send.txt";
const char *clientRecvFileName = "file_test_client_recv.txt";

MAKE_CLIENT_TEST(FileTestClient, FileClientTest, file_test_client, 0)
