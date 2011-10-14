/**
* @file
* @brief 包含所有数据类型的头文件.
* @author ruoxi
*
* 明确定义要用到的全部数据类型.
*/

#ifndef __TYPES_H__
#define __TYPES_H__

/** @brief 有符号8位整形. */
typedef signed char INT08;
/** @brief 无符号8位整形. */
typedef unsigned char UINT08;
/** @brief 无符号8位整形的最大值. */
#define UINT08_MAX 0xFF
/** @brief 有符号16位整形. */
typedef short INT16;
/** @brief 无符号16位整形. */
typedef unsigned short UINT16;
/** @brief 无符号16位整形的最大值. */
#define UINT16_MAX 0xFFFF
/** @brief 有符号32位整形. */
typedef int INT32;
/** @brief 无符号32位整形. */
typedef unsigned int UINT32;
/** @brief 无符号32位整形的最大值. */
#define UINT32_MAX 0xFFFFFFFF
/** @brief 有符号64位整形. */
typedef long long INT64;
/** @brief 无符号64位整形. */
typedef unsigned long long UINT64;
/** @brief 无符号64位整形的最大值. */
#define UINT64_MAX 0xFFFFFFFFFFFFFFFF

#endif // __TYPES_H__
