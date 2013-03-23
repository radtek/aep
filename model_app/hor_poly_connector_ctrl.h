/**
* @file
* @brief 连接线控件类头文件.
* @author ruoxi
*
* 定义了连接线控件类.
*/

#ifndef __HOR_POLY_CONNECTOR_CTRL_H__
#define __HOR_POLY_CONNECTOR_CTRL_H__

class ConnectorCtrl;

class HorPolyConnectorCtrl : public ConnectorCtrl
{
public:
    HorPolyConnectorCtrl(CPoint point = CPoint(0, 0));
    virtual ~HorPolyConnectorCtrl();

    virtual UINT32 GetTypeId();

public:
    virtual void Draw(CDC *dc);

protected:
    virtual double Distance(CPoint point);
};

#endif // __HOR_POLY_CONNECTOR_CTRL_H__
