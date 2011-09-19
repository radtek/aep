#include "test_server.h"
#include "test_client.h"

#define TEST_PORT 10011

DWORD WINAPI ServerThread(LPVOID lparam)
{
    TestServer *server = (TestServer *)lparam;

    server->Service(TEST_PORT);

    return 0;
}

int main(int argc,char* argv[])
{
    TestServer server;
    server.Initialize();

    DWORD threadId;
    HANDLE thread;
    thread = CreateThread(NULL,
        NULL,
        ServerThread,
        (LPVOID)(&server),
        0,
        &threadId);

    if(thread == NULL)
    {
        printf("CreatThread ServiceThread() failed.\n");
    }
    else
    {
        printf("CreateThread OK.\n");
    }

    while (!server.IsListening())
    {
    }

    TestClient client;
    client.Initialize();
    client.Run("rsun-lt1", TEST_PORT);
    server.Stop();
    return 0;
}
