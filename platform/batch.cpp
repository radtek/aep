#include "batch.h"

#include "utility.h"

#include <algorithm>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Batch::Batch(Model &model)
:
m_Model(model),
m_Count(1)
{
}

RC Batch::Parse(wstring fileName)
{
    RC rc;

    wifstream is(fileName.c_str());
    is.imbue(locale("chs"));

    wstring nextLine = L"";

	while(is || nextLine.length() > 0 )
	{
		// Read an entire line at a time
		wstring line;
		if(nextLine.length() > 0)
		{
			line = nextLine;  // we read ahead; use it now
			nextLine = L"";
		}
		else
		{
			getline(is, line);
		}

        // Extract the key
        CHECK_RC(ParseLine(line));
	}

    is.close();

    return rc;
}

RC Batch::Run()
{
    RC rc;

    for (UINT32 i = 1; i <= m_Count; ++i)
    {
        ModList::iterator it = m_ModList.find(i);
        if (it == m_ModList.end())
        {
            continue;
        }

        CompList &compList = it->second;
        CHECK_RC(ConfigModel(compList));

        CHECK_RC(m_Model.Reset());
        CHECK_RC(m_Model.Run());
    }

    return rc;
}

RC Batch::ParseLine(const wstring &line)
{
    RC rc;

    if (line.empty() || line[0] == TEXT('#'))
    {
        return OK;
    }
    
    wistringstream ist(line);

    wstring key, value;
    ist >> key >> value;

    if (key == TEXT("COUNT"))
    {
        string valueStr = Utility::Wstring2String(value);
        m_Count = atoi(valueStr.c_str());
    }
    else if (key == TEXT("COMP"))
    {
        m_CurrentComp = value;
    }
    else if (key == TEXT("ATTR"))
    {
        m_CurrentAttr = value;
    }
    else
    {
        if (m_CurrentComp.empty() || m_CurrentAttr.empty())
        {
            return RC::BATCH_PARSE_FILE_ERROR;
        }
        string keyStr = Utility::Wstring2String(key);
        UINT32 index = atoi(keyStr.c_str());
        m_ModList[index][m_CurrentComp][m_CurrentAttr] = Value(value);
    }

    return rc;
}

RC Batch::ConfigModel(CompList &compList)
{
    RC rc;

    CompList::iterator it = compList.begin();
    for (; it != compList.end(); ++it)
    {
        wstring name = it->first;
        IComponent *component = m_Model.GetComponentByName(name);
        if (component == NULL)
        {
            return RC::BATCH_CONFIG_MODEL_ERROR;
        }
        AttrList &attrList = it->second;
        CHECK_RC(ConfigComponent(component, attrList));
    }

    return rc;
}

RC Batch::ConfigComponent(IComponent *component, AttrList &attrList)
{
    RC rc;

    AttributeList attributeList;
    component->GetAttributeList(attributeList);
    AttrList::iterator itAttr = attrList.begin();
    for (; itAttr != attrList.end(); ++itAttr)
    {
        wstring name = itAttr->first;
        Attribute attribute;
        bool found = false;
        for (UINT32 i = 0; i < attributeList.size(); ++i)
        {
            attribute = attributeList[i];
            if (attribute.Name == name)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return RC::BATCH_CONFIG_COMPONENT_ERROR;
        }
        Value &value = itAttr->second;
        switch (attribute.Type)
        {
        case Attribute::TYPE_INT:
            {
                UINT32 uintValue = value.GetUintValue();
                CHECK_RC(component->SetAttribute(attribute.Id, (void *)(&uintValue)));
                break;
            }
        case Attribute::TYPE_DOUBLE:
            {
                double doubleValue = value.GetDoubleValue();
                CHECK_RC(component->SetAttribute(attribute.Id, (void *)(&doubleValue)));
                break;
            }
        case Attribute::TYPE_STRING:
            {
                wstring stringValue = value.GetStringValue();
                CHECK_RC(component->SetAttribute(attribute.Id, (void *)(&stringValue)));
                break;
            }
        default:
            return RC::BATCH_CONFIG_COMPONENT_ERROR;
        }
    }

    return rc;
}

Batch::Value::Value(wstring value)
:
m_Value(value)
{
}

UINT32 Batch::Value::GetUintValue()
{
    string value = Utility::Wstring2String(m_Value);
    return atoi(value.c_str());
}

double Batch::Value::GetDoubleValue()
{
    string value = Utility::Wstring2String(m_Value);
    return atof(value.c_str());
}

wstring Batch::Value::GetStringValue()
{
    return m_Value;
}
