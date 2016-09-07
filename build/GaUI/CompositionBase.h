#pragma once
#include "memory.h"
#include <list>
#include <stack>
#include <set>
#include "ElementInterface.h"
namespace GaUI
{
	namespace Layout
	{
		/*
		使用相对坐标,既子窗口的位置是父窗口客户区0,0点为坐标原点
		*/
		using namespace Element;
		class Composition
		{
		public:
			typedef std::list<Composition*> CompositionList;
			enum eLimitMode
			{
				//不受限
				Nolimit,
				//受限于当前图元
				Limit2Element,
				//受限于当前图元以及子容器
				Limit2ElementAndChildren,
			};
		public:
			Composition();
			virtual ~Composition();
		protected:
			virtual void OnChildInserted(Composition* child);
			virtual void OnChildRemoved(Composition* child);
#if 0
			virtual void OnParentChanged(composition* oldParent, composition* newParent);
			virtual void OnParentLineChanged();
			virtual void OnRenderTagetChanged();
#endif
		public:
			Composition* GetParent();
			const CompositionList& Children();

			bool AddChild(Composition* child);
			bool InsetChild(Composition* child, int32_t index);
			bool RemoveChild(Composition* child);
			bool MoveChild(Composition* child, int32_t newIndex);


			std::shared_ptr<IElement> GetElement();
			void SetElement(IElement* element);
			void SetElement(std::shared_ptr<IElement> element);
#if 1
			bool GetVisible();
			void SetVisible(bool visible);

			eLimitMode GetLimitMode();
			void SetLimitMode(eLimitMode mode);

#endif

			IRenderTarget* GetRenderTarget();
			void SetRenderTarget(IRenderTarget* renderTarget);


			void Render(CSize offset);
#if 0

			composition* FindComposition(const CPoint& location);
			Rect GetGlobalBrounds();


			virtual Margin GetMargin();
			virtual void SetMargin(Margin value);
			virtual Margin GetInternalMargin();
			virtual void SetInternalMargin(Margin value);
			virtual Size GetPreferredMinSize();
			virtual void SetPreferredMinSize(Size size);

			virtual void ForceCalculateSizeImmediately();
#endif
			virtual CRect GetClientArea();

			virtual bool IsSizeAffectParent() = 0;
			virtual CSize GetMinPreferredClientSize() = 0;
			virtual CRect GetPreferredBounds() = 0;
			virtual CRect GetBounds() = 0;
		public:
			CompositionList m_listChildren;//子容器列表
			Composition* m_pParent;//指向父容器
			std::shared_ptr<IElement> m_pElement;//当前容器的图元
			IRenderTarget* m_pRenderTarget;//渲染器
			bool m_isVisible;//是否可见 
			CMargin m_margin;//内边距
			CMargin m_internalMargin;//外边距

			CSize m_preferredMinSize;//最小size
			eLimitMode m_eLimitMode;//限制模式
		};
		class Site
			:public Composition
		{
		public:
			CRect m_rcPreviousBounds;//上一次分配的窗口大小

			virtual CRect GetBoundsInternal(const CRect& expectedBounds);
			virtual void UpdatePreviousBounds(const CRect& bounds);
			bool IsSizeAffectParent()override;
			CSize GetMinPreferredClientSize()override;
			CRect GetPreferredBounds()override;
		};
	}
}