/**
* @file
* @brief 定义辅助函数的头文件.
* @author ruoxi
*
* 声明辅助函数.
*/

#include "rc.h"
#include "interfaces.h"

#include <string>

using namespace std;

namespace Utility
{
    /** @brief 判断文件是否存在. */
    bool FileExists(LPCWSTR fileName);
    /** @brief 删除指定文件. */
    RC DeleteFile(LPCWSTR fileName);

    /** @brief 弹出信息对话框. */
    void PromptMessage(LPCWSTR msg);
    /** @brief 弹出错误提示对话框. */
    void PromptErrorMessage(LPCWSTR msg);
    /** @brief 弹出最后一条错误的对话框. */
    void PromptLastErrorMessage();

    /** @brief 将宽字符串转化成字符串. */
    string Wstring2String(const wstring &ws);
    /** @brief 将字符串转化成宽字符串. */
    wstring String2Wstring(const string &s);

    /** @brief 判断字符串中是否存在空格. */
    bool ContainSpace(LPCSTR str);
    /** @brief 判断宽字符串中是否存在空格. */
    bool ContainSpace(LPCWSTR str);

    /** @brief 将属性类型转化成字符串. */
    LPCWSTR AttributeTypeToString(Attribute::AttributeType attributeType);
    /** @brief 将字符串转化成属性类型. */
    Attribute::AttributeType StringToAttributeType(wstring str);

    /** @brief 计算点到直线距离. */
    double DistanceToEdge(CPoint p1, CPoint p2, CPoint p);
    /** @brief 计算两点间距离. */
    double DistanceToPoint(CPoint p1, CPoint p2);

    /** @brief 判断目录是否存在. */
    bool DirectoryExists(LPCWSTR pathName);
    /** @brief 去掉文件路径. */
    wstring StripFilePath(LPCWSTR pathName);
};
