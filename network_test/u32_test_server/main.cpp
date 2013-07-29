/**
* @file
* @brief TCP服务端收发32位无符号类型功能测试主函数.
* @author ruoxi
*/

#include "u32_test_server.h"
#include "u32_server_test.h"
#include "massert.h"

MAKE_SERVER_TEST(U32TestServer, U32ServerTest, u32_test_server, 1)
