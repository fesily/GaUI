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
		ʹ���������,���Ӵ��ڵ�λ���Ǹ����ڿͻ���0,0��Ϊ����ԭ��
		*/
		using namespace Element;
		class Composition
		{
		public:
			typedef std::list<Composition*> CompositionList;
			enum eLimitMode
			{
				//������
				Nolimit,
				//�����ڵ�ǰͼԪ
				Limit2Element,
				//�����ڵ�ǰͼԪ�Լ�������
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
			CompositionList m_listChildren;//�������б�
			Composition* m_pParent;//ָ������
			std::shared_ptr<IElement> m_pElement;//��ǰ������ͼԪ
			IRenderTarget* m_pRenderTarget;//��Ⱦ��
			bool m_isVisible;//�Ƿ�ɼ� 
			CMargin m_margin;//�ڱ߾�
			CMargin m_internalMargin;//��߾�

			CSize m_preferredMinSize;//��Сsize
			eLimitMode m_eLimitMode;//����ģʽ
		};
		class Site
			:public Composition
		{
		public:
			CRect m_rcPreviousBounds;//��һ�η���Ĵ��ڴ�С

			virtual CRect GetBoundsInternal(const CRect& expectedBounds);
			virtual void UpdatePreviousBounds(const CRect& bounds);
			bool IsSizeAffectParent()override;
			CSize GetMinPreferredClientSize()override;
			CRect GetPreferredBounds()override;
		};
	}
}