/**
* @file
* @brief TCP服务端收发8位无符号类型功能测试主函数.
* @author ruoxi
*/

#include "u08_test_server.h"
#include "u08_server_test.h"
#include "massert.h"

MAKE_SERVER_TEST(U08TestServer, U08ServerTest, u08_test_server, 1)
