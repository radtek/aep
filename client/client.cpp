#include "client.h"

Client::Client()
:
m_Platform(Platform::GetInstance())
{
}

Client::~Client()
{
}

RC Client::Init()
{
    RC rc;

    m_Platform.Init();

    return rc;
}
