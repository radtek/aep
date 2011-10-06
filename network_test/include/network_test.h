#ifndef __NETWORK_TEST_H__
#define __NETWORK_TEST_H__

#include "rc.h"

class NetworkTest
{
public:
    NetworkTest(const char *testName);
    virtual ~NetworkTest();

    virtual RC Run() = 0;
    enum TestResult
    {
        PASS,
        FAIL,
    };
    virtual TestResult Check() = 0;

protected:
    const char *m_TestName;
};

#endif // __NETWORK_TEST_H__
