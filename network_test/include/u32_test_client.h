/**
* @file
* @brief U32TestClient类头文件.
* @author ruoxi
*
* 定义了U32TestClient类.
*/

#ifndef __U32_TEST_CLIENT_H__
#define __U32_TEST_CLIENT_H__

#include "test_tcp_client.h"

/**
* @class U32TestClient
* @brief 测试收发32位无符号类型的TCP客户端.
*
* U32TestClient类是用来测试收发32位无符号类型的客户端.
* 与服务端互相收发一组32位无符号数.
*/
class U32TestClient : public TestTcpClient
{
public:
    U32TestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __U32_TEST_CLIENT_H__
