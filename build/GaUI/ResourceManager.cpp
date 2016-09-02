#include "stdafx.h"
#include "ResourceManager.h"
namespace GaUI
{
	namespace Element
	{
		GaResourceManager* g_pResourceManager = nullptr;
		GaResourceManager* GetResourcesManager()
		{
			return g_pResourceManager;
		}

		void SetResourcesManager(GaResourceManager* manager)
		{
			g_pResourceManager = manager;
		}

		bool RegisterFactories(IElementFactory* elementFactory, IRendererFactory* rendererFactory)
		{
			if(g_pResourceManager && elementFactory && rendererFactory)
			{
				if(g_pResourceManager->RegisterElementFactory(elementFactory) &&
				   g_pResourceManager->RegisterRendererFactory(elementFactory->GetElementTypeName(),rendererFactory))
					return true;
			}
			return false;
		}

		GaResourceManager::GaResourceManager()
		{

		}

		GaResourceManager::~GaResourceManager()
		{

		}

		bool GaResourceManager::RegisterElementFactory(IElementFactory* factory)
		{
			const std::wstring& typeName = factory->GetElementTypeName();
			if(m_listElementFactory.find(typeName) == m_listElementFactory.end())
			{
				m_listElementFactory.emplace(typeName, factory);
				return true;
			}
			return false;
		}

		bool GaResourceManager::RegisterRendererFactory(const std::wstring& typeName, IRendererFactory* factory)
		{
			if(m_listRendererFactory .find(typeName) == m_listRendererFactory.end())
			{
				m_listRendererFactory.emplace(typeName, factory);
				return true;
			}
			return false;
		}

		IElementFactory* GaResourceManager::GetElementFactory(const std::wstring& elementTypeName)
		{
			auto iter = m_listElementFactory.find(elementTypeName);
			if(iter != m_listElementFactory.end())
				return iter->second;
			return nullptr;
		}

		IRendererFactory* GaResourceManager::GetRendererFactory(const std::wstring& elementTypeName)
		{
			auto iter = m_listRendererFactory.find(elementTypeName);
			if(iter != m_listRendererFactory.end())
				return iter->second;
			return nullptr;
		}

	}
}