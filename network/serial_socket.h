#ifndef __SERIAL_SOCKET_H__
#define __SERIAL_SOCKET_H__

#include "socket.h"

class SerialSocket : public Socket
{
public:
    SerialSocket(int file);

    virtual void Recv(void *buf, size_t size);
    virtual void Send(const void *buf, size_t size);

private:
    int m_File;
};

#endif // __SERIAL_SOCKET_H__
