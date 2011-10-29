// model_run_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "model_run_dlg.h"

extern Aircraft *me, *enemy;
extern IAircraft *iMe, *iEnemy;

// CModelRunDlg dialog

IMPLEMENT_DYNAMIC(CModelRunDlg, CDialog)

CModelRunDlg::CModelRunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModelRunDlg::IDD, pParent)
    , m_MeCoordX(0)
    , m_MeCoordY(0)
    , m_MeCoordZ(0)
    , m_EnemyCoordX(0)
    , m_EnemyCoordY(0)
    , m_EnemyCoordZ(0)
    , m_MeVX(0)
    , m_MeVY(0)
    , m_MeVZ(0)
    , m_EnemyVX(0)
    , m_EnemyVY(0)
    , m_EnemyVZ(0)
    , m_T(0)
{
    m_MeCoordX = me->m_StartCoordinate->x;
    m_MeCoordY = me->m_StartCoordinate->y;
    m_MeCoordZ = me->m_StartCoordinate->z;

    m_EnemyCoordX = enemy->m_StartCoordinate->x;
    m_EnemyCoordY = enemy->m_StartCoordinate->y;
    m_EnemyCoordZ = enemy->m_StartCoordinate->z;

    Vector meV, enemyV;
    me->m_Motion->GetCurrentVelocity(meV);
    enemy->m_Motion->GetCurrentVelocity(enemyV);

    m_MeVX = meV.x;
    m_MeVY = meV.y;
    m_MeVZ = meV.z;

    m_EnemyVX = enemyV.x;
    m_EnemyVY = enemyV.y;
    m_EnemyVZ = enemyV.z;

    m_T = 1;
}

CModelRunDlg::~CModelRunDlg()
{
}

void CModelRunDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ME_COORD_X, m_MeCoordX);
    DDX_Text(pDX, IDC_ME_COORD_Y, m_MeCoordY);
    DDX_Text(pDX, IDC_ME_COORD_Z, m_MeCoordZ);
    DDX_Text(pDX, IDC_ENEMY_COORD_X, m_EnemyCoordX);
    DDX_Text(pDX, IDC_ENEMY_COORD_Y, m_EnemyCoordY);
    DDX_Text(pDX, IDC_ENEMY_COORD_Z, m_EnemyCoordZ);
    DDX_Text(pDX, IDC_ME_V_X, m_MeVX);
    DDX_Text(pDX, IDC_ME_V_Y, m_MeVY);
    DDX_Text(pDX, IDC_ME_V_Z, m_MeVZ);
    DDX_Text(pDX, IDC_ENEMY_V_X, m_EnemyVX);
    DDX_Text(pDX, IDC_ENEMY_V_Y, m_EnemyVY);
    DDX_Text(pDX, IDC_ENEMY_V_Z, m_EnemyVZ);
    DDX_Text(pDX, IDC_MODEL_T, m_T);
}


BEGIN_MESSAGE_MAP(CModelRunDlg, CDialog)
    ON_BN_CLICKED(IDC_MODEL_RUN, &CModelRunDlg::OnBnClickedModelRun)
END_MESSAGE_MAP()


// CModelRunDlg message handlers

void CModelRunDlg::OnBnClickedModelRun()
{
    // TODO: Add your control notification handler code here
    iMe->Fly(m_T);
    iEnemy->Fly(m_T);

    m_MeCoordX = me->m_CurrentCoordinate->x;
    m_MeCoordY = me->m_CurrentCoordinate->y;
    m_MeCoordZ = me->m_CurrentCoordinate->z;

    m_EnemyCoordX = enemy->m_CurrentCoordinate->x;
    m_EnemyCoordY = enemy->m_CurrentCoordinate->y;
    m_EnemyCoordZ = enemy->m_CurrentCoordinate->z;

    Vector meV, enemyV;
    me->m_Motion->GetCurrentVelocity(meV);
    enemy->m_Motion->GetCurrentVelocity(enemyV);

    m_MeVX = meV.x;
    m_MeVY = meV.y;
    m_MeVZ = meV.z;

    m_EnemyVX = enemyV.x;
    m_EnemyVY = enemyV.y;
    m_EnemyVZ = enemyV.z;

    UpdateData(FALSE);
}
