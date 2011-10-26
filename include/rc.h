/**
* @file
* @brief ���������ͷ�ļ�.
* @author ruoxi
*
* ������������RC.
*/

#ifndef __RC_H__
#define __RC_H__

/** @brief ���������0����ΪOK. */
const INT32 OK = 0;

/**
* @class RC
* @brief ���������.
*
* ���������.
* ��ʾ�������н���Ĵ��뼰��Ӧ��Ϣ, �����������д�����뼰��Ӧ��Ϣ.
*/
class RC
{
public:
    /** @brief ���н������Ķ���ö��. */
    enum
    {
        OK = ::OK,
        #undef DEFINE_ERROR
        /** @brief �ض���������������DEFINE_ERROR. */
        #define DEFINE_ERROR(e, msg) e,
        /** @brief ���������������errors.hͷ�ļ��Ŀ���. */
        #define __USE_ERRORS__
        #include "errors.h"
    };

    /** @brief RCĬ�Ϲ��캯��. */
    RC();
    /** @brief ����һ��INT32������RC���캯��. */
    RC(INT32 rc);
    /** @brief RC�������캯��. */
    RC(const RC &rc);

    /** @brief ����������. */
    void Clear();

    /** @brief ��һ��INT32���͸�ֵ��RC�ĸ�ֵ�����. */
    const RC & operator=(INT32 rc);
    /** @brief ��һ��RC���͸�ֵ��RC�ĸ�ֵ�����. */
    const RC & operator=(const RC &rc);

    /** @brief �õ��������. */
    INT32 Get() const;
    /** @brief ת����INT32���͵�ǿ��ת�������. */
    operator INT32() const;
    /** @brief �õ������������ʾ����Ϣ. */
    LPCWSTR Message() const;

protected:
    /** @brief ���ý������. */
    void Set(INT32 rc);

private:
    /** @brief RC�ڲ���INT32��ʾ�����Ľ������. */
    INT32 m_Rc;
};

/** @brief ��⺯�����ص�RC�Ƿ�Ϊ����ĺ�. */
#define CHECK_RC(f) \
    do \
    { \
        if (OK != (rc = (f))) \
        return rc; \
    } while(0)

#endif // __RC_H__
