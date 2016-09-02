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
			class IGDITarget
				:public IRenderTarget
			{
			public:
				virtual DC* GetDC() = 0;
			};

			class IGDIResourceManager
				:public Interface
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
		}
	}
}