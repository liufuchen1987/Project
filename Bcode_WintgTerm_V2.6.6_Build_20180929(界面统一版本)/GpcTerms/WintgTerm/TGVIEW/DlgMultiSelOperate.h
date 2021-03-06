#if !defined(AFX_DLGMULTISELOPERATE_H__AFAA8796_2D5B_4700_B510_E542806C79CD__INCLUDED_)
#define AFX_DLGMULTISELOPERATE_H__AFAA8796_2D5B_4700_B510_E542806C79CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMultiSelOperate.h : header file
//

#include "../GridCtrl_src/GridCtrl.h"
#include "../GridCtrl_src/GridCellCheck.h"
#include "../uneditableGridCell.h"

#include "tg_schedule_base.h"
#include "resource.h"

#include <vector>
/////////////////////////////////////////////////////////////////////////////
// CDlgMultiSelOperate dialog

class CDlgMultiSelOperate : public CDialog
{
// Construction
public:
	CDlgMultiSelOperate(CWnd* pParent = NULL);   // standard constructor
	CDlgMultiSelOperate(std::vector<DWORD>& list, CWnd* pParent); 
	~CDlgMultiSelOperate();
// Dialog Data
	//{{AFX_DATA(CDlgMultiSelOperate)
	enum { IDD = IDD_DLG_MULTISEL_OPERATE };
	CComboBox	m_ctlTrainType;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMultiSelOperate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ResetTrainSelected();
	enum { DEL_TRAIN, STOP_TRAIN, RESTORE_TRAIN	};

    void initialGridCtrl();
	void fillGrid();	
	
	CGridCtrl * m_pGridCtrl;
	
	// Generated message map functions
	//{{AFX_MSG(CDlgMultiSelOperate)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonSelall();
	afx_msg void OnButtonNotSelall();
	afx_msg void OnSelchangeComboTraintype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CTG_TrainScheduleBase* m_pSchdBase;
	std::vector<ULONG> all;
	std::vector<ULONG> sel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMULTISELOPERATE_H__AFAA8796_2D5B_4700_B510_E542806C79CD__INCLUDED_)
