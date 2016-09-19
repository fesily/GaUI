#include "stdafx.h"
#include "GaWindowNCHandler.h"
#include "GaScreenHelp.h"

namespace GaUI
{
	static CRect g_rcNcRect(0, 0, 0, 1);

	GaWindowNCHandler::GaWindowNCHandler()
		:m_NcMargin(3, 3, 3, 3), m_nCaptionHeight(35)
		, m_szMinSize(300, 200)
	{
	}


	GaWindowNCHandler::~GaWindowNCHandler()
	{
	}


	BOOL GaWindowNCHandler::ProcessWindowMessage(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam, _Inout_ LRESULT& lResult, _In_ DWORD dwMsgMapID /*= 0*/)
	{
		if(dwMsgMapID != 0 || IsDiscardMsg(uMsg))
			return FALSE;
		BOOL bHandled = TRUE;
		SetWindow(hWnd);
		switch(uMsg)
		{
		case WM_NCHITTEST:
			lResult = OnNcHitTest(CPoint(lParam));
			break;
		case WM_NCCALCSIZE:
			lResult = OnNcCalcSize((BOOL)wParam, lParam, bHandled);
			break;
		case WM_NCACTIVATE:
			lResult = TRUE;
			break;
		case WM_NCPAINT:
			OnNcPaint();
			lResult = 0;
			break;
		case WM_GETMINMAXINFO:
			OnGetMinMaxInfo(reinterpret_cast<LPMINMAXINFO>(lParam));
			lResult = 0;
			break;
		case WM_DISPLAYCHANGE:
			OnDispalayChange(wParam, CSize(lParam));
			lResult = 0;
			break;
		case WM_NCCREATE:
		case WM_NCDESTROY:
		case WM_NCMOUSEMOVE:
		case WM_NCLBUTTONDOWN:
		case WM_NCLBUTTONUP:
		case WM_NCLBUTTONDBLCLK:
		default:
			bHandled = FALSE;
		}
		return bHandled;
	}

	void GaWindowNCHandler::OnDispalayChange(DWORD dwColorBit,const CSize& szScreen)
	{
		GaScreenHelp::Get()->Update();
	}

	void GaWindowNCHandler::OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo)
	{
		auto screenHelp = GaScreenHelp::Get();
		auto pInfo = screenHelp->Find(::MonitorFromWindow(m_window, MONITOR_DEFAULTTONEAREST));
		if(pInfo)
		{
			static const CRect m_rcMaxInset(0, 0, 0, 0);
			auto& mi = pInfo->m_monitorInfo;
			auto lpMMI = lpMinMaxInfo;
 			CRect rcWork = mi.rcWork, rcMonitor = mi.rcMonitor;
  			lpMMI->ptMaxPosition.x = abs(rcWork.left - rcMonitor.left) - m_rcMaxInset.left;
  			lpMMI->ptMaxPosition.y = abs(rcWork.top - rcMonitor.top) - m_rcMaxInset.top;
 			lpMMI->ptMaxSize.x = abs(rcWork.Width()) +  m_rcMaxInset.right +  m_rcMaxInset.left;
 			lpMMI->ptMaxSize.y = abs(rcWork.Height()) +  m_rcMaxInset.bottom +  m_rcMaxInset.top;
			lpMMI->ptMaxTrackSize.x = abs(rcWork.Width()) +  m_rcMaxInset.right +  m_rcMaxInset.left;
 			lpMMI->ptMaxTrackSize.y = abs(rcWork.Height()) +  m_rcMaxInset.bottom +  m_rcMaxInset.top;
 			lpMMI->ptMinTrackSize = reinterpret_cast<const CPoint&>(m_szMinSize);
		}
	}

	void GaWindowNCHandler::OnNcPaint()
	{
		CWindowDC dc(m_window);
	
		CRect rcWindow = GetCaptionRect();
		dc.FillSolidRect(rcWindow, 0x454548);
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, 0xa5a5a8);
		CPenHandle hPen = dc.SelectPen(pen);
		hPen.DeleteObject();
		dc.MoveTo(rcWindow.left, rcWindow.bottom);
		dc.LineTo(rcWindow.right, rcWindow.bottom);

// 		CBrush brush;
// 		brush.CreateSysColorBrush(COLOR_3DDKSHADOW);
// 		LPCTSTR str = _T("test");
// 		dc.GrayString(brush, nullptr, (LPARAM)str, 0, 10, 10, 200, 200);
	}

	LRESULT GaWindowNCHandler::OnNcCalcSize(BOOL wParam, LPARAM lParam, BOOL& bHandled)
	{
		if(wParam == TRUE)
		{
			LPNCCALCSIZE_PARAMS pNCCalcSizeParam = reinterpret_cast<LPNCCALCSIZE_PARAMS>(lParam);
			 
			pNCCalcSizeParam->rgrc[2] = pNCCalcSizeParam->rgrc[1];
			pNCCalcSizeParam->rgrc[1] = pNCCalcSizeParam->rgrc[0];
			//未知原因,不修改,左拉和上拉的{过程中}会产生窗口偏移
			static_cast<CRect&>(pNCCalcSizeParam->rgrc[0]).DeflateRect(g_rcNcRect);
			return WVR_REDRAW;
		}
		else
		{
			ATLASSERT(wParam == FALSE);
			bHandled = FALSE;
			return 0;
		}
	}

	LRESULT GaWindowNCHandler::OnNcHitTest(CPoint& pt)
	{
		//条件:此时没有实际NC区域,NC靠模拟出来;
		m_window.ScreenToClient(&pt);
		CRect rcWindow;
		m_window.GetWindowRect(&rcWindow);
		rcWindow.OffsetRect(-rcWindow.TopLeft());
		
		if(m_window.IsZoomed())
		{
			return pt.y > rcWindow.top + m_nCaptionHeight ? HTCLIENT : HTCAPTION;
		}
		else
		{
			//左上角,判断是不是在左上角，就是看当前坐标是不是即在左边拖动的范围内，又在上边拖动的范围内，其它角判断方法类似  
			if(pt.x < rcWindow.left + m_NcMargin.left && pt.y < rcWindow.top + m_NcMargin.top)
			{
				return HTTOPLEFT;
			}
			//右上角  
			else if(pt.x >= rcWindow.right - m_NcMargin.right && pt.y < rcWindow.top + m_NcMargin.top)
			{
				return HTTOPRIGHT;
			}
			//左下角  
			else if(pt.x < rcWindow.left + m_NcMargin.left && pt.y >= rcWindow.bottom - m_NcMargin.bottom)
			{
				return HTBOTTOMLEFT;
			}
			//右下角  
			else if(pt.x >= rcWindow.right - m_NcMargin.right && pt.y >= rcWindow.bottom - m_NcMargin.bottom)
			{
				return HTBOTTOMRIGHT;
			}
			else if(pt.x < rcWindow.left + m_NcMargin.left)
			{
				return HTLEFT;
			}
			else if(pt.x >= rcWindow.right - m_NcMargin.right)
			{
				return HTRIGHT;
			}
			else if(pt.y < rcWindow.top + m_NcMargin.top)
			{
				return HTTOP;
			}
			else if(pt.y >= rcWindow.bottom - m_NcMargin.bottom)
			{
				return HTBOTTOM;          //以上这四个是上、下、左、右四个边  
			}
			else
			{
				//rcWindow.DeflateRect(m_NcMargin);
				if(rcWindow.PtInRect(pt))
					return pt.y > rcWindow.top + m_nCaptionHeight ? HTCLIENT : HTCAPTION;
			}
		}
		return HTERROR;
	}

	CRect GaWindowNCHandler::GetClientRectEx()
	{
		ATLASSERT(m_window.m_hWnd);
		CRect rcClient;
		m_window.GetClientRect(&rcClient);
		rcClient.top += m_nCaptionHeight;
		return rcClient;
	}

	CRect GaWindowNCHandler::GetCaptionRect()
	{
		ATLASSERT(m_window.m_hWnd);
		CRect rcWindow;
		m_window.GetWindowRect(&rcWindow);
		rcWindow.OffsetRect(-rcWindow.TopLeft());
		rcWindow.bottom = rcWindow.top + m_nCaptionHeight - 1;
		return rcWindow;
	}

	void GaWindowNCHandler::SetWindow(HWND hWnd)
	{
#ifdef DEBUG
		if(!m_window.m_hWnd)
		{
			m_window.Attach(hWnd);
		}
		else
		{
			ATLASSERT(m_window.m_hWnd == hWnd);
		}
#else
		m_window.Attach(hWnd);
#endif
	}

}