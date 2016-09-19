// GaUI.cpp : main source file for GaUI.exe
//

#include "stdafx.h"

#include <WTL/atlframe.h>
#include <WTL/atlctrls.h>
#include <WTL/atldlgs.h>

#include "resource.h"

#include "GaUIView.h"
#include "aboutdlg.h"
#include "MainFrm.h"

#include "NativeApp.h"
#include "NativeWindow.h"

GaUI::Native::GaApplication _Module;
CAppModule* GetModule()
{
	return &_Module;
}
int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	GaUI::Native::SetApplication(&_Module);
	auto controller = GaUI::Native::InitializeWindowNativeController(_Module.get_m_hInst());
	GaUI::Native::SetCurrentController(controller);

	CMainFrame wndMain;

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	_Module.Run(reinterpret_cast<GaUI::Native::INativeWindow*>(&wndMain));

	GaUI::Native::UninitizlizeWindowNativeController(controller);
	return 0;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
