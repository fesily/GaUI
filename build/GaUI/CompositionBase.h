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
		class GaGraphicesHost;
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

			GaGraphicesHost* GetRelatedGraphicesHost();
			GaGraphicesHost* GetAssociateHost() const;
			void SetAssociateHost(GaGraphicesHost* val);

			bool GetVisible();
			void SetVisible(bool visible);

			eLimitMode GetLimitMode();
			void SetLimitMode(eLimitMode mode);

			IRenderTarget* GetRenderTarget();
			void SetRenderTarget(IRenderTarget* renderTarget);


			void Render(CSize offset);
#if 0

			composition* FindComposition(const CPoint& location);
			Rect GetGlobalBrounds();
#endif


			virtual CMargin GetMargin();
			virtual void SetMargin(const CMargin&  value);
			virtual CMargin GetInternalMargin();
			virtual void SetInternalMargin(const CMargin& value);
			virtual CSize GetPreferredMinSize();
			virtual void SetPreferredMinSize(CSize size);

			//virtual void ForceCalculateSizeImmediately();
			virtual CRect GetClientArea();

			virtual bool IsSizeAffectParent() = 0;
			virtual CSize GetMinPreferredClientSize() = 0;
			virtual CRect GetPreferredBounds() = 0;
			virtual CRect GetBounds() = 0;
		protected:
			CompositionList m_listChildren;//�������б�
			Composition* m_pParent;//ָ������
			std::shared_ptr<IElement> m_pElement;//��ǰ������ͼԪ
			IRenderTarget* m_pRenderTarget;//��Ⱦ��
			GaGraphicesHost* m_pAssociateHost;//�ܹ�����(��ǰ������������native����)
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