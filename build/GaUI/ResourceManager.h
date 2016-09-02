#pragma once
#include <unordered_map>
#include <string>
#include "ElementInterface.h"
namespace GaUI
{
	namespace Element
	{
		class GaResourceManager
		{
			typedef std::unordered_map<std::wstring, IElementFactory*> ElementFactoryList;
			typedef std::unordered_map<std::wstring, IRendererFactory*> RendererFactoryList;
		public:
			GaResourceManager();
			virtual ~GaResourceManager();
		public:
			virtual bool RegisterElementFactory(IElementFactory* factory);
			virtual bool RegisterRendererFactory(const std::wstring& typeName, IRendererFactory* factory);

			virtual IElementFactory* GetElementFactory(const std::wstring& elementTypeName);
			virtual IRendererFactory* GetRendererFactory(const std::wstring& elementTypeName);
		protected:
			ElementFactoryList m_listElementFactory;
			RendererFactoryList m_listRendererFactory;
		};
		extern GaResourceManager* GetResourcesManager();
		extern void SetResourcesManager(GaResourceManager* manager);
		extern bool RegisterFactories(IElementFactory* elementFactory, IRendererFactory* rendererFactory);
	}
}