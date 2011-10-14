/**
* @file
* @brief �������MASSERT��cpp�ļ�.
* @author ruoxi
*
* ������Ժ���.
*/

#include "massert.h"
#include <stdio.h>

/**
* @param file �����ļ�.
* @param line �к�.
* @param function ������.
* @param cond �����ж����.
*
* ��ӡ����ʧ����Ϣ.
* �������ļ�, �к�, �������������ж���䰴��ʽ���.
*/
void AssertFail(const char *file, int line, const char *function, const char *cond)
{
    printf("%s: MASSERT(%s) failed at %s line %d\n", function, cond, file, line);
    fflush(stdout);
}
