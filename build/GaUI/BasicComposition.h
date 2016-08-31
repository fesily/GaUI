#pragma once
#include "CompositionBase.h"
namespace GaUI
{
	namespace Layout
	{
		class WindowComposition
			:public Site
		{
		public:
			CRect GetBounds()override;
		public:
			INativeWindow*	 m_pAttachedWindow;
		};

		class BoundsComposition
			:public Site
		{
		public:

			BoundsComposition() { ClearAlignmentToParent(); }
			CRect GetPreferredBounds()override;
			CRect GetBounds()override;
			void ClearAlignmentToParent();
			bool IsAlignedToParent();
		public:
			CRect m_rcCompositionRounds;//当前窗口位置
			CMargin m_alignment2Parent;//跟父窗口的边距
		};
	}
}