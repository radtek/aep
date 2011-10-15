/**
* @file
* @brief NetworkTest类头文件.
* @author ruoxi
*
* 定义了NetworkTest类.
*/

#ifndef __NETWORK_TEST_H__
#define __NETWORK_TEST_H__

#include "rc.h"

/**
* @class NetworkTest
* @brief 网络测试类.
*
* NetworkTest类是所有网络测试的基类, 定义了测试的通用功能.
* 包括运行, 结果检测等. 相应功能都需由继承该类的子类具体实现.
*/
class NetworkTest
{
public:
    /** @brief NetworkTest构造函数. */
    NetworkTest(const char *testName);
    /** @brief NetworkTest析构函数. */
    virtual ~NetworkTest();

    /**
    * @brief 测试运行函数.
    * @return 结果代码.
    *
    * 抽象的网络测试运行函数.
    * 任何NetworkTest实现类必须给出该函数的一个具体实现,
    * 以完成真正的测试逻辑.
    */
    virtual RC Run() = 0;
    /** @brief 测试结果枚举. */
    enum TestResult
    {
        PASS, /**< 通过. */
        FAIL, /**< 失败. */
    };
    /**
    * @brief 测试检测函数.
    * @return 测试结果.
    *
    * 抽象的网络测试检测函数.
    * 任何NetworkTest实现类必须给出该函数的一个具体实现,
    * 以完成真正的测试检测, 得到测试结果.
    */
    virtual TestResult Check() = 0;

protected:
    /** @brief 测试名. */
    const char *m_TestName;
};

#endif // __NETWORK_TEST_H__
