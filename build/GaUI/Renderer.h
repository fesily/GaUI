#pragma once
#include "ResourceManager.h"
namespace GaUI
{
	namespace Element
	{
		template<typename Element, typename Renderer, typename RenderTarget>
		class IRendererEx
			:public IRenderer
		{
		public:
			class Factory
				:public IRendererFactory
			{
			public:
				IRenderer* Create()override
				{
					return new Renderer;
				}
			};
		protected:
			IRendererEx(IRendererFactory* pFactory)
				:m_factory(pFactory)
				,m_element(nullptr)
				,m_renderTarget(nullptr)
			{}
		public:
			static void Register()
			{
				RegisterFactories(new Element::Factory, new Renderer::Factory);
			}

			IRendererFactory* GetFactory() override
			{
				return m_factory;
			}
			void Initialize(IElement* pElement)override
			{
				m_element = static_cast<Element*>(pElement);
				InitializeInternal();
			}
			void Finalize()override
			{
				FinalizeInternal();
			}
			void SetRenderTarget(IRenderTarget* pRenderTarget)override
			{
				RenderTarget* old = m_renderTarget;
				pRenderTarget = static_cast<RenderTarget*>(pRenderTarget);
				RenderTargetChangedInternal(oldRenderTarget, renderTarget);
			}
			CSize GetMinSzie()override
			{
				return m_minSize;
			}
		protected:
			IRendererFactory*	m_factory;
			Element*			m_element;
			RenderTarget*		m_renderTarget;
			CSize				m_minSize;
		};
	}
}