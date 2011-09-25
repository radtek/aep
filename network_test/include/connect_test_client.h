#ifndef __CONNECT_TEST_CLIENT_H__
#define __CONNECT_TEST_CLIENT_H__

#include "test_tcp_client.h"

class ConnectTestClient : public TestTcpClient
{
public:
    ConnectTestClient(UINT32 id);
    virtual RC Run();
private:
    UINT32 m_Id;
};

#endif // __CONNECT_TEST_CLIENT_H__
