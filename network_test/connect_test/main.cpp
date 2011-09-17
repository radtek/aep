#include "test_server.h"
#include "test_client.h"

#define TEST_PORT 1000

int main()
{
    TestServer(TEST_PORT);
    TestClient("rsun-lt1", TEST_PORT);
    return 0;
}
