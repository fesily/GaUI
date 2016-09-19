#include "stdafx.h"
#include "ResourceManager.h"
namespace GaUI
{
	namespace Element
	{
		GaGraphicsResourceManager* g_pResourceManager = nullptr;
		GaGraphicsResourceManager* GetGraphicsResourcesManager()
		{
			return g_pResourceManager;
		}

		void SetGraphicsResourcesManager(GaGraphicsResourceManager* manager)
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

		GaGraphicsResourceManager::GaGraphicsResourceManager()
		{

		}

		GaGraphicsResourceManager::~GaGraphicsResourceManager()
		{

		}

		bool GaGraphicsResourceManager::RegisterElementFactory(IElementFactory* factory)
		{
			const std::wstring& typeName = factory->GetElementTypeName();
			if(m_listElementFactory.find(typeName) == m_listElementFactory.end())
			{
				m_listElementFactory.emplace(typeName, factory);
				return true;
			}
			return false;
		}

		bool GaGraphicsResourceManager::RegisterRendererFactory(const std::wstring& typeName, IRendererFactory* factory)
		{
			if(m_listRendererFactory .find(typeName) == m_listRendererFactory.end())
			{
				m_listRendererFactory.emplace(typeName, factory);
				return true;
			}
			return false;
		}

		IElementFactory* GaGraphicsResourceManager::GetElementFactory(const std::wstring& elementTypeName)
		{
			auto iter = m_listElementFactory.find(elementTypeName);
			if(iter != m_listElementFactory.end())
				return iter->second;
			return nullptr;
		}

		IRendererFactory* GaGraphicsResourceManager::GetRendererFactory(const std::wstring& elementTypeName)
		{
			auto iter = m_listRendererFactory.find(elementTypeName);
			if(iter != m_listRendererFactory.end())
				return iter->second;
			return nullptr;
		}

	}
}