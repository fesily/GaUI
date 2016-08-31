#pragma once
#include "BasicComposition.h"
namespace GaUI
{
	namespace Layout
	{
		class StackItemComposition;
		class StackComposition
			:public BoundsComposition
		{
		public:
			enum eDirection
			{
				Horizontal,//从左到右布局
				Vertical,//从上到下布局
				Reversed_Horizontal,//从右到左
				Reversed_Vertical,//从下到上
			};

			eDirection m_eDirection{ Horizontal };//布局方向
			std::set<StackItemComposition*> m_listStackItem;//子容器 等同于基类中的children_;
			StackItemComposition* m_pEnsuringVisibleItem{ nullptr };//确保可见项

			std::list<CRect> m_listStackItemBounds;
			CSize m_StackItemTotalSize;
			int32_t m_nPadding{ 0 };//item之间的默认间距
			int32_t m_nAdjustment{ 0 };

			CMargin m_extraMargin;//额外的内边距


			void UpdateStackItemBounds();
			void EnsureStackItemVisble();
			CSize GetMinPreferredClientSize()override;
			CRect GetBounds()override;
			void OnChildInserted(Composition* child)override;
			void OnChildRemoved(Composition* child)override;
		};
		class StackItemComposition
			:public Site
		{
		public:
			StackComposition* stackParent_;
			CRect bounds_;
			CMargin extraMargin_;

			CSize GetMinSize();
			CRect GetBounds()override;
		};
	}
}
