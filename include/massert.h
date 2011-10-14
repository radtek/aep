/**
* @file
* @brief 定义断言MASSERT的头文件.
* @author ruoxi
*
* 声明断言函数及定义断言宏.
*/

#ifndef __MASSERT_H__
#define __MASSERT_H__

/** @brief 打印断言失败信息. */
extern void AssertFail(const char *file, int line, const char *function, const char *cond);

/**
* @brief 断言宏.
*
* 接受一个条件语句. 对于debug版, 如果条件cond为false的话就调用AssertFail函数打印出错的代码文件, 行号, 函数名及条件判断语句.
* 对于release版, 什么都不做.
*/
#ifdef _DEBUG
   #define MASSERT(cond) ((void)((cond) || (AssertFail(__FILE__, __LINE__, __FUNCSIG__, #cond), 0)))
#else
   #define MASSERT(cond) ((void)0)
#endif

#endif // __MASSERT_H__
