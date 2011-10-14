/**
* @file
* @brief 定义断言MASSERT的cpp文件.
* @author ruoxi
*
* 定义断言函数.
*/

#include "massert.h"
#include <stdio.h>

/**
* @param file 代码文件.
* @param line 行号.
* @param function 函数名.
* @param cond 条件判断语句.
*
* 打印断言失败信息.
* 将代码文件, 行号, 函数名及条件判断语句按格式输出.
*/
void AssertFail(const char *file, int line, const char *function, const char *cond)
{
    printf("%s: MASSERT(%s) failed at %s line %d\n", function, cond, file, line);
    fflush(stdout);
}
