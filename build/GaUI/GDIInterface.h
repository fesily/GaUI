#pragma once
#include "ElementInterface.h"
#include "memory.h"
namespace GaUI
{
	namespace Window
	{
		namespace GDI
		{
			class DC;
			class Pen;
			class Brush;
			class Font;
			class Bitmap;
		}
	}
	namespace Element
	{
		namespace Element_GDI
		{
			using namespace Window::GDI;

			class IGDIRenderTarget
				:public IRenderTarget
			{
			public:
				virtual DC* GetDC() = 0;
			};

			class IGDIResourceManager
				:public virtual Interface
			{
			public:
				virtual std::shared_ptr<Pen> CreatePen(const Color& cr) = 0;
				virtual void DestroyPen(const Color& rc) = 0;
				virtual std::shared_ptr<Brush> CreateBrush(const Color& cr) = 0;
				virtual void DestroyBrush(const Color& rc) = 0;

				virtual std::shared_ptr<Font> CreateFont(const FontProperties& font) = 0;
				virtual void DestroyFont(const FontProperties& font) = 0;
// 				virtual std::shared_ptr<Bitmap> CreateBitmap(const Color& cr) = 0;
// 				virtual void DestroyBitmap(const Color& rc) = 0;
			};
			extern IGDIResourceManager* GetGDIResourcesManager();
#if 0
			namespace Detail
			{
				//自动引用计数基类
				template<typename TClassChild, typename TResource,typename TKey>
				class ARCResource_base
					:public std::shared_ptr<TResource>
				{
				public:
					typedef typename std::remove_reference<TKey>::type key_type;
					typedef key_type& key_referece;
					typedef const key_type& key_const_referece;
					typedef std::shared_ptr<TResource> base_type;
				public:
					ARCResource_base(key_const_referece key)
						:_Mykey(key)
					{
						Create();
					}
					~ARCResource_base() 
					{
						Destory();
					}

					void ResetResource()
					{
						Create();
						Destory();
					}
				protected:
					inline void Create()
					{
						auto p = static_cast<TClassChild*>(this);
						p->Create();
					};
					inline void Destory()
					{
						auto p = static_cast<TClassChild*>(this);
						p->Destory();
					};
					inline operator key_referece()
					{
						return _Mykey;
					}
					inline operator key_referece()const
					{
						return _Mykey;
					}
				protected:
					key_const_referece _Mykey;
				};


				class ARCPen
					:public ARCResource_base<ARCPen, Pen, Color>
				{
				public:
					ARCPen(key_const_referece key);
					void Create();
					void Destory();
				};

				class ARCBrush
					:public ARCResource_base<ARCBrush, Brush, Color>
				{
				public:
					ARCBrush(key_const_referece key);
					void Create();
					void Destory();
				};
			}
			using namespace Detail;
#endif
		}
	}
}