#include "stdafx.h"
#include "NativeApp.h"
#include "NativeWindowInterface.h"
namespace GaUI
{
	namespace Native
	{

		GaApplication::GaApplication()
		{
		}

		GaApplication::~GaApplication()
		{
		}

		void GaApplication::Run(INativeWindow* mainWnd)
		{
			ATLASSERT(!m_pMainWnd);
			if(!m_pMainWnd)
			{
				m_pMainWnd = mainWnd;
				GetCurrentController()->WindowServer()->Run(m_pMainWnd);
				m_pMainWnd = nullptr;
			}
		}

		HRESULT GaApplication::Init(ATL::_ATL_OBJMAP_ENTRY* pObjMap, HINSTANCE hInstance, const GUID* pLibID /*= NULL*/)
		{
			auto ret = WTL::CAppModule::Init(pObjMap, hInstance, pLibID);
			AddMessageLoop(&m_messageLoop);
			return ret;
		}

		void GaApplication::Term()
		{
			RemoveMessageLoop();
			WTL::CAppModule::Term();
		}

		GaApplication* g_app = nullptr;
		GaApplication* GetApplication()
		{
			return g_app;
		}

		void SetApplication(GaApplication* app)
		{
			ATLASSERT(g_app == nullptr);
			if(!g_app)
				g_app = app;
		}

	}
}
