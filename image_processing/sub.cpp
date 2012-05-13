/**
* @file
* @brief 减法类cpp文件.
* @author ruoxi
*
* 实现了减法类.
*/

#include "stdafx.h"

#include "sub.h"
#include "matlab_helper.h"
#include "sub_config_dlg.h"
#include "sub/SubFunc.h"
#include "utility.h"

Sub::Sub()
:
m_SubFactor(0)
{
    m_Input1 = new IImageAlgorithmInput1;
    m_Input2 = new IImageAlgorithmInput2;
    m_Output1 = new IImageAlgorithmOutput1;
    m_Output2 = new IImageAlgorithmOutput2;
}

Sub::~Sub()
{
    MatLabHelper::DestroyArray(m_Output1->m_Array);
    MatLabHelper::DestroyArray(m_Output2->m_Array);
    delete m_Input1;
    delete m_Input2;
    delete m_Output1;
    delete m_Output2;
}

UINT32 Sub::GetTypeId()
{
    return s_ComponentId;
}

void Sub::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << m_SubFactor;
}

void Sub::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> m_SubFactor;
}

void Sub::Destroy()
{
    delete this;
}

void *Sub::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CIID_IALGORITHM == iid)
    {
        iface = static_cast<IAlgorithm *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 Sub::GetId()
{
    return m_Id;
}

void Sub::SetId(UINT32 id)
{
    m_Id = id;
}

wstring Sub::GetName()
{
    return m_Name;
}

void Sub::SetName(wstring name)
{
    m_Name = name;
}

void Sub::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_SUB_FACTOR;
    attribute.Name = TEXT("测试参数");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);
}

RC Sub::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_SUB_FACTOR:
        *((double *)attr) = m_SubFactor;
        break;
    }

    return rc;
}

RC Sub::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_SUB_FACTOR:
        m_SubFactor = *((double *)attr);
        break;
    }

    return rc;
}

bool Sub::Connect(IComponent *component)
{
    return false;
}

RC Sub::Config()
{
    RC rc;

    CSubConfigDlg dlg;
    dlg.m_SubFactor = m_SubFactor;
    INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
        if (dlg.m_SubFactor > 10)
        {
            Utility::PromptErrorMessage(TEXT("测试参数不能大于10."));
            return RC::COMPONENT_SETATTRIBUTE_ERROR;
        }
        m_SubFactor = dlg.m_SubFactor;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

    return rc;
}

IComponent *Sub::Clone()
{
    Sub *sub = new Sub();
    sub->m_SubFactor = m_SubFactor;
    sub->m_Id = m_Id;
    sub->m_Name = m_Name;
    return sub;
}

RC Sub::SetInput(IData *input)
{
    if (NULL == input)
    {
        return RC::COMPONENT_SETINPUT_ERROR;
    }

    IExternalDataOutput *externalDataOutput = (IExternalDataOutput *)(input->GetInterface(CLIENT_CIID_EXTERNAL_DATA_OUTPUT));
    if (NULL != externalDataOutput)
    {
        m_Input1->m_Array = externalDataOutput->m_Array;
        return OK;
    }

    IImageOutput *imageOutput = (IImageOutput *)(input->GetInterface(CLIENT_CIID_IMAGE_OUTPUT));
    if (NULL != imageOutput)
    {
        m_Input2->m_Array = imageOutput->m_Array;
        return OK;
    }

    IImageAlgorithmOutput1 *imageAlgorithmOutput1 = (IImageAlgorithmOutput1 *)(input->GetInterface(CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT1));
    if (NULL != imageAlgorithmOutput1)
    {
        m_Input2->m_Array = imageAlgorithmOutput1->m_Array;
        return OK;
    }

    return RC::COMPONENT_SETINPUT_ERROR;
}

RC Sub::GetOutput1(IData *&output)
{
    if (NULL == m_Output1)
    {
        output = NULL;
        return RC::COMPONENT_GETOUTPUT_ERROR;
    }

    output = (IData *)(m_Output1->GetInterface(CIID_IDATA));
    if (NULL == output)
    {
        return RC::COMPONENT_GETOUTPUT_ERROR;
    }

    return OK;
}

RC Sub::GetOutput2(IData *&output)
{
    if (NULL == m_Output2)
    {
        output = NULL;
        return RC::COMPONENT_GETOUTPUT_ERROR;
    }

    output = (IData *)(m_Output2->GetInterface(CIID_IDATA));
    if (NULL == output)
    {
        return RC::COMPONENT_GETOUTPUT_ERROR;
    }

    return OK;
}

RC Sub::Run()
{
    RC rc;

    UINT32 x1 = mxGetM(m_Input1->m_Array);
    UINT32 y1 = mxGetN(m_Input1->m_Array);
    UINT32 x2 = mxGetM(m_Input2->m_Array);
    UINT32 y2 = mxGetN(m_Input2->m_Array);

    if (x1 != x2 || y1 != y2)
    {
        return RC::ALGORITHM_INPUT_ERROR;
    }

    if (m_Output1->m_Array != NULL)
    {
        MatLabHelper::DestroyArray(m_Output1->m_Array);
    }

    if (m_Output2->m_Array != NULL)
    {
        MatLabHelper::DestroyArray(m_Output2->m_Array);
    }

    Array *input3 = MatLabHelper::CreateDoubleArray(1, 1, &m_SubFactor);
    m_Output1->m_Array = MatLabHelper::CreateDoubleArray(x1, y1);
    m_Output2->m_Array = MatLabHelper::CreateDoubleArray(x1, y1);

    if (!SubFuncInitialize())
    {
        return RC::ALGORITHM_RUN_INITIALIZE_ERROR;
    }
    if (!mlfSubFunc(1, &m_Output1->m_Array, m_Input2->m_Array, m_Input1->m_Array, input3))
    {
        SubFuncPrintStackTrace();
        return RC::ALGORITHM_RUN_ERROR;
    }
    if (!mlfSubFunc(1, &m_Output2->m_Array, m_Input2->m_Array, m_Input1->m_Array, input3))
    {
        SubFuncPrintStackTrace();
        return RC::ALGORITHM_RUN_ERROR;
    }
    // SubFuncTerminate();
    MatLabHelper::DestroyArray(input3);

    return rc;
}

Sub *Sub::Factory()
{
    Sub *sub = new Sub;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    sub->m_Name = name;
    ++s_Count;
    delete[] name;
    return sub;
}

LPCWSTR Sub::s_ComponentName = TEXT("减法");

UINT32 Sub::s_Count = 0;
