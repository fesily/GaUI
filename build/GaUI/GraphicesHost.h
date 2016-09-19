#pragma once
#include "BasicComposition.h"
namespace GaUI
{
	namespace Native
	{
		class INativeWindow;
	}
	namespace Layout
	{
		class GaGraphicesHost
		{
		public:
			GaGraphicesHost();
			~GaGraphicesHost();


			void Render();

			Native::INativeWindow* GetNativeWindow() const;
			void SetNativeWindow(Native::INativeWindow* val);
			GaUI::Layout::WindowComposition* GetMainComposition() const;
		protected:
			Native::INativeWindow* m_pWnd;//native窗口对象
			Layout::WindowComposition* m_pComposition;//native窗口布局器

			CSize m_previousClientSize;//缓存的窗口大小
			CSize m_minSize;//最小窗口限制
		};
	}
}