/**
* @file
* @brief ���帨��������ͷ�ļ�.
* @author ruoxi
*
* ������������.
*/

#include "rc.h"
#include "interfaces.h"

#include <string>

using namespace std;

namespace Utility
{
    /** @brief �ж��ļ��Ƿ����. */
    bool FileExists(LPCWSTR fileName);
    /** @brief ɾ��ָ���ļ�. */
    RC DeleteFile(LPCWSTR fileName);

    /** @brief ������Ϣ�Ի���. */
    void PromptMessage(LPCWSTR msg);
    /** @brief ����������ʾ�Ի���. */
    void PromptErrorMessage(LPCWSTR msg);
    /** @brief �������һ������ĶԻ���. */
    void PromptLastErrorMessage();

    /** @brief �����ַ���ת�����ַ���. */
    string Wstring2String(const wstring &ws);
    /** @brief ���ַ���ת���ɿ��ַ���. */
    wstring String2Wstring(const string &s);

    /** @brief �ж��ַ������Ƿ���ڿո�. */
    bool ContainSpace(LPCSTR str);
    /** @brief �жϿ��ַ������Ƿ���ڿո�. */
    bool ContainSpace(LPCWSTR str);

    /** @brief ����������ת�����ַ���. */
    LPCWSTR AttributeTypeToString(Attribute::AttributeType attributeType);
    /** @brief ���ַ���ת������������. */
    Attribute::AttributeType StringToAttributeType(wstring str);

    /** @brief ����㵽ֱ�߾���. */
    double DistanceToEdge(CPoint p1, CPoint p2, CPoint p);
    /** @brief ������������. */
    double DistanceToPoint(CPoint p1, CPoint p2);

    /** @brief �ж�Ŀ¼�Ƿ����. */
    bool DirectoryExists(LPCWSTR pathName);
    /** @brief ȥ���ļ�·��. */
    wstring StripFilePath(LPCWSTR pathName);

    // bool SaveBmpFile(HBITMAP hBitmap, CString fileName);
    RC SaveBmpFile(CString fileName, UINT32 x, UINT32 y,
        // const char *content,
        const double *content,
        UINT32 widthByte, UINT32 height,
        UINT32 startXByte, UINT32 startY,
        UINT32 depth);

    wstring ModifyPathSpec(const wstring &path, bool addSpec);
    bool CreateDirectoryNested(LPCWSTR dirPath);
    bool CreateFileNested(LPCWSTR filePath);

    wstring GetExtName(const wstring &path, bool withDot = false);
    wstring InsertNumToFileName(const wstring &path, UINT32 num);

    UINT64 GetNS();
    UINT32 GetCpuPercentage();
    UINT32 GetMemoryUsageKB();
    UINT32 GetMaxMemoryUsageKB();

    extern const UINT32 CpuFrequencyMhz;
};
