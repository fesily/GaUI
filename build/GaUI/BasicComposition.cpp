#include "stdafx.h"
#include "BasicComposition.h"
#include "NativeWindowInterface.h"
namespace GaUI
{
	namespace Layout
	{
		//////////////////////////////////////////////////////////////////////////

		CRect WindowComposition::GetBounds()
		{
			return CRect(CPoint(), m_pAttachedWindow ? m_pAttachedWindow->GetClientSize() : CSize());
		}

		//////////////////////////////////////////////////////////////////////////


		CRect BoundsComposition::GetPreferredBounds()
		{
			CRect result = GetBoundsInternal(m_rcCompositionRounds);
			if(GetParent() && IsAlignedToParent())
			{
				if(m_alignment2Parent.left >= 0)
					result.OffsetRect(m_alignment2Parent.left - result.left, 0);
				if(m_alignment2Parent.top >= 0)
					result.OffsetRect(0, m_alignment2Parent.top - result.top);
				if(m_alignment2Parent.right >= 0)
					result.right += m_alignment2Parent.right;
				if(m_alignment2Parent.bottom >= 0)
					result.bottom += m_alignment2Parent.bottom;
			}
			return result;
		}

		CRect BoundsComposition::GetBounds()
		{
			CRect result = GetPreferredBounds();
			if(GetParent() && IsAlignedToParent())
			{
				CSize clientSize = GetParent()->GetClientArea().Size();
				if(m_alignment2Parent.left >= 0 && m_alignment2Parent.right >= 0)
				{
					result.left = m_alignment2Parent.left;
					result.right = clientSize.cx - m_alignment2Parent.right;
				}
				else if(m_alignment2Parent.left >= 0)
				{
					auto w = result.Width();
					result.left = m_alignment2Parent.left;
					result.right = result.left + w;
				}
				else if(m_alignment2Parent.right >= 0)
				{
					auto w = result.Width();
					result.right = clientSize.cx - m_alignment2Parent.right;
					result.left = result.right - w;
				}


				if(m_alignment2Parent.top >= 0 && m_alignment2Parent.bottom >= 0)
				{
					result.top = m_alignment2Parent.top;
					result.bottom = clientSize.cy - m_alignment2Parent.bottom;
				}
				else if(m_alignment2Parent.top >= 0)
				{
					auto h = result.Height();
					result.top = m_alignment2Parent.top;
					result.bottom = result.top + h;
				}
				else if(m_alignment2Parent.bottom >= 0)
				{
					auto h = result.Height();
					result.bottom = clientSize.cy - m_alignment2Parent.bottom;
					result.top = result.bottom - h;
				}
			}
			UpdatePreviousBounds(result);
			return result;
		}

		void BoundsComposition::ClearAlignmentToParent()
		{
			m_alignment2Parent.SetRect(-1, -1, -1, -1);
		}

		void BoundsComposition::AlignmentToParentEmpty()
		{
			m_alignment2Parent.SetRect(0, 0, 0, 0);
		}

		bool BoundsComposition::IsAlignedToParent()
		{
			return !(m_alignment2Parent.left == -1 && m_alignment2Parent.top == -1 &&
					 m_alignment2Parent.right == -1 && m_alignment2Parent.bottom == -1);
		}
	}
}
