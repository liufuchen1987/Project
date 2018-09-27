// ToolTipWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ToolTipWnd.h"
#include ".\tooltipwnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipWnd
CToolTipWnd::CToolTipWnd()
{
	lpWndCls = AfxRegisterWndClass(0);
	
	m_iWidth = 180;
	m_iHeight = 20;

	m_clrTextColor = RGB(0,0,255);
}

CToolTipWnd::~CToolTipWnd()
{
	m_fontText.DeleteObject();
}


BEGIN_MESSAGE_MAP(CToolTipWnd, CWnd)
	//{{AFX_MSG_MAP(CToolTipWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CToolTipWnd message handlers
BOOL CToolTipWnd::Create(CWnd* pParentWnd, int width, int height, bool wht) 
{
	if(wht)
	{
		bsBkgrdBrush.CreateSolidBrush(RGB(255,255,255));
		bsFrameBrush.CreateSolidBrush(RGB(255,255,255));
	}
	else
	{
		bsBkgrdBrush.CreateSolidBrush(RGB(255,255,255));
		bsFrameBrush.CreateSolidBrush(RGB(255, 255, 225));
	}
	
	m_iWidth = width;
	m_iHeight = height;
	BOOL bRet = CWnd::CreateEx(NULL, lpWndCls, NULL,
		WS_POPUP, 0, 0, m_iWidth, m_iHeight,
		pParentWnd->GetSafeHwnd(), NULL, NULL);

	if(bRet)
		SetOwner(pParentWnd);

	return bRet;
}

void CToolTipWnd::OnPaint() 
{
	// device m_context for painting
	CPaintDC dc(this); 
	
	dc.SaveDC();
	CRgn rgnComb;	
	CRect m_RectText;
	GetClientRect(&m_RectText);
	rgnComb.CreateRectRgn(m_RectText.left,m_RectText.top, m_RectText.right,  m_RectText.bottom);
	
	dc.SetBkMode(TRANSPARENT);
	dc.FillRgn( &rgnComb, &bsBkgrdBrush);
	//dc.FrameRgn(&rgnComb, &bsFrameBrush, 1, 1);
	
	COLORREF pClr=dc.SetTextColor(m_clrTextColor);
	CFont *pFont = dc.SelectObject(&m_fontText);
	CSize czTextWidth = dc.GetTextExtent(m_strText);
	
	if( czTextWidth.cx < m_RectText.Width())
	{
		dc.DrawText(m_strText, m_RectText, DT_TOP | DT_LEFT | DT_SINGLELINE);
	}
	else
	{
		dc.DrawText(m_strText, m_RectText, DT_TOP | DT_LEFT | DT_WORDBREAK);
	}
	
	dc.SelectObject(pFont);
	dc.SetTextColor(pClr);
	dc.RestoreDC(-1);
}


int CToolTipWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_fontText.CreateFont(18, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
	
	return 0;
}

void CToolTipWnd::HideTipWindow()
{
	m_strText="";
	ShowWindow(SW_HIDE);
}

void CToolTipWnd::ShowTipWindow(const CPoint& pt,CString strText)
{
	m_strText = strText;
	
	CClientDC dc(this);

	CFont *pFont = dc.SelectObject(&m_fontText);
	CSize czTextWidth = dc.GetTextExtent(m_strText);
	dc.SelectObject(pFont);

	int width = 250;
	int height = 18;
	if(czTextWidth.cx < 250)
		width = czTextWidth.cx;
	else
	{
		height *= (1+(czTextWidth.cx/250));
	}

	SetWindowPos(&wndTop,pt.x, pt.y-height, width, height, SWP_NOACTIVATE);

	ShowWindow(SW_SHOWNOACTIVATE);
}

