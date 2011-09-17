#include "serial_socket.h"

#include <fcntl.h>
#include <io.h>

SerialSocket::SerialSocket(int file)
{
    m_File = file;
}

void SerialSocket::Recv(void *buf, size_t size)
{
    _read(m_File, buf, (int)size);
}

void SerialSocket::Send(const void *buf, size_t size)
{
    _write(m_File, buf, (int)size);
}


Socket *CreateSerialSocket(const char *port)
{
    int file = _open(port, _O_RDWR | _O_BINARY);
    if (file == -1)
        return NULL;
    return new SerialSocket(file);
}
