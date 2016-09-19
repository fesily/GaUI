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
			Native::INativeWindow* m_pWnd;//native���ڶ���
			Layout::WindowComposition* m_pComposition;//native���ڲ�����

			CSize m_previousClientSize;//����Ĵ��ڴ�С
			CSize m_minSize;//��С��������
		};
	}
}