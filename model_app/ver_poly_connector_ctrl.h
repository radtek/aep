/**
* @file
* @brief �����߿ؼ���ͷ�ļ�.
* @author ruoxi
*
* �����������߿ؼ���.
*/

#ifndef __VER_POLY_CONNECTOR_CTRL_H__
#define __VER_POLY_CONNECTOR_CTRL_H__

class ConnectorCtrl;

class VerPolyConnectorCtrl : public ConnectorCtrl
{
public:
    VerPolyConnectorCtrl(CPoint point = CPoint(0, 0));
    virtual ~VerPolyConnectorCtrl();

    virtual UINT32 GetTypeId();

public:
    virtual void Draw(CDC *dc);

protected:
    virtual double Distance(CPoint point);
};

#endif // __VER_POLY_CONNECTOR_CTRL_H__
