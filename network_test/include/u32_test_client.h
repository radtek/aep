#ifndef __U32_TEST_CLIENT_H__
#define __U32_TEST_CLIENT_H__

#include "test_tcp_client.h"

class U32TestClient : public TestTcpClient
{
public:
    U32TestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __U32_TEST_CLIENT_H__
