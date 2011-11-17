#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "platform.h"

class Client
{
public:
    Client();
    ~Client();

    RC Init();

private:
    Platform &m_Platform;
};

#endif // __CLIENT_H__
