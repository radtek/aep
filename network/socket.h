#ifndef __SOCKET_H__
#define __SOCKET_H__

typedef void (* ErrorHandlerFunc)(void *);

// An endian-safe wrapper for a socket, serial port, etc.
// Always uses little endian over the wire.
class Socket
{
public:
    Socket();

    // These functions are specific to a particular socket implementation.
    virtual void WaitForConnection() {}
    virtual void Recv(void *Buf, size_t Size) = 0;
    virtual void Send(const void *Buf, size_t Size) = 0;

    // These functions are common to all socket implementations
    // SockChipCommand RecvCommand();
    // void SendCommand(SockChipCommand Command);

    UINT08 Recv08();
    void Send08(UINT08 Data);

    UINT16 Recv16();
    void Send16(UINT16 Data);

    NvU032 Recv32();
    void Send32(NvU032 Data);

    UINT64 Recv64();
    void Send64(UINT64 Data);

    double RecvDouble();
    void SendDouble(double Data);

    string RecvString();
    void SendString(const char *Str);

    void InstallErrorHandler(ErrorHandlerFunc Function, void *Args);

protected:
    void CallErrorHandler();

private:
    ErrorHandlerFunc ErrorHandler;
    void *ErrorHandlerArgs;
};

Socket *CreateSerialSocket(const char *Port);
Socket *CreateServerNetSocket(int Port);
Socket *CreateServerNetSocket(const char *Filename, int SessionID);
Socket *CreateClientNetSocket(const char *Hostname, int Port);

#endif // __SOCKET_H__
