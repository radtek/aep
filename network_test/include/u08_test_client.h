#ifndef __U08_TEST_CLIENT_H__
#define __U08_TEST_CLIENT_H__

#include "test_tcp_client.h"

class U08TestClient : public TestTcpClient
{
public:
    U08TestClient(UINT32 id);
    virtual RC Run();
private:
    UINT32 m_Id;
};

#endif // __U08_TEST_CLIENT_H__
