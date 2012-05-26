/**
* @file
* @brief 批类头文件.
* @author ruoxi
*
* 定义了批类.
*/

#ifndef __BATCH_H__
#define __BATCH_H__

#include "model.h"

class Batch
{
public:
    Batch( Model &model);
    RC Parse(wstring fileName);
    UINT32 GetCount();
    RC Run();
    RC ConfigModel(UINT32 modId);
    RC RunSingleModel(UINT32 modId);

    Model &GetModel();

private:
    UINT32 m_Count;

    class Value
    {
    public:
        Value(wstring value = TEXT(""));
        UINT32 GetUintValue();
        double GetDoubleValue();
        wstring GetStringValue();

    private:
        wstring m_Value;
    };
    typedef map<wstring, Value> AttrList;
    typedef map<wstring, AttrList> CompList;
    typedef map<UINT32, CompList> ModList;

protected:
    virtual RC ParseLine(const wstring &line);

    RC ConfigModel(CompList &compList);
    RC ConfigComponent(IComponent *component, AttrList &attrList);

private:
    Model &m_Model;

    ModList m_ModList;

    wstring m_CurrentComp, m_CurrentAttr;
};

#endif // __BATCH_H__
