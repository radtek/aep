#include "rc.h"
#include <map>

using namespace std;

static map<INT32, const char *> MakeErrorMap()
{
    map<INT32, const char *> errorMap;
#undef DEFINE_ERROR
#define DEFINE_ERROR(e, msg) errorMap[RC::e] = msg;
#define __USE_ERRORS__
#include "errors.h"
    return errorMap;
}

static map<INT32, const char *> ErrorMap = MakeErrorMap();

RC::RC()
{
    Set(OK);
}

RC::RC(INT32 rc)
{
    Set(rc);
}

RC::RC(const RC &rc)
{
    Set(rc.Get());
}

void RC::Clear()
{
    m_Rc = OK;
}

const RC & RC::operator=(INT32 rc)
{
    Set(rc);
    return *this;
}

const RC & RC::operator=(const RC &rc)
{
    Set(rc);
    return *this;
}

INT32 RC::Get() const
{
    return m_Rc;
}

RC::operator INT32() const
{
    return m_Rc;
}

const char *RC::Message() const
{
    return ErrorMap[m_Rc];
}

void RC::Set(INT32 rc)
{
    m_Rc = rc;
}
