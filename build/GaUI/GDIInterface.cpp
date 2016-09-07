#include "stdafx.h"
#include "GDIInterface.h"
#include "WinGDI.h"
#include <unordered_map>
#include "type_traits_ex.h"
namespace GaUI
{
	namespace Element
	{
		template<typename Child,typename Key, typename Value,typename HashFunc = void>
		class ResourceAllocator
		{
			static const int32_t DeadPackageMax = 32;
		public:
			typedef Key key_type;
			typedef Value Value_type;
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
				DeadPackage(const Key& _key, const Package& _value)
					:key(_key)
					,value(_value.resource)
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
			std::unordered_map<Key, Package, typename std::conditional<std::is_void<HashFunc>::value, std::hash<Key>, HashFunc>::type> m_listAliveResources;
			std::list<DeadPackage> m_listDeadResources;
		};



		namespace Element_GDI
		{
			class GDIResourceManager;
			GDIResourceManager* g_GDIResourceManager = nullptr;
			IGDIResourceManager* GetGDIResourcesManager()
			{
				return g_GDIResourceManager;
			}

#if 0
			namespace Detail
			{
				//����������
				ARCPen::ARCPen(key_const_referece key)
					:ARCResource_base(key)
				{

				}
				void ARCPen::Create()
				{
					base_type::operator=(g_GDIResourceManager->CreatePen(_Mykey));
				}
				void ARCPen::Destory()
				{
					g_GDIResourceManager->DestroyPen(_Mykey);
				}

				ARCBrush::ARCBrush(key_const_referece key)
					:ARCResource_base(key)
				{
				}
				void ARCBrush::Create()
				{
					base_type::operator=(g_GDIResourceManager->CreateBrush(_Mykey));
				}
				void ARCBrush::Destory()
				{
					g_GDIResourceManager->DestroyBrush(_Mykey);
				}



			}
#endif
			//��Դ����� ��
			class CachedPenAllocator
				:public ResourceAllocator<CachedPenAllocator, Color, std::shared_ptr<Pen>>
			{
			public:
				Value_type CreateInternal(const key_type& color)
				{
					return std::make_shared<Pen>(PS_SOLID, 1, color);
				}
			};
			class CachedBrushAllocator
				:public ResourceAllocator<CachedBrushAllocator, Color, std::shared_ptr<Brush>>
			{
			public:
				Value_type CreateInternal(const key_type& color)
				{
					return std::make_shared<Brush>(color);
				}
			};

			class GDIResourceManager
				:public IGDIResourceManager
			{
			public:
				virtual std::shared_ptr<Pen> CreatePen(const Color& cr)
				{
					m_pens.Create(cr);
				}
				virtual void DestroyPen(const Color& rc)
				{
					m_pens.Destroy(rc);
				}
				virtual std::shared_ptr<Brush> CreateBrush(const Color& cr)
				{
					m_brushs.Create(cr);
				}
				virtual void DestroyBrush(const Color& rc)
				{
					m_brushs.Destroy(rc);
				}

				virtual std::shared_ptr<Font> CreateFont(const FontProperties& font)
				{

				}
				virtual void DestroyFont(const FontProperties& font)
				{

				}
				//virtual std::shared_ptr<Bitmap> CreateBitmap(const Color& cr) = 0;
				//virtual void DestroyBitmap(const Color& rc) = 0;
			protected:
				CachedPenAllocator m_pens;
				CachedBrushAllocator m_brushs;
			};


		}
	}
}


