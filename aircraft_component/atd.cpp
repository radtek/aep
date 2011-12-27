#include "atd.h"

#include "engine.h"

ATD::ATD()
:
m_Step(0.5),
m_Aircraft(NULL),
m_Target(NULL)
{
}

ATD::~ATD()
{
}

UINT32 ATD::GetTypeId()
{
    return s_ComponentId;
}

void ATD::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << m_Step
        << m_Time;
}

void ATD::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> m_Step >> m_Time;
}

void ATD::Destroy()
{
    delete this;
}

void *ATD::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CIID_IPARAM == iid)
    {
        iface = static_cast<IParam *>(this);
    }
    else if (CLIENT_CIID_REAL_VALUE == iid)
    {
        iface = static_cast<IRealValue *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 ATD::GetId()
{
    return m_Id;
}

void ATD::SetId(UINT32 id)
{
    m_Id = id;
}

wstring ATD::GetName()
{
    return m_Name;
}

void ATD::SetName(wstring name)
{
    m_Name = name;
}

void ATD::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_STEP;
    attribute.Name = TEXT("步长");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);

    attribute.Id = AAID_TIME;
    attribute.Name = TEXT("时间");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);
}

RC ATD::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_STEP:
        *((double *)attr) = m_Step;
        break;
    case AAID_TIME:
        *((double *)attr) = m_Time;
        break;
    }

    return rc;
}

RC ATD::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_STEP:
        m_Step = *((double *)attr);
        break;
    case AAID_TIME:
        m_Time = *((double *)attr);
        break;
    }

    return rc;
}

bool ATD::Connect(IComponent *component)
{
    IAircraft *aircraft = (IAircraft *)component->GetInterface(CLIENT_CIID_AIRCRAFT);
    if (NULL != aircraft)
    {
        m_Aircraft = aircraft;
        return true;
    }

    ITarget *target = (ITarget *)component->GetInterface(CLIENT_CIID_TARGET);
    if (NULL != target)
    {
        m_Target = target;
        return true;
    }

    return false;
}

Param *ATD::ToParam()
{
    Param *param = new vector<double>;

    for (double t = 0; t <= m_Time; t += m_Step)
    {
        Vector aircraftCoordinate = m_Aircraft->GetCurrentCoordinate();
        Vector targetCoordinate = m_Target->GetCurrentCoordinate();

        double d = Distance(aircraftCoordinate, targetCoordinate);
        param->push_back(d);

        m_Aircraft->Fly(m_Step);
        m_Target->Fly(m_Step);
    }
    /*
    double *data = mxGetPr(param);
    data[0] = m_CurrentCoordinate.x;
    data[1] = m_CurrentCoordinate.y;
    data[2] = m_CurrentCoordinate.z;
    data[3] = m_CurrentVelocity.x;
    data[4] = m_CurrentVelocity.y;
    data[5] = m_CurrentVelocity.z;
    data[6] = 0;
    data[7] = 0;
    data[8] = 0;
    */
    return param;
}

UINT32 ATD::GetParamSize()
{
    return 9;
}

RC ATD::DrawFigure()
{
    RC rc;

    Engine *engine;
    if (!(engine = engOpen(NULL)))
    {
        return RC::MODEL_INIT_MATLAB_ENGINE_ERROR;
    }

    Param *param = ToParam();

    mxArray *t = mxCreateDoubleMatrix(1, param->size(), mxREAL);
    mxArray *distance = mxCreateDoubleMatrix(1, param->size(), mxREAL);

    for (UINT32 i = 0; i <= param->size(); ++i)
    {
        mxGetPr(t)[i] = m_Step * i;
    }
    memcpy(mxGetPr(distance), &(*param)[0], param->size() * sizeof(double));

    engPutVariable(engine, "t", t);
    engPutVariable(engine, "distance", distance);

    engEvalString(engine, "plot(t, distance);");

    engClose(engine);

    return rc;
}

ATD *ATD::Factory()
{
    ATD *atd = new ATD;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    atd->m_Name = name;
    ++s_Count;
    delete[] name;
    return atd;
}

LPCWSTR ATD::s_ComponentName = TEXT("飞行器-目标-距离真实值");

UINT32 ATD::s_Count = 0;
