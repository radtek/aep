/**
* @file
* @brief TcpClientTest类头文件.
* @author ruoxi
*
* 定义了TcpClientTest类.
*/

#ifndef __TCP_CLIENT_TEST_H__
#define __TCP_CLIENT_TEST_H__

#include "network_test.h"
#include "test_tcp_client.h"

/**
* @class TcpClientTest
* @brief TCP客户端的测试类.
*
* TcpClientTest类是测试用TCP客户端测试的基类.
* 用来运行一个测试用TCP客户端, 分析运行日志, 检测运行结果.
* 继承自NetworkTest, 可以被继承以实现具体的测试及检测功能
*/
class TcpClientTest : public NetworkTest
{
public:
    /** @brief TcpClientTest构造函数. */
    TcpClientTest(const char *testName, TestTcpClient *client);
    /** @brief TcpClientTest析构函数. */
    virtual ~TcpClientTest();

    /** @brief 用于测试用TCP客户端的测试运行函数. */
    RC Run();

protected:
    /** @brief 测试用TCP客户端. */
    TestTcpClient *m_Client;
};

/**
* @brief 用于定义一个客户端测试程序主函数的宏.
* @param clientClass 客户端的类型.
* @param testClass 客户端测试的类型.
* @param testName 测试名.
* @param id 客户端ID.
*
* 定义一个客户端测试程序主函数.
* 创建测试客户端及客户端测试对象, 调用运行函数并检测结果.
*/
#define MAKE_CLIENT_TEST(clientClass, testClass, testName, id) \
int main(int argc,char* argv[]) \
{ \
    const char *hostName = argv[1]; \
    int port = atoi(argv[2]); \
    clientClass client(hostName, port, #testName".log", id); \
    testClass test(#testName, &client); \
    MASSERT(test.Run() == OK); \
    MASSERT(test.Check() == NetworkTest::PASS); \
    return 0; \
}

#endif // __TCP_CLIENT_TEST_H__
