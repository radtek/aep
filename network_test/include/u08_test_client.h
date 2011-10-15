/**
* @file
* @brief U08TestClient类头文件.
* @author ruoxi
*
* 定义了U08TestClient类.
*/

#ifndef __U08_TEST_CLIENT_H__
#define __U08_TEST_CLIENT_H__

#include "test_tcp_client.h"

/**
* @class U08TestClient
* @brief 测试收发8位无符号类型的TCP客户端.
*
* U08TestClient类是用来测试收发8位无符号类型的客户端.
* 与服务端互相收发一组8位无符号数.
*/
class U08TestClient : public TestTcpClient
{
public:
    U08TestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __U08_TEST_CLIENT_H__
