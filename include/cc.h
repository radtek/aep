#ifndef __CC_H__
#define __CC_H__

class CC
{
public:
    enum
    {
        #undef DEFINE_COMMAND
        #define DEFINE_COMMAND(c) c,
        #define __USE_COMMANDS__
        #include "commands.h"
    };

    CC();
    CC(INT32 cc);
    CC(const CC &cc);

    void Clear();

    const CC & operator=(INT32 cc);
    const CC & operator=(const CC &cc);

    INT32 Get() const;
    operator INT32() const;
    LPCWSTR Message() const;

protected:
    void Set(INT32 cc);

private:
    INT32 m_Cc;
};

#endif // __CC_H__
