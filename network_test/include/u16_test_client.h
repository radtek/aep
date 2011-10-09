#ifndef __U16_TEST_CLIENT_H__
#define __U16_TEST_CLIENT_H__

#include "test_tcp_client.h"

class U16TestClient : public TestTcpClient
{
public:
    U16TestClient(const char *hostName, int port, const char *logFileName, UINT32 id = 0);
    virtual RC Run();
};

#endif // __U16_TEST_CLIENT_H__
