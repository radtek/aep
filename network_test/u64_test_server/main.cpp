/**
* @file
* @brief TCP服务端收发64位无符号类型功能测试主函数.
* @author ruoxi
*/

#include "u64_test_server.h"
#include "u64_server_test.h"
#include "massert.h"

MAKE_SERVER_TEST(U64TestServer, U64ServerTest, u64_test_server, 1)
