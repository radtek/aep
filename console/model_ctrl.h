#include "stdafx.h"

#include "model.h"

class CModelCtrl : public CStatic
{
public:
	CModelCtrl(Model &model);
	~CModelCtrl(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

private:
    Model &m_Model;

    UINT32 m_Width, m_Height;

protected:
    void DrawBackGround(CDC &dc);
};
