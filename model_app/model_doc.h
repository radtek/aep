// model_doc.h : interface of the CModelDoc class
//


#pragma once

#include "model.h"
#include "model_ctrl.h"
#include "connector_ctrl.h"

class CModelDoc : public CDocument
{
protected: // create from serialization only
	CModelDoc();
	DECLARE_DYNCREATE(CModelDoc)

// Attributes
public:
    ModelCtrlList m_ModelCtrlList;

    ConnectorCtrlList m_ConnectorCtrlList;

protected:
    UINT32 m_CurrentComponentId;

public:
    enum State
    {
        STATE_NORMAL,
        STATE_NEW_COMPONENT,
        STATE_NEW_INTERNAL_ALGORITHM,
        STATE_NEW_EXTERNAL_ALGORITHM,
        STATE_NEW_CONNECTOR,
        STATE_COMPONENT_SELECTED,
        STATE_CONNECTOR_SELECTED,
    } m_CurrentState;

    // New component.
    INT32 m_CurrentComponentTypeId;
    ModelCtrl *m_CurrentModelCtrl;

    // New internal algorithm.
    INT32 m_CurrentInternalAlgorithmId;

    // New connector ctrl.
    INT32 m_CurrentConnectorId;
    ConnectorCtrl *m_CurrentConnectorCtrl;

    // Normal.
    CPoint m_LastClickPosition;
    bool m_Moved;

// Operations
public:
    void SelectModelCtrl(ModelCtrl *modelCtrl);
    void SelectConnectorCtrl(ConnectorCtrl *connectorCtrl, CPoint point);
    void UnSelectCurrentModelCtrl();
    void UnSelectCurrentConnectorCtrl();
    void UnSelectAll();

    void RemoveCurrentModelCtrl();
    void RemoveCurrentConnectorCtrl();

// Operations
public:
    bool AddModelCtrl(ModelCtrl *modelCtrl);
    bool RemoveModelCtrl(ModelCtrl *modelCtrl);

    bool AddConnectorCtrl(ConnectorCtrl *connectorCtrl);
    bool RemoveConnectorCtrl(ConnectorCtrl *connectorCtrl);

// Overrides
	public:
	virtual BOOL OnNewDocument();
    virtual void DeleteContents();
	virtual void Serialize(CArchive& ar);

// Interfaces
    RC ExportModel(CArchive &ar);
    Model ExportModel();
    RC DrawData();

protected:
    RC DrawSingleData(IParam *param);

// Implementation
public:
	virtual ~CModelDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


