#include "cc.h"
#include <map>

using namespace std;

static map<INT32, LPCWSTR> MakeCommandMap()
{
    map<INT32, LPCWSTR> commandMap;
    #undef DEFINE_COMMAND
    #define DEFINE_COMMAND(c) commandMap[CC::c] = TEXT(#c);
    #define __USE_COMMANDS__
    #include "commands.h"
    return commandMap;
}

static map<INT32, LPCWSTR> CommandMap = MakeCommandMap();

CC::CC()
{
    Set(UNKNOWN_COMMAND);
}

CC::CC(INT32 cc)
{
    Set(cc);
}

CC::CC(const CC &cc)
{
    Set(cc.Get());
}

void CC::Clear()
{
    m_Cc = UNKNOWN_COMMAND;
}

const CC & CC::operator=(INT32 cc)
{
    Set(cc);
    return *this;
}

const CC & CC::operator=(const CC &cc)
{
    Set(cc);
    return *this;
}

INT32 CC::Get() const
{
    return m_Cc;
}

CC::operator INT32() const
{
    return m_Cc;
}

LPCWSTR CC::Message() const
{
    return CommandMap[m_Cc];
}

void CC::Set(INT32 cc)
{
    m_Cc = cc;
}
