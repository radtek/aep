/**
* @file
* @brief 连接线控件类头文件.
* @author ruoxi
*
* 定义了连接线控件类.
*/

#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

class ModelCtrl;
class CModelDoc;

class Connector
{
public:
    Connector(CPoint point = CPoint(0, 0));
    virtual ~Connector();

    void Save(CArchive &ar);
    void Load(CArchive &ar, CModelDoc &doc);

public:
    void Draw(CDC *dc);

    enum ConnectorSelectMode
    {
        CSM_NONE,
        CSM_ALL,
        CSM_START,
        CSM_END,
    };

    ConnectorSelectMode HitTest(CPoint point);
    void Select(ConnectorSelectMode selectMode);
    ConnectorSelectMode GetSelectMode();
    void Move(CPoint point, ModelCtrl *from = NULL);
    void Connect(ModelCtrl *modelCtrl);
    void Disconnect();
    void SetAttachPoint(CPoint point);

    bool Connect();

protected:
    bool InBound(CPoint point);
    double Distance(CPoint point);
    double DistanceToStart(CPoint point);
    double DistanceToEnd(CPoint point);

protected:
    ModelCtrl *m_Source, *m_Target;
    CPoint m_Start, m_End;

    ConnectorSelectMode m_CurrentSelectMode;

protected:
    static const UINT32 s_Length = 100;
    static const UINT32 s_Threshold = 5;

public:
    static const UINT32 s_ModelCtrlId = 3;
};

typedef list<Connector *> ConnectorList;

#endif // __CONNECTOR_H__
