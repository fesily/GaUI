#include "stdafx.h"
#include "NativeWindowInterface.h"
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

	}
}


