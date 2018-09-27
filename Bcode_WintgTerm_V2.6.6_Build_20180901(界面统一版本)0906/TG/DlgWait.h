#if !defined(AFX_DLGWAIT_H__69D2233A_57C8_4CE6_A3A4_3B40037A9489__INCLUDED_)
#define AFX_DLGWAIT_H__69D2233A_57C8_4CE6_A3A4_3B40037A9489__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWait.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgWait dialog

class CDlgWait : public CDialog
{
// Construction
public:
	CDlgWait(const char *str,CWnd* pParent);   // standard constructor
	~CDlgWait();
// Dialog Data
	//{{AFX_DATA(CDlgWait)
	enum { IDD = IDD_DLG_WAIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWait)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWait)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
public:
	void SetWaitText(CString s);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWAIT_H__69D2233A_57C8_4CE6_A3A4_3B40037A9489__INCLUDED_)
