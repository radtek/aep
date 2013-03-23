/**
* @file
* @brief �����߿ؼ���ͷ�ļ�.
* @author ruoxi
*
* �����������߿ؼ���.
*/

#ifndef __POLY_CONNECTOR_CTRL_H__
#define __POLY_CONNECTOR_CTRL_H__

class ModelCtrl;
class CModelDoc;
class ConnectorCtrl;

class PolyConnectorCtrl : public ConnectorCtrl
{
public:
    PolyConnectorCtrl(CPoint point = CPoint(0, 0));
    virtual ~PolyConnectorCtrl();

public:
    virtual void Draw(CDC *dc);

protected:
    virtual double Distance(CPoint point);
};

#endif // __POLY_CONNECTOR_CTRL_H__
