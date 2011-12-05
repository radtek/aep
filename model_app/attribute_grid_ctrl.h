/**
* @file
* @brief 属性表格控件类头文件.
* @author ruoxi
*
* 定义了属性表格控件类.
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
