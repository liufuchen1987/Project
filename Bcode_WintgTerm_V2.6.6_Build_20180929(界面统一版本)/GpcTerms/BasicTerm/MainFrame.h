
#if !defined(AFX_MAINFRAME_H__C44C1C24_BA0B_11D1_9D36_000021000CE6__INCLUDED_)
#define AFX_MAINFRAME_H__C44C1C24_BA0B_11D1_9D36_000021000CE6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MainFrame.h : header file
//
//#include "digitalclock.h"
#include "MyStatusBar.h"
#include "mytoolbar.h"
#include "DlgMemory.h"


#include "ext_src/OXTabClientWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame frame
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNCREATE(CMainFrame)
public:
	CMainFrame();           // protected constructor used by dynamic creation

// Operations
public:
	UINT	m_nTimerID;
	CMenu * m_pOptionMenu;

	void SetStatusText(UINT index, LPCTSTR text);//add by cf after 7-18

	// MTI client window
	COXTabClientWnd m_MTIClientWnd;
	CDlgMemory   m_DlgMemory;
	void OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult);
	
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMainFrame();
	CMyStatusBar  m_wndStatusBar;

	// Generated message map functions
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
 	afx_msg void OnButtonExit();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	
	afx_msg void OnUpdateCarsImage(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStoptimeOptimization();
	afx_msg void OnUpdateStoptimeOptimization(CCmdUI* pCmdUI);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
 	afx_msg LRESULT OnStatusBarUpdate(WPARAM wParam,LPARAM lParam);
	afx_msg void OnNcDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	
	afx_msg void OnBasicWin();
	
	
	
	//}}AFX_MSG
	
	afx_msg LRESULT OnStationStatus(WPARAM wParam, LPARAM lParam); 
	
	afx_msg void OnAbout();
	afx_msg void OnSystemComWnd();
	
	afx_msg void OnBasicPrevWin( ); 
	afx_msg void OnBasicBackupWin( );
	
	LRESULT OnProgramOnce(WPARAM wParam, LPARAM lParam);
	

	DECLARE_MESSAGE_MAP()
	void  OnMemoryWnd();
	
	void  AddXdtMenus();

	afx_msg void OnSelectDDT(UINT nID);
	afx_msg void OnUpdateSelectDDT(CCmdUI* pCmdUI);
public:
	
private:
	int nSectionNum;
	int nSectionNo[128];
public:
	afx_msg void OnInitMenu(CMenu* pMenu);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__C44C1C24_BA0B_11D1_9D36_000021000CE6__INCLUDED_)
