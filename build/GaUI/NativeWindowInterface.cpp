#include "stdafx.h"
#include "NativeWindowInterface.h"
#include "NativeWindow.h"
namespace GaUI
{
	namespace Native
	{

		CSize INativeWindow::GetClientSize()
		{
			CRect rc;
			CWindow::GetClientRect(rc);
			return rc.Size();
		}


		INativeWindowListener::eHitTestResult INativeWindowListener::HitTest(const CPoint& cpt)
		{
			return eHitTestResult::NoDecision;
		}

		INativeController* g_currentController = nullptr;
		extern void SetCurrentController(INativeController* controller)
		{
			g_currentController = controller;
		}

		extern INativeController* GetCurrentController()
		{
			return g_currentController;
		}

	}
}


