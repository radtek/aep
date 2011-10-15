/**
* @file
* @brief U16TestClient类头文件.
* @author ruoxi
*
* 定义了U16TestClient类.
*/

#ifndef __U16_TEST_CLIENT_H__
#define __U16_TEST_CLIENT_H__

#include "test_tcp_client.h"

/**
* @class U16TestClient
* @brief 测试收发16位无符号类型的TCP客户端.
*
* U16TestClient类是用来测试收发16位无符号类型的客户端.
* 与服务端互相收发一组16位无符号数.
*/
class U16TestClient : public TestTcpClient
{
public:
    U16TestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __U16_TEST_CLIENT_H__
