/**
* @file
* @brief 模型控件类头文件.
* @author ruoxi
*
* 定义了模型控件类.
*/

#ifndef __MODEL_CTRL_H__
#define __MODEL_CTRL_H__

// #include <afxwin.h>

#include <list>

using namespace std;

class CAttributeBar;
class ConnectorCtrl;

class ModelCtrl
{
public:
    ModelCtrl();
    virtual ~ModelCtrl();

    virtual void Save(CArchive &ar) = 0;
    virtual void Load(CArchive &ar) = 0;
    virtual void Export(CArchive &ar) = 0;

public:
    virtual void Draw(CDC *dc) = 0;
    virtual bool HitTest(CPoint point) = 0;
    virtual UINT32 GetId() = 0;
    virtual bool SetId(UINT32 id) = 0;
    virtual void Move(CPoint point) = 0;

    virtual void Select();
    virtual void UnSelect();

    virtual bool Connect(ModelCtrl *modelCtrl) = 0;

    virtual void Config();

public:
    virtual void AddConnectorCtrl(ConnectorCtrl *connectorCtrl);
    virtual void RemoveConnectorCtrl(ConnectorCtrl *connectorCtrl);

    virtual CPoint GetAttachPoint(CPoint point) = 0;

public:
    virtual INT32 Left() = 0;
    virtual INT32 Right() = 0;
    virtual INT32 Top() = 0;
    virtual INT32 Bottom() = 0;
    virtual CPoint Center() = 0;

    virtual CPoint LeftCenter() = 0;
    virtual CPoint RightCenter() = 0;
    virtual CPoint TopCenter() = 0;
    virtual CPoint BottomCenter() = 0;

protected:
    virtual CAttributeBar &GetAttributeBar();
    virtual void UpdateAttributeBar() = 0;
    virtual void ClearAttributeBar() = 0;

protected:
    bool m_IsSelected;
    list<ConnectorCtrl *> m_ConnectorCtrlList;
};

typedef list<ModelCtrl *> ModelCtrlList;

#endif // __MODEL_CTRL_H__
