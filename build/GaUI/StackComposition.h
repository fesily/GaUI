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
				Horizontal,//�����Ҳ���
				Vertical,//���ϵ��²���
				Reversed_Horizontal,//���ҵ���
				Reversed_Vertical,//���µ���
			};

			eDirection m_eDirection{ Horizontal };//���ַ���
			std::set<StackItemComposition*> m_listStackItem;//������ ��ͬ�ڻ����е�children_;
			StackItemComposition* m_pEnsuringVisibleItem{ nullptr };//ȷ���ɼ���

			std::list<CRect> m_listStackItemBounds;
			CSize m_StackItemTotalSize;
			int32_t m_nPadding{ 0 };//item֮���Ĭ�ϼ��
			int32_t m_nAdjustment{ 0 };

			CMargin m_extraMargin;//������ڱ߾�


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
