#pragma once
#include "ElementInterface.h"
#include "memory.h"
#include "ResourceManager.h"
namespace GaUI
{
	namespace Element
	{
		template<typename TElement>
		class IElementEx
			:public IElement
		{
		public:
			class Factory
				:public IElementFactory
			{
			public:
				std::wstring GetElementTypeName()override
				{
					return TElement::GetElementTypeName();
				}
				IElement* Create()override
				{
					TElement* element = new TElement;
					element->m_pFactory = this;
					IRendererFactory* renderFactory = GetResourcesManager()->GetRendererFactory(GetElementTypeName());
					if(renderFactory)
					{
						element->m_renderer = renderFactory->Create();
						element->m_renderer->Initialize(element);
					}
				}
			};
		public:
			static std::wstring GetElementTypeName()
			{
				return typeid(TElement).name();
			}
			static TElement* Create()
			{
				return dynamic_cast<TElement*>(GetResourcesManager()->GetElementFactory(TElement::GetElementTypeName())->Create());
			}
			IElementFactory* GetFactory()override
			{
				return m_pFactory;
			}
			IRenderer* GetRender()override
			{
				return m_renderer.get();
			}
		protected:
			IElementFactory* m_pFactory;
			std::shared_ptr<IRenderer> m_renderer;
		};
		enum eElementShape
		{
			Rectangle,
			Ellipse,
		};
		class GaSolidBorderElement
			:public IElementEx<GaSolidBorderElement>
		{
		protected:
			GaSolidBorderElement();
		public:
			~GaSolidBorderElement();
		protected:
			eElementShape m_eShape;
			Color m_color;
		};

		class GaRoundBorderElement
			:public IElement
		{

		};
		class Ga3DBorderElement
			:public IElement
		{

		};
		class Ga3DSplitterElement
			:public IElement
		{

		};
		class GaSoildBackgroundElement
			:public IElement
		{

		};
		class GaGradientBackgroundElement
			:public IElement
		{

		};
		class GaSolidLabelElement
			:public IElement
		{

		};
		class GaImageFrameElement
			:public IElement
		{

		};
		class GaPolygonElement
			:public IElement
		{

		};

	}
}