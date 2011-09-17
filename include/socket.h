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

    // These functions are specific to a particular socket implementation.
    virtual void WaitForConnection() {}
    virtual void Recv(void *buf, size_t size) = 0;
    virtual void Send(const void *buf, size_t size) = 0;

    // These functions are common to all socket implementations
    // SockChipCommand RecvCommand();
    // void SendCommand(SockChipCommand Command);

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

    void InstallErrorHandler(ErrorHandlerFunc func, void *args);

protected:
    void CallErrorHandler();

private:
    ErrorHandlerFunc m_ErrorHandler;
    void *m_ErrorHandlerArgs;
};

Socket *CreateSerialSocket(const char *port);
Socket *CreateServerNetSocket(int port);
Socket *CreateClientNetSocket(const char *hostName, int port);

#endif // __SOCKET_H__
