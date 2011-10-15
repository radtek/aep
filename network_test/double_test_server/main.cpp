/**
* @file
* @brief TCP服务端收发双精度浮点类型功能测试主函数.
* @author ruoxi
*/

#include "double_test_server.h"
#include "double_server_test.h"
#include "massert.h"

MAKE_SERVER_TEST(DoubleTestServer, DoubleServerTest, double_test_server, 1)
