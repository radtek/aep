/**
* @file
* @brief NetworkTest��ͷ�ļ�.
* @author ruoxi
*
* ������NetworkTest��.
*/

#ifndef __NETWORK_TEST_H__
#define __NETWORK_TEST_H__

#include "rc.h"

/**
* @class NetworkTest
* @brief ���������.
*
* NetworkTest��������������ԵĻ���, �����˲��Ե�ͨ�ù���.
* ��������, �������. ��Ӧ���ܶ����ɼ̳и�����������ʵ��.
*/
class NetworkTest
{
public:
    /** @brief NetworkTest���캯��. */
    NetworkTest(const char *testName);
    /** @brief NetworkTest��������. */
    virtual ~NetworkTest();

    /**
    * @brief �������к���.
    * @return �������.
    *
    * ���������������к���.
    * �κ�NetworkTestʵ�����������ú�����һ������ʵ��,
    * ����������Ĳ����߼�.
    */
    virtual RC Run() = 0;
    /** @brief ���Խ��ö��. */
    enum TestResult
    {
        PASS, /**< ͨ��. */
        FAIL, /**< ʧ��. */
    };
    /**
    * @brief ���Լ�⺯��.
    * @return ���Խ��.
    *
    * �����������Լ�⺯��.
    * �κ�NetworkTestʵ�����������ú�����һ������ʵ��,
    * ����������Ĳ��Լ��, �õ����Խ��.
    */
    virtual TestResult Check() = 0;

protected:
    /** @brief ������. */
    const char *m_TestName;
};

#endif // __NETWORK_TEST_H__
