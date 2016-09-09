#pragma once
#include "CompositionBase.h"
namespace GaUI
{
	namespace Native
	{
		class INativeWindow;
	}
	namespace Layout
	{
		class WindowComposition
			:public Site
		{
		public:
			CRect GetBounds()override;
		public:
			Native::INativeWindow*	 m_pAttachedWindow;
		};

		class BoundsComposition
			:public Site
		{
		public:

			BoundsComposition() { ClearAlignmentToParent(); }
			CRect GetPreferredBounds()override;
			CRect GetBounds()override;
			void ClearAlignmentToParent();
			void AlignmentToParentEmpty();
			bool IsAlignedToParent();
		public:
			CRect m_rcCompositionRounds;//��ǰ����λ��
			CMargin m_alignment2Parent;//�������ڵı߾�
		};
	}
}