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
{
    m_Input1 = new IImageAlgorithmInput1;
    m_Input2 = new IImageAlgorithmInput2;
    m_Output = new IImageAlgorithmOutput(m_OutputCount);
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        m_AddFactor[i] = 0;
    }
}

Add::~Add()
{
    delete m_Input1;
    delete m_Input2;
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        MatLabHelper::DestroyArray(m_Output->m_Array[i]);
    }
    delete m_Output;
}

UINT32 Add::GetTypeId()
{
    return s_ComponentId;
}

void Add::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str());

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar << m_AddFactor[i];
    }
}

void Add::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar >> m_AddFactor[i];
    }
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

    for (UINT32 i = AAID_ADD_FACTOR1; i <= AAID_ADD_FACTOR5; ++i)
    {
        attribute.Id = i;
        CString name = TEXT("加法因子");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_DOUBLE;
        attributeList.push_back(attribute);
    }
}

RC Add::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    for (UINT32 i = AAID_ADD_FACTOR1; i <= AAID_ADD_FACTOR5; ++i)
    {
        if (aid == i)
        {
            *((double *)attr) = m_AddFactor[i];
            return rc;
        }
    }

    return RC::COMPONENT_GETATTRIBUTE_ERROR;
}

RC Add::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    for (UINT32 i = AAID_ADD_FACTOR1; i <= AAID_ADD_FACTOR5; ++i)
    {
        if (aid == i)
        {
            m_AddFactor[i] = *((double *)attr);
            return rc;
        }
    }

    return RC::COMPONENT_SETATTRIBUTE_ERROR;
}

bool Add::Connect(IComponent *component)
{
    return false;
}

IComponent *Add::Clone()
{
    Add *add = new Add();
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        add->m_AddFactor[i] = m_AddFactor[i];
    }
    add->m_Id = m_Id;
    add->m_Name = m_Name;
    return add;
}

void Add::Reset()
{
    m_Input1->m_Array = 0;
    m_Input2->m_Array = 0;
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        MatLabHelper::DestroyArray(m_Output->m_Array[i]);
    }
    m_Output->Reset();
}

RC Add::Config()
{
    RC rc;

    CAddConfigDlg dlg;
    dlg.m_AddFactor1 = m_AddFactor[0];
    dlg.m_AddFactor2 = m_AddFactor[1];
    dlg.m_AddFactor3 = m_AddFactor[2];
    dlg.m_AddFactor4 = m_AddFactor[3];
    dlg.m_AddFactor5 = m_AddFactor[4];
    INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
        m_AddFactor[0] = dlg.m_AddFactor1;
        m_AddFactor[1] = dlg.m_AddFactor2;
        m_AddFactor[2] = dlg.m_AddFactor3;
        m_AddFactor[3] = dlg.m_AddFactor4;
        m_AddFactor[4] = dlg.m_AddFactor5;
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

    IImageAlgorithmOutput *imageAlgorithmOutput = (IImageAlgorithmOutput *)(input->GetInterface(CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT));
    if (NULL != imageAlgorithmOutput)
    {
        m_Input2->m_Array = imageAlgorithmOutput->m_Array[0];
        return OK;
    }

    return RC::COMPONENT_SETINPUT_ERROR;
}

RC Add::GetOutput(IData *&output)
{
    output = (IData *)(m_Output->GetInterface(CIID_IDATA));

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

    if (!AddFuncInitialize())
    {
        return RC::ALGORITHM_RUN_INITIALIZE_ERROR;
    }

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        if (m_Output->m_Array[i] != NULL)
        {
            MatLabHelper::DestroyArray(m_Output->m_Array[i]);
        }
        Array *input3 = MatLabHelper::CreateDoubleArray(1, 1, &m_AddFactor[i]);
        m_Output->m_Array[i] = MatLabHelper::CreateDoubleArray(x1, y1);
        if (!mlfAddFunc(1, &m_Output->m_Array[i], m_Input1->m_Array, m_Input2->m_Array, input3))
        {
            AddFuncPrintStackTrace();
            return RC::ALGORITHM_RUN_ERROR;
        }
        MatLabHelper::DestroyArray(input3);
    }

    // AddFuncTerminate();

    return rc;
}

Add *Add::Factory()
{
    Add *add = new Add;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    add->m_Name = name;
    ++s_Count;
    return add;
}

LPCWSTR Add::s_ComponentName = TEXT("加法");

UINT32 Add::s_Count = 0;
