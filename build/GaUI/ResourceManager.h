#pragma once
#include <unordered_map>
#include <string>
#include "ElementInterface.h"
namespace GaUI
{
	namespace Native
	{
		class INativeWindow;
	}
	namespace Element
	{
		class GaGraphicsResourceManager
		{
			typedef std::unordered_map<std::wstring, IElementFactory*> ElementFactoryList;
			typedef std::unordered_map<std::wstring, IRendererFactory*> RendererFactoryList;
		public:
			GaGraphicsResourceManager();
			virtual ~GaGraphicsResourceManager();
		public:
			virtual bool RegisterElementFactory(IElementFactory* factory);
			virtual bool RegisterRendererFactory(const std::wstring& typeName, IRendererFactory* factory);

			virtual IElementFactory* GetElementFactory(const std::wstring& elementTypeName);
			virtual IRendererFactory* GetRendererFactory(const std::wstring& elementTypeName);
			virtual IRenderTarget* GetRenderTarget(Native::INativeWindow* window) = 0;
			virtual void RecreateRenderTarget(Native::INativeWindow* window) = 0;
		protected:
			ElementFactoryList m_listElementFactory;
			RendererFactoryList m_listRendererFactory;
		};
		extern GaGraphicsResourceManager* GetGraphicsResourcesManager();
		extern void SetGraphicsResourcesManager(GaGraphicsResourceManager* manager);
		extern bool RegisterFactories(IElementFactory* elementFactory, IRendererFactory* rendererFactory);
	}
}