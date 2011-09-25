#include "connect_test_server.h"
#include "connect_test_client.h"

#define TEST_PORT 104231

DWORD WINAPI ServerListen(LPVOID lparam)
{
    ConnectTestServer *server = (ConnectTestServer *)lparam;

    server->Listen(TEST_PORT);

    return 0;
}

int main(int argc,char* argv[])
{
    ConnectTestServer server;
    server.Init();

    DWORD threadId;
    HANDLE thread;
    thread = CreateThread(NULL,
        NULL,
        ServerListen,
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

    ConnectTestClient client(0);
    client.Init();
    client.Connect("rsun-lt1", TEST_PORT);
    client.Run();
    server.Stop();
    return 0;
}
