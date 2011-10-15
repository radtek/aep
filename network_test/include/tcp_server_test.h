/**
* @file
* @brief TcpServerTest类头文件.
* @author ruoxi
*
* 定义了TcpServerTest类.
*/

#ifndef __TCP_SERVER_TEST_H__
#define __TCP_SERVER_TEST_H__

#include "network_test.h"
#include "test_tcp_server.h"

/**
* @class TcpServerTest
* @brief TCP服务端的测试类.
*
* TcpServerTest类是测试用TCP服务端测试的基类.
* 用来运行一个测试用TCP服务端, 分析运行日志, 检测运行结果.
* 继承自NetworkTest, 可以被继承以实现具体的测试及检测功能
*/
class TcpServerTest : public NetworkTest
{
public:
    /** @brief TcpServerTest构造函数. */
    TcpServerTest(const char *testName, TestTcpServer *server);
    /** @brief TcpServerTest析构函数. */
    virtual ~TcpServerTest();

    /** @brief 用于测试用TCP服务端的测试运行函数. */
    virtual RC Run();

protected:
    /** @brief 测试用TCP服务端. */
    TestTcpServer *m_Server;
};

/**
* @brief 用于定义一个服务端测试程序主函数的宏.
* @param serverClass 服务端的类型.
* @param testClass 服务端测试的类型.
* @param testName 测试名.
* @param maxClientNum 可服务的最大客户端数.
*
* 定义一个服务端测试程序主函数.
* 创建测试服务端及服务端测试对象, 调用运行函数并检测结果.
*/
#define MAKE_SERVER_TEST(serverClass, testClass, testName, maxClientNum) \
int main(int argc,char* argv[]) \
{ \
    int port = atoi(argv[1]); \
    serverClass server(port, #testName".log", maxClientNum); \
    testClass test(#testName, &server); \
    MASSERT(test.Run() == OK); \
    MASSERT(test.Check() == NetworkTest::PASS); \
    return 0; \
}

#endif // __TCP_SERVER_TEST_H__
