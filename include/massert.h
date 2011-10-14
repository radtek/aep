/**
* @file
* @brief �������MASSERT��ͷ�ļ�.
* @author ruoxi
*
* �������Ժ�����������Ժ�.
*/

#ifndef __MASSERT_H__
#define __MASSERT_H__

/** @brief ��ӡ����ʧ����Ϣ. */
extern void AssertFail(const char *file, int line, const char *function, const char *cond);

/**
* @brief ���Ժ�.
*
* ����һ���������. ����debug��, �������condΪfalse�Ļ��͵���AssertFail������ӡ����Ĵ����ļ�, �к�, �������������ж����.
* ����release��, ʲô������.
*/
#ifdef _DEBUG
   #define MASSERT(cond) ((void)((cond) || (AssertFail(__FILE__, __LINE__, __FUNCSIG__, #cond), 0)))
#else
   #define MASSERT(cond) ((void)0)
#endif

#endif // __MASSERT_H__
