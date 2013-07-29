/**
* @file
* @brief TCP客户端收发64位无符号类型功能测试主函数.
* @author ruoxi
*/

#include "u64_test_client.h"
#include "u64_client_test.h"
#include "massert.h"

MAKE_CLIENT_TEST(U64TestClient, U64ClientTest, u64_test_client, 0)
