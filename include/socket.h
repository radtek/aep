#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>

using namespace std;

typedef void (* ErrorHandlerFunc)(void *);

// An endian-safe wrapper for a socket, serial port, etc.
// Always uses little endian over the wire.
class Socket
{
public:
    Socket();
    virtual ~Socket();

    virtual int Initialize() = 0;
    virtual int Shutdown() = 0;

    // These functions are specific to a particular socket implementation.
    virtual int Listen(int port) = 0;
    virtual int Connect(const char *hostname, int port) = 0;
    virtual int Accept(Socket &clientSocket) = 0;
    virtual int Recv(void *buf, size_t size) = 0;
    virtual int Send(const void *buf, size_t size) = 0;

    // These functions are common to all socket implementations
    UINT08 Recv08();
    void Send08(UINT08 data);

    UINT16 Recv16();
    void Send16(UINT16 data);

    UINT32 Recv32();
    void Send32(UINT32 data);

    UINT64 Recv64();
    void Send64(UINT64 data);

    double RecvDouble();
    void SendDouble(double data);

    string RecvString();
    void SendString(const char *str);

    void InstallErrorHandler(ErrorHandlerFunc func);

protected:
    void CallErrorHandler(void *socket);

private:
    ErrorHandlerFunc m_ErrorHandler;
};

#endif // __SOCKET_H__
