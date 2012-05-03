/**
* @file
* @brief �ӷ���cpp�ļ�.
* @author ruoxi
*
* ʵ���˼ӷ���.
*/

#include "stdafx.h"

#include "add.h"
#include "matlab_helper.h"
#include "add_config_dlg.h"

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
    else if (CLIENT_CIID_IMAGE == iid)
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
    attribute.Name = TEXT("���Բ���");
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
        m_AddFactor = dlg.m_AddFactor;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

    return rc;
}

RC Add::SetInput(IData *data)
{
    if (NULL == data)
    {
        return RC::COMPONENT_SETINPUT_ERROR;
    }

    IExternalDataOutput *externalDataOutput = (IExternalDataOutput *)(data->GetInterface(CLIENT_CIID_EXTERNAL_DATA_OUTPUT));
    if (NULL != externalDataOutput)
    {
        m_Input1->m_Array = externalDataOutput->m_Array;
        return OK;
    }

    IImageOutput *imageOutput = (IImageOutput *)(data->GetInterface(CLIENT_CIID_IMAGE_OUTPUT));
    if (NULL != imageOutput)
    {
        m_Input2->m_Array = imageOutput->m_Array;
        return OK;
    }

    IImageAlgorithmOutput1 *imageAlgorithmOutput1 = (IImageAlgorithmOutput1 *)(data->GetInterface(CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT1));
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

IARC Add::Run()
{
    IARC iarc;

    UINT32 x1 = mxGetM(m_Input1->m_Array);
    UINT32 y1 = mxGetN(m_Input1->m_Array);
    UINT32 x2 = mxGetM(m_Input2->m_Array);
    UINT32 y2 = mxGetN(m_Input2->m_Array);

    if (x1 != x2 || x2 != y2)
    {
        return IARC::ALGORITHM_INPUT_ERROR;
    }

    if (m_Output1 != NULL)
    {
        MatLabHelper::DestroyArray(m_Output1->m_Array);
    }

    if (m_Output2 != NULL)
    {
        MatLabHelper::DestroyArray(m_Output2->m_Array);
    }

    m_Output1->m_Array = MatLabHelper::CreateDoubleArray(x1, y1);
    m_Output2->m_Array = MatLabHelper::CreateDoubleArray(x1, y1);

    return iarc;
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

LPCWSTR Add::s_ComponentName = TEXT("�ӷ�");

UINT32 Add::s_Count = 0;