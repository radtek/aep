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

    RC Recv08(UINT08 &data);
    RC Send08(UINT08 data);

    RC Recv16(UINT16 &data);
    RC Send16(UINT16 data);

    RC Recv32(UINT32 &data);
    RC Send32(UINT32 data);

    RC Recv64(UINT64 &data);
    RC Send64(UINT64 data);

    RC RecvDouble(double &data);
    RC SendDouble(double data);

    RC RecvString(string &str);
    RC SendString(const char *str);

    static int GetLastError();
};

#endif // __SOCKET_H__
