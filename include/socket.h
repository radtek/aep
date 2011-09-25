#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "rc.h"
#include <string>

using namespace std;

class Socket
{
public:
    Socket();
    virtual ~Socket();

    static RC Init();
    static RC Shut();

    virtual RC Recv(void *buf, size_t size) = 0;
    virtual RC Send(const void *buf, size_t size) = 0;

    RC Recv(UINT08 &data);
    RC Send(UINT08 data);

    RC Recv(UINT16 &data);
    RC Send(UINT16 data);

    RC Recv(UINT32 &data);
    RC Send(UINT32 data);

    RC Recv(UINT64 &data);
    RC Send(UINT64 data);

    RC Recv(double &data);
    RC Send(double data);

    RC RecvStr(string &str);
    RC SendStr(const char *str);
};

#endif // __SOCKET_H__
