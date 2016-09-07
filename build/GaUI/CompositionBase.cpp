#include "stdafx.h"
#include "CompositionBase.h"
namespace GaUI
{
	namespace Layout
	{
#define DeflateMargin DeflateRect
		Composition::Composition()
			:m_pParent(nullptr)
			, m_pRenderTarget(nullptr)
			, m_isVisible(true)
			, m_eLimitMode(Nolimit)
		{

		}

		Composition::~Composition()
		{
			for each (auto var in m_listChildren)
			{
				delete var;
				var = nullptr;
			}
		}

		void Composition::OnChildInserted(Composition* child)
		{

		}

		void Composition::OnChildRemoved(Composition* child)
		{

		}

		Composition* Composition::GetParent()
		{
			return m_pParent;
		}

		const Layout::Composition::CompositionList& Composition::Children()
		{
			return m_listChildren;
		}

		bool Composition::AddChild(Composition* child)
		{
			return InsetChild(child, m_listChildren.size());
		}

		bool Composition::InsetChild(Composition* child, int32_t index)
		{
			if((!child) || child->GetParent()) return false;

			auto iter = m_listChildren.begin();
			std::advance(iter, index);
			m_listChildren.emplace(iter, child);

			child->m_pParent = this;
			child->SetRenderTarget(m_pRenderTarget);
			OnChildInserted(child);
			return true;
		}

		bool Composition::RemoveChild(Composition* child)
		{
			if(child)
			{
				auto iter = std::find(m_listChildren.begin(), m_listChildren.end(), child);
				if(iter != m_listChildren.end())
				{
					m_listChildren.erase(iter);
					OnChildInserted(child);
					child->m_pParent = nullptr;
					child->SetRenderTarget(nullptr);
					return true;
				}
			}
			return false;
		}

		bool Composition::MoveChild(Composition* child, int32_t newIndex)
		{
			if(child)
			{
				auto iter = std::find(m_listChildren.begin(), m_listChildren.end(), child);
				if(iter != m_listChildren.end())
				{
					m_listChildren.erase(iter);
					iter = m_listChildren.begin();
					std::advance(iter, newIndex);
					m_listChildren.emplace(iter, child);
					return true;
				}
			}
			return false;
		}

		std::shared_ptr<GaUI::Element::IElement> Composition::GetElement()
		{
			return m_pElement;
		}

		void Composition::SetElement(IElement * element)
		{
			SetElement(std::make_shared<IElement>(element));
		}

		void Composition::SetElement(std::shared_ptr<IElement> element)
		{
			if(m_pElement)
			{
				auto renderer = m_pElement->GetRender();
				if(renderer)
					renderer->SetRenderTarget(nullptr);
			}
			m_pElement = element;
			if(m_pElement)
			{
				auto renderer = m_pElement->GetRender();
				if(renderer)
					renderer->SetRenderTarget(m_pRenderTarget);
			}
		}

		IRenderTarget* Composition::GetRenderTarget()
		{
			return m_pRenderTarget;
		}

		void Composition::SetRenderTarget(IRenderTarget* renderTarget)
		{
			m_pRenderTarget = renderTarget;
			if(m_pElement)
			{
				auto renderer = m_pElement->GetRender();
				if(renderer)
					renderer->SetRenderTarget(m_pRenderTarget);
			}
			for each (auto& var in m_listChildren)
			{
				var->SetRenderTarget(m_pRenderTarget);
			}
		}

		void Composition::Render(CSize offset)
		{
			if(m_isVisible && m_pRenderTarget && !m_pRenderTarget->IsClipperCoverWholeTarget())
			{//绘制条件,可见,有渲染目标,渲染器内部关于裁剪区域计算为0 = 没有使用裁剪区域
				CRect bounds = GetBounds();//获得实际区域
										  //实际区域去除外边框
				bounds.DeflateMargin(m_margin);

				//矩形是合法的
				if(bounds.IsNormalize())
				{
					//偏移值,将矩形转换成父窗口坐标系统
					bounds.OffsetRect(offset);
					if(m_pElement)
					{//有当前图元,则当前图元先渲染
						auto renderer = m_pElement->GetRender();
						if(renderer)
						{
							renderer->Render(bounds);
						}
					}
					if(!m_listChildren.empty())
					{//如果有子排版对象
					 //先移除边框
						bounds.DeflateMargin(m_internalMargin);
						if(bounds.IsNormalize())
						{
							offset = bounds.Size();
							m_pRenderTarget->PushClipper(bounds);
							if(!m_pRenderTarget->IsClipperCoverWholeTarget())
							{
								for each (auto& var in m_listChildren)
								{
									var->Render(CSize(bounds.left, bounds.top));
								}
							}
							m_pRenderTarget->PoshClipper();
						}
					}
				}
			}
		}

		CRect Composition::GetClientArea()
		{
			CRect bounds = GetBounds();
			bounds.DeflateMargin(m_margin);
			bounds.DeflateMargin(m_internalMargin);
			return bounds;
		}

		//////////////////////////////////////////////////////////////////////////
		CRect Site::GetBoundsInternal(const CRect& expectedBounds)
		{
			CSize minSize = GetMinPreferredClientSize();
			minSize.IntersectSize(m_preferredMinSize);

			minSize.IntersectSize(CSize(expectedBounds.Width(), expectedBounds.Height()));

			return CRect(expectedBounds.TopLeft(), minSize);
		}

		void Site::UpdatePreviousBounds(const CRect& bounds)
		{
			if(m_rcPreviousBounds != bounds)
			{
				m_rcPreviousBounds = bounds;
			}
		}

		bool Site::IsSizeAffectParent()
		{
			return true;
		}

		CSize Site::GetMinPreferredClientSize()
		{
			CSize minSize;
			if(m_eLimitMode != Nolimit)
			{
				if(m_pElement)
				{
					auto renderer = m_pElement->GetRender();
					if(renderer)
						minSize = renderer->GetMinSize();
				}
			}
			if(m_eLimitMode == Composition::Limit2ElementAndChildren)
			{
				for each (auto& var in m_listChildren)
				{
					if(var->IsSizeAffectParent())
					{
						CRect childBounds = var->GetPreferredBounds();
						minSize.IntersectSize(CSize(childBounds.Width(), childBounds.Height()));
					}
				}
			}
			return minSize;
		}

		CRect Site::GetPreferredBounds()
		{
			return GetBoundsInternal(CRect());
		}


	}
}