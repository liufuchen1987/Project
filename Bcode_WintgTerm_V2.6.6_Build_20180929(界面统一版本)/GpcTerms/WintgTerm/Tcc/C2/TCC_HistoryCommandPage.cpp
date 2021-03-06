/*
 *  服务器历史限速命令管理
 */

#include "stdafx.h"
#include "resource.h"
#include "Tcc_Dlg.h"

namespace TCC {



void CHistoryCommandPage::InitListCtrl(CGridCtrl& grid)
{
	struct COLINFO { TCHAR* label;	INT width;	INT fmt; }
	colinfo[] =
	{
		{"命令号", 60, DT_RIGHT | DT_WORDBREAK|DT_NOPREFIX },
		{"开始站", 80, DT_LEFT | DT_WORDBREAK|DT_NOPREFIX },
		{"结束站", 80, DT_LEFT | DT_WORDBREAK|DT_NOPREFIX },
		{"上下行", 100, DT_LEFT | DT_WORDBREAK|DT_NOPREFIX },
		{"开始公里标", 80, DT_CENTER | DT_WORDBREAK|DT_NOPREFIX },
		{"结束公里标", 80, DT_CENTER | DT_WORDBREAK|DT_NOPREFIX},
		{"限速值", 60, DT_RIGHT | DT_WORDBREAK|DT_NOPREFIX },
		{"状态", 80, DT_LEFT | DT_WORDBREAK|DT_NOPREFIX },
		{"本站状态", 80, DT_LEFT | DT_WORDBREAK|DT_NOPREFIX },
		{"生成时间", 80, DT_LEFT | DT_WORDBREAK|DT_NOPREFIX },
		{"本站执行时间", 80, DT_LEFT | DT_WORDBREAK|DT_NOPREFIX },
		{"开始时间", 80, DT_LEFT | DT_WORDBREAK|DT_NOPREFIX },
		{"结束时间", 80, DT_LEFT | DT_WORDBREAK|DT_NOPREFIX },
	};

	CRect rcClient;
	grid.GetClientRect(&rcClient);

	try{
		grid.SetRowCount(1);                //行
		grid.SetColumnCount(sizeof(colinfo)/sizeof(colinfo[0]));             //列
		grid.SetFixedRowCount(1);        //固定行
		grid.SetFixedColumnCount(3);     //固定列		    
		grid.SetFixedTextColor(RGB(0,0,0));      //文本颜色
		grid.SetGridLineColor(RGB(166,202,240));       //线的颜色
	    grid.SetFixedBkColor(RGB(255,242,240));

		for(int i=0; i<grid.GetColumnCount(); i++)
		{
			grid.SetColumnWidth(i, colinfo[i].width);
		}
	}
   	catch(CMemoryException * e)
	{
		e->ReportError();
		e->Delete();
		return ;
	}

	GV_ITEM item;
	item.mask = GVIF_TEXT|GVIF_FORMAT;
	item.nFormat = DT_CENTER| DT_WORDBREAK|DT_NOPREFIX;

	item.row = 0;  //行
	for(item.col = 0; item.col < grid.GetColumnCount(); item.col++)
	{
		item.strText.Format(colinfo[item.col].label);
		item.nFormat = colinfo[item.col].fmt;
		grid.SetItem(&item);
	}
	grid.SetHeaderSort(TRUE);
	grid.SetSingleRowSelection();
}

void CHistoryCommandPage::AppendCommand(STOCK_COMMAND& cmd)
{
	ITccClientInfoProvider *pInfoProvider = GetTccClientInfoProvider();

	CGridCtrl& grid = m_CmdList;

	GV_ITEM item;
	item.row = item.col = 0;

	item.mask = GVIF_TEXT|GVIF_FORMAT;//|GVIF_PARAM;
	item.nFormat = DT_CENTER|DT_WORDBREAK|DT_NOPREFIX;

	CString str;
	str.Format("%4d", cmd.nCmdID);

	int nPos = 0;
	for(int i=1; i<grid.GetRowCount(); i++)
	{
		STOCK_COMMAND *pCmd = (STOCK_COMMAND *)grid.GetItemData(i, 0);
		if(pCmd->nConsoleID == cmd.nConsoleID
			&& pCmd->nCmdID == cmd.nCmdID
			&& pCmd->sys_id == cmd.sys_id
			&& pCmd->bCancelLimit == cmd.bCancelLimit)
		{
			*pCmd = cmd;
			break;
		}
	}
	if(i == grid.GetRowCount())
	{
		// 在屁股后增加
		STOCK_COMMAND *pCmd = new STOCK_COMMAND;
		ASSERT(pCmd);
		*pCmd = cmd;
		item.row = grid.InsertRow(str, -1);
		grid.SetItemFormat(item.row, item.col, grid.GetItemFormat(0, item.col));
		grid.SetItemData(item.row, 0, (DWORD)pCmd);
	}
	else
	{
		item.row = i;
		grid.SetItemText(item.row, 0, str);
	}
	grid.EnsureVisible(item.row, 0);

	// 开始站
	item.col ++;
	if(cmd.nStaID[0])
		item.strText = pInfoProvider->GetStationName(cmd.nStaID[0]);
	else
		item.strText = "";
	//item.lParam = cmd.nStaID[0];
	item.nFormat = grid.GetItemFormat(0, item.col);
	grid.SetItem(&item);

	// 结束站
	item.col ++;
	if(cmd.nStaID[1])
		item.strText = pInfoProvider->GetStationName(cmd.nStaID[1]);
	else
		item.strText="";
	//item.lParam = cmd.nStaID[1];
	item.nFormat = grid.GetItemFormat(0, item.col);
	grid.SetItem(&item);

	item.mask |= GVIF_STATE;
	item.nState = GVIS_READONLY;

	// 上下行
	item.col ++;
	item.strText = pInfoProvider->GetTccLineName(cmd.nStaID[0], cmd.nLineID);
	if(item.strText.IsEmpty())
		item.strText = gpcdef.GetC3TccLineName(cmd.nLineID);
	//item.lParam = cmd.nLineID;
	item.nFormat = grid.GetItemFormat(0, item.col);
	grid.SetItem(&item);

	// 开始公里标
	item.col ++;
	if(cmd.bFullLimit)
		str.Format("全限速");
	else
		str = cmd.nKmMark[0].toString();
	item.strText = str;
	//item.lParam = (DWORD)cmd.nKmMark[0];
	item.nFormat = grid.GetItemFormat(0, item.col);
	grid.SetItem(&item);

	// 结束公里标
	item.col ++;
	if(cmd.bFullLimit)
		str.Format("全限速");
	else
		str = cmd.nKmMark[1].toString();
	item.strText = str;
	//item.lParam = (DWORD)cmd.nKmMark[1];
	item.nFormat = grid.GetItemFormat(0, item.col);
	grid.SetItem(&item);

	// 限速值
	item.col ++;
	if(cmd.bCancelLimit)
	{
		grid.SetItemFgColour(item.row, item.col, RGB(255, 0, 0) );
		str.Format("取消限速");
	}
	else
	{
		grid.SetItemFgColour(item.row, item.col);
		str.Format("%3dKm/h", cmd.nSpeedMaxVal);
	}
	item.strText = str;
	//item.lParam = cmd.nSpeedMaxVal;
	item.nFormat = grid.GetItemFormat(0, item.col);
	grid.SetItem(&item);

	// 状态
	INT nConfirmNum = 0;
	INT nExecNum = 0;
	INT nCancelNum = 0;
	INT nUnknownNum = 0;
	for(i=0; i<cmd.tcc.size(); i++)
	{
		switch(cmd.tcc[i].nStatus)
		{
		case CONFIRM:
			nConfirmNum ++;
			break;
		case EXECUTING:
			nExecNum ++;
			break;
		case CANCELED:
			nCancelNum ++;
			break;
		default:
			nUnknownNum ++;
			break;
		}
	}

	// 设置颜色
	COLORREF clrBk = grid.GetGridBkColor();
	COLORREF clrFg = grid.GetGridColor();
	str.Empty();
	if(nConfirmNum == cmd.tcc.size())
	{
		grid.SetItemFgColour(item.row, 0, RGB(0, 255, 0));
		str.Format("全部确认");
	}
	else if(nExecNum == cmd.tcc.size())
	{
        grid.SetItemFgColour(item.row, 1, RGB(0, 0, 255));
		str.Format("全部执行");
	}
	else if(nCancelNum == cmd.tcc.size())
	{
		if(grid.GetItemText(item.row, 2).IsEmpty())
			grid.SetItemBkColour(item.row, 2, RGB(255, 0, 0));
		else
			grid.SetItemFgColour(item.row, 2, RGB(255, 0, 0));
		str.Format("全部取消");
	}
	else
	{
		if(nUnknownNum)
		{
			str += "存在未知状态";
		}
		if(nExecNum)
		{
			grid.SetItemFgColour(item.row, 1, RGB(0, 0, 255));
			str += "部分执行";
		}
		if(nCancelNum)
		{
			if(grid.GetItemText(item.row, 2).IsEmpty())
				grid.SetItemBkColour(item.row, 2, RGB(255, 0, 0));
			else
				grid.SetItemFgColour(item.row, 2, RGB(255, 0, 0));
			str += "部分取消";
		}
		//if(nConfirmNum)
		//{
		//	grid.SetItemFgColour(item.row, 0, RGB(0, 255, 0));
		//	str = "全部确认" + str;
		//}
	}

	// 设置状态
	item.col ++;
	item.strText = str;
	//item.lParam = 0;
	item.nFormat = grid.GetItemFormat(0, item.col);
	grid.SetItem(&item);

	// 本站状态
	item.col ++;
	for(i=0; i<cmd.tcc.size(); i++)
	{
		if (cmd.tcc[i].nID != GetCurrentTccID())
			continue;

		switch(cmd.tcc[i].nStatus)
		{
		case CONFIRM:
			item.strText = "已确认";
			break;
		case EXECUTING:
			item.strText = "已执行";
			break;
		case CANCELED:
			item.strText = "已取消";
			break;
		default:
			item.strText.Format("未知状态 %d", cmd.tcc[i].nStatus);
			break;
		}
		break;
	}
	item.lParam = 0;
	item.nFormat = grid.GetItemFormat(0, item.col);
	grid.SetItem(&item);

	CTime ct;
	// 生成时间
	item.col ++;
	if(cmd.nCreateTime <= 0)
		str.Format("0");
	else
	{
		ct = cmd.nCreateTime;
		str= ct.Format("%Y-%m-%d %H:%M");
	}
	item.strText = str;
	//item.lParam = ;
	item.nFormat = grid.GetItemFormat(0, item.col);
	grid.SetItem(&item);

	// 本站执行时间
	item.col ++;
	for (i=0; i<cmd.tcc.size(); i++)
	{
		if (cmd.tcc[i].nID != GetCurrentTccID())
			continue;

		if(cmd.tcc[i].nTime <= 0)
			str.Format("");
		else
		{
			ct = cmd.tcc[i].nTime;
			str= ct.Format("%Y-%m-%d %H:%M");
		}
		item.strText = str;
		//item.lParam = ;
		item.nFormat = grid.GetItemFormat(0, item.col);
		grid.SetItem(&item);
	}

	// 限速开始时间
	item.col ++;
	if(cmd.bStartNow || cmd.nTime[0] <= 0)
	{
		str = "立即开始";
	}
	else
	{
		ct = cmd.nTime[0];
		str = ct.Format("%m-%d %H:%M");
	}
	item.strText = str;
	//item.lParam = cmd.nTime[0];
	item.nFormat = grid.GetItemFormat(0, item.col);
	grid.SetItem(&item);

	// 限速结束时间
	item.col ++;
	if(cmd.bEndless || cmd.nTime[1] <= 0)
		str.Format("永久有效");
	else
	{
		ct = cmd.nTime[1];
		str= ct.Format("%m-%d %H:%M");
	}
	item.strText = str;
	//item.lParam = cmd.nTime[1];
	item.nFormat = grid.GetItemFormat(0, item.col);
	grid.SetItem(&item);

	grid.RedrawRow(item.row);
}

// CHistoryCommandPage 对话框

IMPLEMENT_DYNAMIC(CHistoryCommandPage, CPropertyPage)
CHistoryCommandPage::CHistoryCommandPage()
	: CPropertyPage(CHistoryCommandPage::IDD)
	, m_pCurCmd(NULL)
	, m_bTimeBegin(1), m_bTimeEnd(1)
{
}

CHistoryCommandPage::~CHistoryCommandPage()
{
}

CTccDlg* CHistoryCommandPage::GetTccDlg()
{
	CWnd *pWnd = GetParent();
	ASSERT(pWnd);
	pWnd = pWnd->GetParent();
	ASSERT(pWnd);

	return (CTccDlg*)pWnd;
}

ITccAdviseSink* CHistoryCommandPage::GetTccAdviseSink()
{
	return GetTccDlg()->GetTccAdviseSink();
}

ITccClientInfoProvider* CHistoryCommandPage::GetTccClientInfoProvider()
{
	return GetTccDlg()->GetTccClientInfoProvider();
}

stano_t CHistoryCommandPage::GetCurrentTccID()
{
	return GetTccDlg()->GetCurrentTccID();
}

void CHistoryCommandPage::Refresh()
{
	OnBtnClickedTccRefresh();
}

STOCK_COMMAND* CHistoryCommandPage::GetCommand(DWORD nConsoleID, sysid_t& sysid, WORD nCmdID)
{
	STOCK_COMMAND *p = NULL;
	for(int row=m_CmdList.GetFixedRowCount(); row<m_CmdList.GetRowCount(); row++)
	{
		STOCK_COMMAND *pcmd = (STOCK_COMMAND*)m_CmdList.GetItemData(row, 0);
		if(NULL == pcmd)
			continue;
		if(pcmd->sys_id == sysid)
		{
			p = pcmd;
			break;
		}
		else if(pcmd->nCmdID == nCmdID && !pcmd->bCancelLimit)
		{
			WORD status = pcmd->GetTccStatus(GetCurrentTccID());
			if(EXECUTING == status)
			{
				p = pcmd;
				break;
			}
			if(CANCELED != status)
				p = pcmd;
		}
	}
	return p;
}

void CHistoryCommandPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_TCC_CMD_NOTE, m_CmdString);

	//DDX_Control(pDX, IDC_TCC_LIST, m_TccList);

	DDX_Control(pDX, IDC_TCC_CMD_TIMEBEGIN, m_tmBegin);
	DDX_Control(pDX, IDC_TCC_CMD_TIMEEND, m_tmEnd);

	DDX_Radio(pDX, IDC_TCC_CMD_TIMEBEGIN_RADIO, m_bTimeBegin);
	DDX_Control(pDX, IDC_TCC_CMD_TIMEBEGIN_RADIO, m_BeginRadio);
	DDX_Control(pDX, IDC_TCC_CMD_TIMEBEGIN_RADIO2, m_BeginRadio2);
	DDX_Radio(pDX, IDC_TCC_CMD_TIMEEND_RADIO, m_bTimeEnd);
	DDX_Control(pDX, IDC_TCC_CMD_TIMEEND_RADIO, m_EndRadio);
	DDX_Control(pDX, IDC_TCC_CMD_TIMEEND_RADIO2, m_EndRadio2);
}

void CHistoryCommandPage::ShowCmd(STOCK_COMMAND *pcmd)
{
	ITccClientInfoProvider *pInfoProvider = GetTccClientInfoProvider();

	if(pcmd)
		m_CmdString = pcmd->toString(pInfoProvider);
	else
		m_CmdString.Empty();
	
	UpdateData(FALSE);
}


#define GRIDCTRL 101
BOOL CHistoryCommandPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ITccClientInfoProvider *pInfoProvider = GetTccClientInfoProvider();
	if(NULL == pInfoProvider)
	{
		MessageBox("没有安装TccClientInfoProvider接口!");
		return FALSE;
	}
	ITccAdviseSink *pAdviseSink = GetTccAdviseSink();
	if(NULL == pAdviseSink)
	{
		MessageBox("没有安装TccAdviseSink接口!");
		return FALSE;
	}

	CRect rcl;
	GetDlgItem(IDC_TCC_CMD_LIST)->GetWindowRect(&rcl);
	ScreenToClient(rcl);
	m_CmdList.Create(rcl, this, GRIDCTRL);
	InitListCtrl(m_CmdList);


	//查询时间范围
	m_tmBegin.SetFormat("yyy'-'MM'-'dd HH':'mm");
	m_tmEnd.SetFormat("yyy'-'MM'-'dd HH':'mm");

	CTime ct;
	ct = CTime::GetCurrentTime();
	m_tmEnd.SetTime(ct.GetTime());

	ct -= CTimeSpan(2, 0, 0, 0);
	m_tmBegin.SetTime(ct.GetTime());

	m_tmBegin.EnableWindow(m_bTimeBegin == 0);
	m_tmEnd.EnableWindow(m_bTimeEnd == 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BEGIN_MESSAGE_MAP(CHistoryCommandPage, CPropertyPage)
	ON_NOTIFY(NM_CLICK, GRIDCTRL, OnNMClickTccCmdList)
	ON_NOTIFY(NM_RCLICK, GRIDCTRL, OnNMClickTccCmdList)
	ON_WM_DESTROY()
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_TCC_REFRESH, OnBtnClickedTccRefresh)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	ON_BN_CLICKED(IDC_TCC_CMD_TIMEBEGIN_RADIO2, OnBtnClickedTccCmdTimebeginRadio2)
	ON_BN_CLICKED(IDC_TCC_CMD_TIMEBEGIN_RADIO,  OnBtnClickedTccCmdTimebeginRadio)
	ON_BN_CLICKED(IDC_TCC_CMD_TIMEEND_RADIO2,   OnBtnClickedTccCmdTimeendRadio2)
	ON_BN_CLICKED(IDC_TCC_CMD_TIMEEND_RADIO,    OnBtnClickedTccCmdTimeendRadio)
END_MESSAGE_MAP()

// CHistoryCommandPage 消息处理程序
//

void CHistoryCommandPage::OnNMClickTccCmdList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNMHDR;
	int nItem = pItem->iRow;
	if(nItem < 1)
		return ;

	// 设置当前选择的命令
	STOCK_COMMAND *pCmd = (STOCK_COMMAND *)m_CmdList.GetItemData(nItem, 0);
	if(m_pCurCmd != pCmd)
	{
		m_pCurCmd = pCmd;
		ShowCmd(m_pCurCmd);
	}

	*pResult = 0;
}


void CHistoryCommandPage::OnBtnClickedTccRefresh()
{
	UpdateData(TRUE);

	stano_t nTccID = GetCurrentTccID();
	if(0 == nTccID)
	{
		MessageBox("请选择车站!");
		return ;
	}

	m_pCurCmd = NULL;
	ShowCmd(m_pCurCmd);

	for(int row=m_CmdList.GetFixedRowCount(); row<m_CmdList.GetRowCount(); row++)
	{
		STOCK_COMMAND *pcmd = (STOCK_COMMAND *)m_CmdList.GetItemData(row, 0);
		if(pcmd)
			delete pcmd;
		m_CmdList.SetItemData(row, 0, 0);
	}
	m_CmdList.DeleteNonFixedRows();
	m_CmdList.Refresh();

	CTime ct;
	m_tmBegin.GetTime(ct);
	time_t tmBegin = ct.GetTime();

	m_tmEnd.GetTime(ct);
	time_t tmEnd = ct.GetTime();

	if(m_bTimeBegin)
		tmBegin = 0;
	if(m_bTimeEnd)
		tmEnd = 0;

	GetTccAdviseSink()->OnRequestStockCommandList(0, nTccID, dcmd_id_t(), tmBegin, tmEnd, GetSafeHwnd(), 1);
	//GetTccAdviseSink()->OnRequestStockCommandList(nTccID, GetSafeHwnd());
}

void CHistoryCommandPage::OnDestroy()
{
	CPropertyPage::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	STOCK_COMMAND *pcmd = NULL;
	for(int i=m_CmdList.GetFixedRowCount(); i<m_CmdList.GetRowCount(); i++)
	{
		pcmd = (STOCK_COMMAND*)m_CmdList.GetItemData(i, 0);
		if(pcmd)
			delete pcmd;
	}
	m_CmdList.DeleteAllItems();
	m_pCurCmd = NULL;
}

void CHistoryCommandPage::OnCancel()
{
	CPropertyPage::OnCancel();

	 GetTccDlg()->SendMessage(WM_COMMAND, IDCANCEL);
}


void CHistoryCommandPage::OnBtnClickedTccCmdTimeendRadio2()
{
	m_tmEnd.EnableWindow(FALSE);
}

void CHistoryCommandPage::OnBtnClickedTccCmdTimeendRadio()
{
	m_tmEnd.EnableWindow(TRUE);
}

void CHistoryCommandPage::OnBtnClickedTccCmdTimebeginRadio2()
{
	m_tmBegin.EnableWindow(FALSE);
}

void CHistoryCommandPage::OnBtnClickedTccCmdTimebeginRadio()
{
	m_tmBegin.EnableWindow(TRUE);
}


};
