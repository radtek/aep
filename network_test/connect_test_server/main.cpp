/**
* @file
* @brief TCP服务端连接功能测试主函数.
* @author ruoxi
*/

#include "connect_test_server.h"
#include "connect_server_test.h"
#include "massert.h"

MAKE_SERVER_TEST(ConnectTestServer, ConnectServerTest, connect_test_server, 1)
