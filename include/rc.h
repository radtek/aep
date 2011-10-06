#ifndef __RC_H__
#define __RC_H__

const INT32 OK = 0;

class RC
{
public:
    enum
    {
        OK = ::OK,
        #undef DEFINE_ERROR
        #define DEFINE_ERROR(e, msg) e,
        #define __USE_ERRORS__
        #include "errors.h"
    };

    RC();
    RC(INT32 rc);
    RC(const RC &rc);

    void Clear();

    const RC & operator=(INT32 rc);
    const RC & operator=(const RC &rc);

    INT32 Get() const;
    operator INT32() const;
    const char * Message() const;

protected:
    void Set(INT32 rc);

private:
    INT32 m_Rc;
};

#define CHECK_RC(f) \
    do \
    { \
        if (OK != (rc = (f))) \
        return rc; \
    } while(0)

#endif // __RC_H__
