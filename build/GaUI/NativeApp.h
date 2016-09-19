#pragma once
namespace GaUI
{
	namespace Native
	{
		class INativeWindow;
		class GaApplication;
		class GaMessageLoop
			:public CMessageLoop
		{
			friend GaApplication;
		};
		class GaApplication
			:public WTL::CAppModule
		{
		public:
			GaApplication();
			~GaApplication();
			void Run(INativeWindow* mainWnd);

			HRESULT Init(ATL::_ATL_OBJMAP_ENTRY* pObjMap, HINSTANCE hInstance, const GUID* pLibID = NULL);
			void Term();
		protected:
			INativeWindow* m_pMainWnd;//Ö÷´°¿Ú
			GaMessageLoop m_messageLoop;
		};
		extern GaApplication* GetApplication();
		extern void SetApplication(GaApplication* app);
	}
}