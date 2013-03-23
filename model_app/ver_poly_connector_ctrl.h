/**
* @file
* @brief 连接线控件类头文件.
* @author ruoxi
*
* 定义了连接线控件类.
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
