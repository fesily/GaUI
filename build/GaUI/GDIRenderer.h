#pragma once
#include "Renderer.h"
#include "Element.h"
#include "GDIInterface.h"
namespace GaUI
{
	namespace Element
	{
		namespace Element_GDI
		{
			class GaSolidBorderElementRenderer
				:public IRendererEx<GaSolidBorderElement, GaSolidBorderElementRenderer, IGDIRenderTarget>
			{
			public:
				void Render(CRect bounds)override;
				void OnElementStateChanged()override;
			protected:
				void InitializeInternal()override;
				void FinalizeInternal()override;
			protected:
				Color					m_oldColor;
				std::shared_ptr<Pen>	m_pen;
				std::shared_ptr<Brush>	m_brush;
			};

			class GaGradientBackgroundElementRenderer
				:public IRendererEx<GaGradientBackgroundElement, GaGradientBackgroundElementRenderer, IGDIRenderTarget>
			{
			public:
				void Render(CRect bounds)override;
				void OnElementStateChanged()override;
			};

			class GaSolidLabelElementRenderer
				:public IRendererEx<GaSolidLabelElement, GaSolidBorderElementRenderer, IGDIRenderTarget>
			{
			public:
				GaSolidLabelElementRenderer();

				void Render(CRect bounds)override;
				void OnElementStateChanged()override;
			protected:
				void UpdateMinSize();

				void InitializeInternal()override;
				void FinalizeInternal()override;
				void RenderTargetChangedInternal(IGDIRenderTarget* oldTarget, IGDIRenderTarget* newTarget)override;
			protected:
				FontProperties m_oldFontProperties;
				std::shared_ptr<Font> m_font;
				int32_t m_oldMaxWidth;
			};
		}
	}
}