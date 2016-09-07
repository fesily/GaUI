#pragma once
#include "CompositionBase.h"
namespace GaUI
{
	namespace Layout
	{
		class INativeWindow;
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
			void AlignmentToParentEmpty();
			bool IsAlignedToParent();
		public:
			CRect m_rcCompositionRounds;//��ǰ����λ��
			CMargin m_alignment2Parent;//�������ڵı߾�
		};
	}
}