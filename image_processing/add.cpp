/**
* @file
* @brief 加法类cpp文件.
* @author ruoxi
*
* 实现了加法类.
*/

#include "stdafx.h"

#include "add.h"
#include "matlab_helper.h"
#include "add_config_dlg.h"
#include "add/AddFunc.h"
#include "utility.h"

Add::Add()
:
m_AddFactor(0)
{
    m_Input1 = new IImageAlgorithmInput1;
    m_Input2 = new IImageAlgorithmInput2;
    m_Output1 = new IImageAlgorithmOutput1;
    m_Output2 = new IImageAlgorithmOutput2;
}

Add::~Add()
{
    MatLabHelper::DestroyArray(m_Output1->m_Array);
    MatLabHelper::DestroyArray(m_Output2->m_Array);
    delete m_Input1;
    delete m_Input2;
    delete m_Output1;
    delete m_Output2;
}

UINT32 Add::GetTypeId()
{
    return s_ComponentId;
}

void Add::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << m_AddFactor;
}

void Add::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> m_AddFactor;
}

void Add::Destroy()
{
    delete this;
}

void *Add::GetInterface(UINT32 iid)
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
    else if (CLIENT_CIID_IMAGE_ALGORITHM == iid)
    {
        iface = static_cast<IImageAlgorithm *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 Add::GetId()
{
    return m_Id;
}

void Add::SetId(UINT32 id)
{
    m_Id = id;
}

wstring Add::GetName()
{
    return m_Name;
}

void Add::SetName(wstring name)
{
    m_Name = name;
}

void Add::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_ADD_FACTOR;
    attribute.Name = TEXT("测试参数");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);
}

RC Add::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_ADD_FACTOR:
        *((double *)attr) = m_AddFactor;
        break;
    }

    return rc;
}

RC Add::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_ADD_FACTOR:
        m_AddFactor = *((double *)attr);
        break;
    }

    return rc;
}

bool Add::Connect(IComponent *component)
{
    return false;
}

IComponent *Add::Clone()
{
    Add *add = new Add();
    add->m_AddFactor = m_AddFactor;
    add->m_Id = m_Id;
    add->m_Name = m_Name;
    return add;
}

RC Add::Config()
{
    RC rc;

    CAddConfigDlg dlg;
    dlg.m_AddFactor = m_AddFactor;
    INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
        if (dlg.m_AddFactor > 10)
        {
            Utility::PromptErrorMessage(TEXT("测试参数不能大于10."));
            return RC::COMPONENT_SETATTRIBUTE_ERROR;
        }
        m_AddFactor = dlg.m_AddFactor;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

    return rc;
}

RC Add::SetInput(IData *input)
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

RC Add::GetOutput1(IData *&output)
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

RC Add::GetOutput2(IData *&output)
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

RC Add::Run()
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

    Array *input3 = MatLabHelper::CreateDoubleArray(1, 1, &m_AddFactor);
    m_Output1->m_Array = MatLabHelper::CreateDoubleArray(x1, y1);
    m_Output2->m_Array = MatLabHelper::CreateDoubleArray(x1, y1);

    if (!AddFuncInitialize())
    {
        return RC::ALGORITHM_RUN_INITIALIZE_ERROR;
    }
    if (!mlfAddFunc(1, &m_Output1->m_Array, m_Input1->m_Array, m_Input2->m_Array, input3))
    {
        AddFuncPrintStackTrace();
        return RC::ALGORITHM_RUN_ERROR;
    }
    if (!mlfAddFunc(1, &m_Output2->m_Array, m_Input1->m_Array, m_Input2->m_Array, input3))
    {
        AddFuncPrintStackTrace();
        return RC::ALGORITHM_RUN_ERROR;
    }
    // AddFuncTerminate();
    MatLabHelper::DestroyArray(input3);

    return rc;
}

Add *Add::Factory()
{
    Add *add = new Add;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    add->m_Name = name;
    ++s_Count;
    delete[] name;
    return add;
}

LPCWSTR Add::s_ComponentName = TEXT("加法");

UINT32 Add::s_Count = 0;
