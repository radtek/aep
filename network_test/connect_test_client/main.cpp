/**
* @file
* @brief TCP客户端连接功能测试主函数.
* @author ruoxi
*/

#include "connect_test_client.h"
#include "connect_client_test.h"
#include "massert.h"

MAKE_CLIENT_TEST(ConnectTestClient, ConnectClientTest, connect_test_client, 0)
