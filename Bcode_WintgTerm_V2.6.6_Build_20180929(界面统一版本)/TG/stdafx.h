// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 头中排除极少使用的资料
#endif

// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
// 有关不同平台的相应值的最新信息，请参考 MSDN。
#ifndef WINVER				// 允许使用特定于 Windows 95 和 Windows NT 4 或更高版本的功能。
#define WINVER 0x0400		// 将此更改为针对于 Windows 98 和 Windows 2000 或更高版本的合适的值。
#endif

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows NT 4 或更高版本的功能。
#define _WIN32_WINNT 0x0400	// 将此更改为针对于 Windows 2000 或更高版本的合适的值。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用特定于 Windows 98 或更高版本的功能。
#define _WIN32_WINDOWS 0x0410 // 将此更改为针对于 Windows Me 或更高版本的合适的值。
#endif

#ifndef _WIN32_IE			// 允许使用特定于 IE 4.0 或更高版本的功能。
#define _WIN32_IE 0x0400	// 将此更改为针对于 IE 5.0 或更高版本的合适的值。
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将为显式的

#include <afxctl.h>         // ActiveX 控件的 MFC 支持
#include <afxext.h>         // MFC 扩展
#include <afxdtctl.h>		// MFC 对 Internet Explorer 4 公共控件的支持
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

// 如果不希望使用 MFC 数据库类，
//  请删除下面的两个包含文件
#include <afxdb.h>			// MFC 数据库类
#include <afxdao.h>			// MFC DAO 数据库类
#include <afxwin.h>

#pragma warning(disable:4018)
#pragma warning(disable:4244)

#define PI	3.14159265359
CString ConvertTimetoString(long tm); 
long ConvertStringtoTime(char *theString);
float CalDisp(float x1,float y1,float x2,float y2);
float PointLine(int m_fPixelPerHour,float xx,float yy,float x1,float y1,float x2,float y2);
CString ChangeAlpha(CString &input);
CString GetValidStr(CString str);
