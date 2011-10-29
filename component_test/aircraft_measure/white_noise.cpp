/**
* @file
* @brief 白噪声类cpp文件.
* @author ruoxi
*
* 实现了白噪声类.
*/

#include "white_noise.h"
#include "wn_config_dlg.h"

WhiteNoise::~WhiteNoise()
{
}

RC WhiteNoise::GetInterface(UINT32 iid, void **iface)
{
    if (CIID_ICOMPONENT == iid)
    {
        *iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_NOISE == iid)
    {
        *iface = static_cast<INoise *>(this);
    }
    else
    {
        *iface = 0;
        return RC::COMPONENT_GETINTERFACE_ERROR;
    }
    return OK;
}

RC WhiteNoise::Config()
{
    // AFX_MANAGE_STATE(AfxGetStaticModuleState());
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CWNConfigDlg dlg(this);
    dlg.DoModal();

    m_Factor = dlg.m_Factor;

    return OK;
}

RC WhiteNoise::Destroy()
{
    delete this;
    return OK;
}

RC WhiteNoise::GetName(LPWSTR *name)
{
    *name = m_Name;
    return OK;
}

RC WhiteNoise::GetAttribute(UINT32 aid, void **attr)
{
    return OK;
}

RC WhiteNoise::SetAttribute(UINT32 aid, void *attr)
{
    return OK;
}

bool WhiteNoise::Validate()
{
    return true;
}

RC WhiteNoise::Affect(Vector &data)
{
    return OK;
}

LPCWSTR WhiteNoise::WhiteNoiseTypeName = TEXT("白噪声");

UINT32 WhiteNoise::WhiteNoiseCount = 0;

WhiteNoise *WhiteNoise::WhiteNoiseFactory()
{
    WhiteNoise *whiteNoise = new WhiteNoise();
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), WhiteNoiseTypeName, WhiteNoiseCount);
    whiteNoise->m_Name = name;
    ++WhiteNoiseCount;
    return whiteNoise;
}