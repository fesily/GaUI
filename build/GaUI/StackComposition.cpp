#include "stdafx.h"
#include "StackComposition.h"

namespace GaUI
{
	namespace Layout
	{
		//////////////////////////////////////////////////////////////////////////

		void StackComposition::UpdateStackItemBounds()
		{
			if(m_listStackItemBounds.size() != m_listStackItem.size())
			{
				m_listStackItemBounds.resize(m_listStackItem.size());
			}

			m_StackItemTotalSize.SetSizeEmpty();
			CPoint offset;
			auto iterBounds = m_listStackItemBounds.begin();
			for each (auto& var in m_listStackItem)
			{
				CSize itemSize = var->GetMinSize();
				*iterBounds = CRect(offset, itemSize);
#define  Accumulate(U,V)									\
			{												\
				if(m_StackItemTotalSize.V < itemSize.V)		\
				{											\
					m_StackItemTotalSize.V = itemSize.V;		\
				}											\
				if(iterBounds != m_listStackItemBounds.begin())	\
					m_StackItemTotalSize.U += m_nPadding;		\
				m_StackItemTotalSize.U += itemSize.U;		\
			}
				switch(m_eDirection)
				{
				case Layout::StackComposition::Horizontal:
				case Layout::StackComposition::Reversed_Horizontal:
					Accumulate(cx, cy);
					break;
				case Layout::StackComposition::Vertical:
				case Layout::StackComposition::Reversed_Vertical:
					Accumulate(cy, cx);
					break;
				}
#undef Accumulate

				offset.x += itemSize.cx + m_nPadding;
				offset.y += itemSize.cy + m_nPadding;
				++iterBounds;
			}
			EnsureStackItemVisble();
		}

		void StackComposition::EnsureStackItemVisble()
		{
#define Adjustment(U, V)															\
				if (itemBounds.U <= 0)											\
				{																	\
					m_nAdjustment -= itemBounds.U;									\
				}																	\
				else																\
				{																	\
					int32_t overflow = itemBounds.V - m_rcPreviousBounds.V;		\
					if (overflow > 0)												\
					{																\
						m_nAdjustment -= overflow;										\
					}																\
				}																	
			if(m_pEnsuringVisibleItem)
			{
				m_nAdjustment = 0;//todo需不需初始化?

				CRect itemBounds = m_pEnsuringVisibleItem->GetBounds();
				switch(m_eDirection)
				{
				case Layout::StackComposition::Horizontal:
				case Layout::StackComposition::Reversed_Horizontal:
					Adjustment(left, right);
					break;
				case Layout::StackComposition::Vertical:
				case Layout::StackComposition::Reversed_Vertical:
					Adjustment(top, bottom);
					break;
				}
			}
#undef  Adjustment
		}

		CSize StackComposition::GetMinPreferredClientSize()
		{
			CSize minSize = __super::GetMinPreferredClientSize();
			if(m_eLimitMode == Composition::Limit2ElementAndChildren)
			{
				if(!m_pEnsuringVisibleItem)
				{
					switch(m_eDirection)
					{
					case Layout::StackComposition::Horizontal:
					case Layout::StackComposition::Reversed_Horizontal:
						minSize.cx = max(minSize.cx, m_StackItemTotalSize.cx);
						break;
					case Layout::StackComposition::Vertical:
					case Layout::StackComposition::Reversed_Vertical:
						minSize.cy = max(minSize.cy, m_StackItemTotalSize.cy);
						break;
					}
				}
			}

			int32_t x(0), y(0);
			if(m_extraMargin.left > 0)
				x += m_extraMargin.left;
			if(m_extraMargin.right > 0)
				x += m_extraMargin.right;
			if(m_extraMargin.top > 0)
				y += m_extraMargin.top;
			if(m_extraMargin.bottom > 0)
				y += m_extraMargin.bottom;
			return minSize + CSize(x, y);
		}

		CRect StackComposition::GetBounds()
		{
			ATLASSERT(m_listStackItem.size() == m_listStackItemBounds.size());
			auto iter = m_listStackItemBounds.begin();
			for each (auto& var in m_listStackItem)
			{
				if(var->GetMinSize() != iter->Size())
				{
					UpdateStackItemBounds();
					break;
				}
				++iter;
			}

			return  __super::GetBounds();
		}

		void StackComposition::OnChildInserted(Composition* child)
		{
			__super::OnChildInserted(child);
			auto item = dynamic_cast<StackItemComposition*>(child);
			if(item)
			{
				if(m_listStackItem.find(item) == m_listStackItem.end())
				{
					m_listStackItem.insert(item);
					item->stackParent_ = this;
				}
				UpdateStackItemBounds();
			}
		}

		void StackComposition::OnChildRemoved(Composition* child)
		{
			__super::OnChildRemoved(child);
			auto item = dynamic_cast<StackItemComposition*>(child);
			if(item)
			{
				m_listStackItem.erase(item);
				if(item == m_pEnsuringVisibleItem)
					m_pEnsuringVisibleItem = nullptr;
				UpdateStackItemBounds();
			}
		}

		CSize StackItemComposition::GetMinSize()
		{
			return GetBoundsInternal(bounds_).Size();
		}

		CRect StackItemComposition::GetBounds()
		{
			CRect result = bounds_;
			if(stackParent_)
			{
				{
					ATLASSERT(stackParent_->m_listStackItem.size() == stackParent_->m_listStackItemBounds.size());
					;
					auto iter = stackParent_->m_listStackItemBounds.begin();
					for each (auto& var in stackParent_->m_listStackItem)
					{
						if(var == this)
						{
							result = *iter;
							break;
						}
						++iter;
					}
				}
				CRect parentBounds = stackParent_->m_rcPreviousBounds;
				CMargin margin = stackParent_->m_extraMargin;
				margin.FormatPositiveRect();

				auto& x = result.left;
				auto& y = result.top;
				auto w = result.Width();
				auto h = result.Height();

				switch(stackParent_->m_eDirection)
				{
				case Layout::StackComposition::Horizontal:
					x += margin.left + stackParent_->m_nAdjustment;
					y = margin.top;
					h = parentBounds.Height() - margin.top - margin.bottom;
					break;
				case Layout::StackComposition::Vertical:
					x = parentBounds.Width() - margin.right - x - w + stackParent_->m_nAdjustment;
					y = margin.top;
					h = parentBounds.Height() - margin.top - margin.bottom;
					break;
				case Layout::StackComposition::Reversed_Horizontal:
					x = margin.left;
					y += margin.top + stackParent_->m_nAdjustment;
					w = parentBounds.Width() - margin.left - margin.right;
					break;
				case Layout::StackComposition::Reversed_Vertical:
					x = margin.left;
					y = parentBounds.Height() - margin.bottom - y - h + stackParent_->m_nAdjustment;
					w = parentBounds.Width() - margin.left - margin.right;
					break;
				}

				result = CRect(x - extraMargin_.left, y - extraMargin_.top, x + w + extraMargin_.right, y + h + extraMargin_.bottom);
			}
			UpdatePreviousBounds(result);
			return result;
		}
	}
}
