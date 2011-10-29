/**
* @file
* @brief 简单比较算法类cpp文件.
* @author ruoxi
*
* 实现了简单比较算法类.
*/

#include "simple_compare_algorithm.h"
#include "aircraft_measure_ifaces.h"
#include "component.h"

#include <afx.h>
#include <math.h>

RC SimpleCompareAlgorithm::GetName(LPWSTR *name)
{
    *name = m_Name;
    return OK;
}

IAircraft *me = NULL, *enemy = NULL;

RC SimpleCompareAlgorithm::Run()
{
    ComponentList componentList;
    Component::GetComponentList(componentList);

    for (UINT32 i = 0; i < componentList.size(); ++i)
    {
        IComponent *component = componentList[i];
        LPWSTR name;
        component->GetName(&name);
        if (CString(TEXT("我机")) == CString(name))
        {
            component->GetInterface(CLIENT_CIID_AIRCRAFT, (void**)&me);
        }
        else if (CString(TEXT("敌机")) == CString(name))
        {
            component->GetInterface(CLIENT_CIID_AIRCRAFT, (void**)&enemy);
        }
    }

    Vector *meCoord, *enemyCoord;
    me->GetAttribute(4, (void**)&meCoord);
    enemy->GetAttribute(4, (void**)&enemyCoord);
    CString cs;
    double dis = sqrt(
        (meCoord->x - enemyCoord->x) * (meCoord->x - enemyCoord->x) + 
        (meCoord->y - enemyCoord->y) * (meCoord->y - enemyCoord->y) + 
        (meCoord->z - enemyCoord->z) * (meCoord->z - enemyCoord->z));
    cs.Format(TEXT("两机距离为：%f"), dis);

    MessageBox(NULL, cs, TEXT("结果"), MB_OK); 

    return OK;
}

LPCWSTR SimpleCompareAlgorithm::SimpleCompareAlgorithmName = TEXT("简单比较算法");
