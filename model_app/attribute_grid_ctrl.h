/**
* @file
* @brief ���Ա��ؼ���ͷ�ļ�.
* @author ruoxi
*
* ���������Ա��ؼ���.
*/

#ifndef __ATTRIBUTE_GRID_CTRL_H__
#define __ATTRIBUTE_GRID_CTRL_H__

class CAttributeBar;

class CAttributeGridCtrl : public CBCGPGridCtrl
{
public:
    CAttributeGridCtrl(CAttributeBar *attributeBar);

protected:
    virtual void OnItemChanged(CBCGPGridItem* pItem, int nRow, int nColumn);

private:
    CAttributeBar *m_AttributeBar;
};

#endif // __ATTRIBUTE_GRID_CTRL_H__
