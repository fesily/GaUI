#include "stdafx.h"
#include "GDIInterface.h"
#include "WinGDI.h"
#include <unordered_map>
#include "type_traits_ex.h"
namespace GaUI
{
	namespace Element
	{
		template<typename Child,typename Key, typename Value>
		class ResourceAllocator
		{
			static const int32_t DeadPackageMax = 32;
		public:
			struct Package
			{
				Package(const Value& var)
					:resource(var)
					,counter(1)
				{

				}
				Value resource;
				int32_t counter;
				bool operator == (const Package&)const { return false; }
				bool operator != (const Package&)const { return true; }
			};
			struct DeadPackage
			{
				DeadPackage(const Key& _key, const Value& _value)
					:key(_key)
					,value(_value)
				{

				}
				Key key;
				Value value;
				bool operator == (const DeadPackage& package)const
				{ 
					return key == package.key;
				}
				bool operator != (const DeadPackage& package)const
				{
					return key != package.key;
				}
			};
		public:
			Value Create(const Key& key)
			{
				{
					auto iter = m_listAliveResources.find(key);
					if(iter != m_listAliveResources.end())
					{//����Ѿ�����,�����ü�����һ
						Package& package = iter->second;
						package.counter++;
						return package.resource;
					}
				}
				Value resource;
				for(auto iter = m_listDeadResources.begin();iter != m_listDeadResources.end(); iter++)
				{//���Ȳ��Ҵ����ٶ���,�еĻ��ָ�
					auto& var = (*iter);
					if(var.key == key)
					{
						resource = var.value;
						m_listDeadResources.erase(iter);
						break;
					}
				}
				if(!resource)
				{//����һ����ֵ
					auto p = static_cast<Child*>(this);
					resource = p->Child::CreateInternal(key);
				}
				m_listAliveResources.emplace(key, Package(resource));
				return resource;
			}
			void Destroy(const Key& key)
			{
				auto iter = m_listAliveResources.find(key);
				if(iter != m_listAliveResources.end())
				{//����ֱ�����ü���Ϊ0
					auto& package = iter->second;
					package.counter--;
					if(package.counter == 0)
					{//Ϊ���ʱ�򽫶����������ٶ���
						m_listAliveResources.erase(iter);
						//���ٶ��й���,ɾ�����ٶ���ͷ��
						if(m_listDeadResources.size() >= DeadPackageMax)
							m_listDeadResources.pop_front();
						m_listDeadResources.emplace_back(key, package);
					}
				}
			}
		public:
			std::unordered_map<Key, Package> m_listAliveResources;
			std::list<DeadPackage> m_listDeadResources;
		};

		namespace Element_GDI
		{
			class CachedPenAllocator
				:public ResourceAllocator<CachedPenAllocator,Color,std::shared_ptr<Pen>>
			{
			public:
				std::shared_ptr<Pen> CreateInternal(const Color& color)
				{
					return std::make_shared<Pen>(PS_SOLID, 1, RGB(color.r, color.g, color.b));
				}
			};

			class GDIResourceManager
				:public IGDIResourceManager
			{
				virtual std::shared_ptr<Pen> CreatePen(const Color& cr)
				{
					m_pens.Create(cr);
				}
				virtual void DestroyPen(const Color& rc)
				{
					m_pens.Destroy(rc);
				}
				virtual std::shared_ptr<Brush> CreateBrush(const Color& cr);
				virtual void DestroyBrush(const Color& rc);

				virtual std::shared_ptr<Font> CreateFont(const FontProperties& font);
				virtual void DestroyFont(const FontProperties& font);
				//virtual std::shared_ptr<Bitmap> CreateBitmap(const Color& cr) = 0;
				//virtual void DestroyBitmap(const Color& rc) = 0;
			protected:
				CachedPenAllocator m_pens;
			};

			GDIResourceManager* g_GDIResourceManager = nullptr;
			IGDIResourceManager* GetGDIResourcesManager()
			{
				return g_GDIResourceManager;
			}
		}
	}
}


