/**
* @file
* @brief U64TestClient类头文件.
* @author ruoxi
*
* 定义了U64TestClient类.
*/

#ifndef __U64_TEST_CLIENT_H__
#define __U64_TEST_CLIENT_H__

#include "test_tcp_client.h"

/**
* @class U64TestClient
* @brief 测试收发64位无符号类型的TCP客户端.
*
* U64TestClient类是用来测试收发64位无符号类型的客户端.
* 与服务端互相收发一组64位无符号数.
*/
class U64TestClient : public TestTcpClient
{
public:
    U64TestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __U64_TEST_CLIENT_H__
