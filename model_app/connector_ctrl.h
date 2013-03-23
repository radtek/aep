/**
* @file
* @brief 连接线控件类头文件.
* @author ruoxi
*
* 定义了连接线控件类.
*/

#ifndef __CONNECTOR_CTRL_H__
#define __CONNECTOR_CTRL_H__

class ModelCtrl;
class CModelDoc;

class ConnectorCtrl
{
public:
    ConnectorCtrl(CPoint point = CPoint(0, 0));
    virtual ~ConnectorCtrl();

    virtual UINT32 GetTypeId();

    void Save(CArchive &ar);
    void Load(CArchive &ar, CModelDoc &doc);
    void Export(CArchive &ar);
    ModelCtrl *GetSource();
    ModelCtrl *GetTarget();

public:
    virtual void Draw(CDC *dc);

    enum ConnectorCtrlSelectMode
    {
        CSM_NONE,
        CSM_ALL,
        CSM_START,
        CSM_END,
    };

    ConnectorCtrlSelectMode HitTest(CPoint point);
    void Select(ConnectorCtrlSelectMode selectMode);
    ConnectorCtrlSelectMode GetSelectMode();
    void Move(CPoint point, ModelCtrl *from = NULL);
    void Connect(ModelCtrl *modelCtrl);
    void Disconnect(ModelCtrl *modelCtrl);
    void Disconnect();
    void DisconnectAll();
    void SetAttachPoint(CPoint point);

    // bool Connect();

protected:
    void DrawArrow(CDC *dc, CPoint start, CPoint end, double theta, UINT32 length);

    virtual bool InBound(CPoint point);
    virtual double Distance(CPoint point);
    virtual double DistanceToStart(CPoint point);
    virtual double DistanceToEnd(CPoint point);

protected:
    ModelCtrl *m_Source, *m_Target;
    CPoint m_Start, m_End;

    ConnectorCtrlSelectMode m_CurrentSelectMode;

protected:
    static const UINT32 s_Length = 100;
    static const UINT32 s_Threshold = 5;

public:
    static const UINT32 s_ModelCtrlId = 3;
};

typedef list<ConnectorCtrl *> ConnectorCtrlList;

#endif // __CONNECTOR_CTRL_H__
