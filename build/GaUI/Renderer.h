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
					auto pRenderer =  new Renderer;
					pRenderer->m_factory = this;
					return pRenderer;
				}
			};
			typedef Factory FactoryType;
		protected:
			IRendererEx()
				: m_factory(nullptr)
				, m_element(nullptr)
				, m_renderTarget(nullptr)
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
				m_renderTarget = static_cast<RenderTarget*>(pRenderTarget);
				RenderTargetChangedInternal(old, m_renderTarget);
			}
			CSize GetMinSize()override
			{
				return m_minSize;
			}
		public:
			virtual void InitializeInternal() {};
			virtual void FinalizeInternal() {};
			virtual void RenderTargetChangedInternal(RenderTarget* oldTarget, RenderTarget* newTarget) {};
		protected:
			IRendererFactory*	m_factory;
			Element*			m_element;
			RenderTarget*		m_renderTarget;
			CSize				m_minSize;
		};
	}
}