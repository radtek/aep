/**
* @file
* @brief 加法类cpp文件.
* @author ruoxi
*
* 实现了加法类.
*/

#include "stdafx.h"

#include "image_algorithm.h"
#include "matlab_helper.h"
#include "image_algorithm_dlg.h"
#include "utility.h"

ImageAlgorithm::ImageAlgorithm()
:
m_FromAlgorithmOutputIndex(0)
{
    m_Input1 = new IImageAlgorithmInput1;
    m_Input2 = new IImageAlgorithmInput2;
    m_Output = new IImageAlgorithmOutput(m_OutputCount);
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        m_Width[i] = 0;
        m_Height[i] = 0;
        m_Factor[i] = 0;
    }
}

ImageAlgorithm::~ImageAlgorithm()
{
    delete m_Input1;
    delete m_Input2;
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        if (m_Output->m_Array[i])
        {
            MatLabHelper::DestroyArray(m_Output->m_Array[i]);
        }
    }
    delete m_Output;
}

UINT32 ImageAlgorithm::GetTypeId()
{
    return s_ComponentId;
}

void ImageAlgorithm::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str());

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar << m_Width[i];
        ar << m_Height[i];
        ar << m_Factor[i];
    }

    ar << CString(m_DllFileName.c_str());
    ar << CString(m_FuncName.c_str());

    ar << m_FromAlgorithmOutputIndex;
}

void ImageAlgorithm::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        ar >> m_Width[i];
        ar >> m_Height[i];
        ar >> m_Factor[i];
    }

    ar >> str;
    m_DllFileName = str;
    ar >> str;
    m_FuncName = str;

    ar >> m_FromAlgorithmOutputIndex;
}

void ImageAlgorithm::Destroy()
{
    delete this;
}

void *ImageAlgorithm::GetInterface(UINT32 iid)
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

UINT32 ImageAlgorithm::GetId()
{
    return m_Id;
}

void ImageAlgorithm::SetId(UINT32 id)
{
    m_Id = id;
}

wstring ImageAlgorithm::GetName()
{
    return m_Name;
}

void ImageAlgorithm::SetName(wstring name)
{
    m_Name = name;
}

void ImageAlgorithm::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        attribute.Id = i + AAID_WIDTH1;
        CString name = TEXT("宽度");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_INT;
        attributeList.push_back(attribute);

        attribute.Id = i + AAID_HEIGHT1;
        name = TEXT("高度");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_INT;
        attributeList.push_back(attribute);
    }

    attribute.Id = AAID_DLL_FILE_NAME;
    CString name = TEXT("Dll文件路径");
    attribute.Name = name;
    attribute.Type = Attribute::TYPE_STRING;
    attributeList.push_back(attribute);

    attribute.Id = AAID_FUNC_NAME;
    name = TEXT("函数名");
    attribute.Name = name;
    attribute.Type = Attribute::TYPE_STRING;
    attributeList.push_back(attribute);

    attribute.Id = AAID_FROM_ALGORITHM_OUTPUT_INDEX;
    name = TEXT("从前一算法获得输入ID");
    attribute.Name = name;
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        attribute.Id = i + AAID_FACTOR1;
        CString name = TEXT("算法因子");
        name.AppendFormat(TEXT("%u"), i + 1);
        attribute.Name = name;
        attribute.Type = Attribute::TYPE_DOUBLE;
        attributeList.push_back(attribute);
    }
}

RC ImageAlgorithm::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    for (UINT32 i = AAID_WIDTH1; i <= AAID_WIDTH5; ++i)
    {
        if (aid == i)
        {
            *((UINT32 *)attr) = m_Width[i];
            return rc;
        }
    }

    for (UINT32 i = AAID_HEIGHT1; i <= AAID_HEIGHT5; ++i)
    {
        if (aid == i)
        {
            *((UINT32 *)attr) = m_Height[i - AAID_HEIGHT1];
            return rc;
        }
    }

    if (aid == AAID_DLL_FILE_NAME)
    {
        *((wstring *)attr) = m_DllFileName;
        return rc;
    }

    if (aid == AAID_FUNC_NAME)
    {
        *((wstring *)attr) = m_FuncName;
        return rc;
    }

    if (aid == AAID_FROM_ALGORITHM_OUTPUT_INDEX)
    {
        *((UINT32 *)attr) = m_FromAlgorithmOutputIndex;
        return rc;
    }

    for (UINT32 i = AAID_FACTOR1; i <= AAID_FACTOR5; ++i)
    {
        if (aid == i)
        {
            *((double *)attr) = m_Factor[i - AAID_FACTOR1];
            return rc;
        }
    }

    return RC::COMPONENT_GETATTRIBUTE_ERROR;
}

RC ImageAlgorithm::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    for (UINT32 i = AAID_WIDTH1; i <= AAID_WIDTH5; ++i)
    {
        if (aid == i)
        {
            m_Width[i] = *((UINT32 *)attr);
            return rc;
        }
    }

    for (UINT32 i = AAID_HEIGHT1; i <= AAID_HEIGHT5; ++i)
    {
        if (aid == i)
        {
            m_Height[i - AAID_HEIGHT1] = *((UINT32 *)attr);
            return rc;
        }
    }

    if (aid == AAID_DLL_FILE_NAME)
    {
        m_DllFileName = *((wstring *)attr);
        return rc;
    }

    if (aid == AAID_FUNC_NAME)
    {
        m_FuncName = *((wstring *)attr);
        return rc;
    }

    if (aid == AAID_FROM_ALGORITHM_OUTPUT_INDEX)
    {
        m_FromAlgorithmOutputIndex = *((UINT32 *)attr);
        return rc;
    }

    for (UINT32 i = AAID_FACTOR1; i <= AAID_FACTOR5; ++i)
    {
        if (aid == i)
        {
            m_Factor[i - AAID_FACTOR1] = *((double *)attr);
            return rc;
        }
    }

    return RC::COMPONENT_SETATTRIBUTE_ERROR;
}

bool ImageAlgorithm::Connect(IComponent *component)
{
    return false;
}

IComponent *ImageAlgorithm::Clone()
{
    ImageAlgorithm *imageAlgorithm = new ImageAlgorithm();

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        imageAlgorithm->m_Width[i] = m_Width[i];
        imageAlgorithm->m_Height[i] = m_Height[i];
        imageAlgorithm->m_Factor[i] = m_Factor[i];
    }

    imageAlgorithm->m_DllFileName = m_DllFileName;
    imageAlgorithm->m_FuncName = m_FuncName;

    imageAlgorithm->m_FromAlgorithmOutputIndex = m_FromAlgorithmOutputIndex;

    imageAlgorithm->m_Id = m_Id;
    imageAlgorithm->m_Name = m_Name;

    return imageAlgorithm;
}

void ImageAlgorithm::Reset()
{
    m_Input1->m_Array = 0;
    m_Input2->m_Array = 0;
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        MatLabHelper::DestroyArray(m_Output->m_Array[i]);
    }
    m_Output->Reset();
}

RC ImageAlgorithm::Config()
{
    RC rc;

    CImageAlgorithmDlg dlg;
    dlg.m_Width1 = m_Width[0];
    dlg.m_Width2 = m_Width[1];
    dlg.m_Width3 = m_Width[2];
    dlg.m_Width4 = m_Width[3];
    dlg.m_Width5 = m_Width[4];
    dlg.m_Height1 = m_Height[0];
    dlg.m_Height2 = m_Height[1];
    dlg.m_Height3 = m_Height[2];
    dlg.m_Height4 = m_Height[3];
    dlg.m_Height5 = m_Height[4];
    dlg.m_Factor1 = m_Factor[0];
    dlg.m_Factor2 = m_Factor[1];
    dlg.m_Factor3 = m_Factor[2];
    dlg.m_Factor4 = m_Factor[3];
    dlg.m_Factor5 = m_Factor[4];
    dlg.m_Name = m_Name.c_str();
    dlg.m_FromId = m_FromAlgorithmOutputIndex;
    dlg.m_DllFileName = m_DllFileName.c_str();
    dlg.m_FuncName = m_FuncName.c_str();
    INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
        m_Width[0] = dlg.m_Width1;
        m_Width[1] = dlg.m_Width2;
        m_Width[2] = dlg.m_Width3;
        m_Width[3] = dlg.m_Width4;
        m_Width[4] = dlg.m_Width5;
        m_Height[0] = dlg.m_Height1;
        m_Height[1] = dlg.m_Height2;
        m_Height[2] = dlg.m_Height3;
        m_Height[3] = dlg.m_Height4;
        m_Height[4] = dlg.m_Height5;
        m_Factor[0] = dlg.m_Factor1;
        m_Factor[1] = dlg.m_Factor2;
        m_Factor[2] = dlg.m_Factor3;
        m_Factor[3] = dlg.m_Factor4;
        m_Factor[4] = dlg.m_Factor5;
        m_Name = dlg.m_Name;
        m_FromAlgorithmOutputIndex = dlg.m_FromId;
        m_DllFileName = dlg.m_DllFileName;
        m_FuncName = dlg.m_FuncName;
	}

    return rc;
}

RC ImageAlgorithm::SetInput(IData *input)
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
        m_Input2->m_Array = imageAlgorithmOutput->m_Array[m_FromAlgorithmOutputIndex];
        return OK;
    }

    return RC::COMPONENT_SETINPUT_ERROR;
}

RC ImageAlgorithm::GetOutput(IData *&output)
{
    output = (IData *)(m_Output->GetInterface(CIID_IDATA));

    return OK;
}

RC ImageAlgorithm::Run()
{
    RC rc;

    /*
    if (!ImageAlgorithmFuncInitialize())
    {
        return RC::ALGORITHM_RUN_INITIALIZE_ERROR;
    }
    */

    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        if (m_Output->m_Array[i] != NULL)
        {
            MatLabHelper::DestroyArray(m_Output->m_Array[i]);
        }
        if (m_Width[i] == 0 || m_Height[i] == 0)
        {
            continue;
        }
        m_Output->m_Array[i] = MatLabHelper::CreateDoubleArray(m_Width[i], m_Height[i], (const char *)(0), 0, 0, 0, 0);

        /*
        if (!mlfImageAlgorithmFunc(1, &m_Output->m_Array[i], m_Input1->m_Array, m_Input2->m_Array))
        {
            ImageAlgorithmFuncPrintStackTrace();
            return RC::ALGORITHM_RUN_ERROR;
        }
        */
    }

    vector<Array *> input;
    input.push_back(m_Input1->m_Array);
    input.push_back(m_Input2->m_Array);
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        Array *a = MatLabHelper::CreateDoubleArray(1, 1, &m_Factor[i], 0, 0, 0, 0);
        input.push_back(a);
    }
    vector<Array *> output(m_OutputCount);
    // Array *output[1] = {m_Output->m_Array[i]};
    CHECK_RC(MatLabHelper::RunFunc(m_DllFileName, m_FuncName, output/*&m_Output->m_Array[0]*/, input));
    //memcpy(&m_Output->m_Array[0], &output[0], m_OutputCount * sizeof(Array *));
    for (UINT32 i = 0; i < m_OutputCount; ++i)
    {
        if (m_Output->m_Array[i] != NULL)
        {
            MatLabHelper::DestroyArray(m_Output->m_Array[i]);
        }
        UINT32 x = m_Width[i], y = m_Height[i];
        UINT32 m = mxGetM(output[i]), n = mxGetN(output[i]);
        if (!x)
        {
            x = m;
        }
        if (!y)
        {
            y = n;
        }
        m_Output->m_Array[i] = MatLabHelper::CreateDoubleArray(x, y, mxGetPr(output[i]), m, n, 0, 0);
        MatLabHelper::DestroyArray(input[i + 2]);
        MatLabHelper::DestroyArray(output[i]);
    }

    return rc;
}

ImageAlgorithm *ImageAlgorithm::Factory()
{
    ImageAlgorithm *imageAlgorithm = new ImageAlgorithm;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    imageAlgorithm->m_Name = name;
    ++s_Count;
    return imageAlgorithm;
}

LPCWSTR ImageAlgorithm::s_ComponentName = TEXT("图像算法");

UINT32 ImageAlgorithm::s_Count = 0;
