/**
* @file
* @brief TCP服务端收发16位无符号类型功能测试主函数.
* @author ruoxi
*/

#include "u16_test_server.h"
#include "u16_server_test.h"
#include "massert.h"

MAKE_SERVER_TEST(U16TestServer, U16ServerTest, u16_test_server, 1)
