#if !defined(AFX_INSERTSIMPLEDLG_H__92EAC290_397A_4E75_8A0C_5FAC03BC72C4__INCLUDED_)
#define AFX_INSERTSIMPLEDLG_H__92EAC290_397A_4E75_8A0C_5FAC03BC72C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertSimpleDlg.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CInsertSimpleDlg dialog

class CInsertSimpleDlg : public CDialog
{
// Construction
public:
	CString title;

	CInsertSimpleDlg(LPCTSTR title,CWnd* pParent, int flag=0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsertSimpleDlg)
	enum { IDD = IDD_DIG_GOON_RETURN };
	CString	m_sStaionid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsertSimpleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsertSimpleDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_flag;
	
public:
	CString m_sRetTrainId;
	afx_msg void OnEnChangeEdit1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTSIMPLEDLG_H__92EAC290_397A_4E75_8A0C_5FAC03BC72C4__INCLUDED_)
