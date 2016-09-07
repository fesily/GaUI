#include "stdafx.h"
#include "GDIRenderer.h"
#include "WinGDI.h"

namespace GaUI
{
	namespace Element
	{
		namespace Element_GDI
		{

			void ResetPen(std::shared_ptr<Pen>& Resource, Color& oldValue, const Color& newValue)
			{
				IGDIResourceManager* resourceManager = GetGDIResourcesManager();
				resourceManager->DestroyPen(oldValue);
				oldValue = newValue;
				Resource = resourceManager->CreatePen(oldValue);
			}

			void ResetFont(std::shared_ptr<Font>& Resource, FontProperties& oldValue, const FontProperties& newValue)
			{
				IGDIResourceManager* resourceManager = GetGDIResourcesManager();
				resourceManager->DestroyFont(oldValue);
				oldValue = newValue;
				Resource = resourceManager->CreateFont(oldValue);
			}

			void GaSolidBorderElementRenderer::Render(CRect bounds)
			{
				if(m_oldColor.a > 0)
				{
					auto pDC = m_renderTarget->GetDC();
					pDC->SelectPen(*m_pen);
					pDC->SelectBrush(*m_brush);
					switch(m_element->m_eShape)
					{
					case eElementShape::Ellipse:
						pDC->Ellipse(bounds.left, bounds.top, bounds.right - 1, bounds.bottom - 1);
						break;
					case eElementShape::Rectangle:
						pDC->Rectangle(bounds.left, bounds.top, bounds.right - 1, bounds.bottom - 1);
						break;
					}
				} 
			}

			void GaSolidBorderElementRenderer::OnElementStateChanged()
			{
				const Color& color = m_element->m_color;
				if(m_oldColor != color)
					ResetPen(m_pen, m_oldColor, color);
			}

			void GaSolidBorderElementRenderer::InitializeInternal()
			{
				IGDIResourceManager* resourceManager = GetGDIResourcesManager();
				m_oldColor = m_element->m_color;
 				m_pen = resourceManager->CreatePen(m_oldColor);
 				m_brush = resourceManager->CreateBrush(Color());
			}

			void GaSolidBorderElementRenderer::FinalizeInternal()
			{
				IGDIResourceManager* resourceManager = GetGDIResourcesManager();
				resourceManager->DestroyPen(m_oldColor);
				resourceManager->DestroyBrush(Color());
			}

			//////////////////////////////////////////////////////////////////////////
			void GaGradientBackgroundElementRenderer::Render(CRect bounds)
			{
				const Color& color1 = m_element->m_color1;
				const Color& color2 = m_element->m_color2;
				if(color1.a > 0 || color2.a > 0)
				{
					TRIVERTEX vertices[4];
					GRADIENT_TRIANGLE triangles[2];
					
					vertices[0].x = bounds.left;
					vertices[0].y = bounds.top;
					vertices[1].x = bounds.left;
					vertices[1].y = bounds.bottom;
					vertices[2].x = bounds.right;
					vertices[2].y = bounds.bottom;
					vertices[3].x = bounds.right;
					vertices[3].y = bounds.top;

					triangles[0].Vertex1 = 0;
					triangles[0].Vertex2 = 1;
					triangles[0].Vertex3 = 2;
					triangles[1].Vertex1 = 0;
					triangles[1].Vertex2 = 2;
					triangles[1].Vertex3 = 3;

					if(m_element->m_eDirection == GaGradientBackgroundElement::Horizontal)
					{
						vertices[0].Red = color1.r << 8;
						vertices[0].Green = color1.g << 8;
						vertices[0].Blue = color1.b << 8;
						vertices[0].Alpha = 0xFF00;

						vertices[1].Red = color1.r << 8;
						vertices[1].Green = color1.g << 8;
						vertices[1].Blue = color1.b << 8;
						vertices[1].Alpha = 0xFF00;

						vertices[2].Red = color2.r << 8;
						vertices[2].Green = color2.g << 8;
						vertices[2].Blue = color2.b << 8;
						vertices[2].Alpha = 0xFF00;

						vertices[3].Red = color2.r << 8;
						vertices[3].Green = color2.g << 8;
						vertices[3].Blue = color2.b << 8;
						vertices[3].Alpha = 0xFF00;
					}
					else
					{
						vertices[0].Red = color1.r << 8;
						vertices[0].Green = color1.g << 8;
						vertices[0].Blue = color1.b << 8;
						vertices[0].Alpha = 0xFF00;

						vertices[1].Red = color2.r << 8;
						vertices[1].Green = color2.g << 8;
						vertices[1].Blue = color2.b << 8;
						vertices[1].Alpha = 0xFF00;

						vertices[2].Red = color2.r << 8;
						vertices[2].Green = color2.g << 8;
						vertices[2].Blue = color2.b << 8;
						vertices[2].Alpha = 0xFF00;

						vertices[3].Red = color1.r << 8;
						vertices[3].Green = color1.g << 8;
						vertices[3].Blue = color1.b << 8;
						vertices[3].Alpha = 0xFF00;
					}

					switch(m_element->m_eShape)
					{
					case Element::Rectangle:
					{
						m_renderTarget->GetDC()->GradientFill(vertices, 6, triangles, 2, GRADIENT_FILL_TRIANGLE);
					}
					break;
					case Element::Ellipse:
					{
						auto pDC = m_renderTarget->GetDC();

						Region ellipseRegion(bounds.left, bounds.top, bounds.right + 1, bounds.bottom + 1, false);
						Region oldRegion = pDC->GetClipRgn();
						Region newRegion(oldRegion, ellipseRegion, RGN_AND);

						pDC->SelectClipRgn(newRegion);
						pDC->GradientFill(vertices, 6, triangles, 2, GRADIENT_FILL_TRIANGLE);
						pDC->SelectClipRgn(oldRegion);
					}
					break;
					}
				}
			}

			void GaGradientBackgroundElementRenderer::OnElementStateChanged()
			{

			}
//////////////////////////////////////////////////////////////////////////
			GaSolidLabelElementRenderer::GaSolidLabelElementRenderer()
				:m_oldMaxWidth(-1)
			{

			}


			void GaSolidLabelElementRenderer::Render(CRect bounds)
			{
				const Color& color = m_element->m_color;
				if(color.a > 0)
				{
					auto pDC = m_renderTarget->GetDC();
					pDC->SelectFont(*m_font);
					pDC->SetTextColor(color);

					UINT format = DT_NOPREFIX;
					if(m_element->m_isMulitiline || m_element->m_isWrapLine)
						format |= DT_EDITCONTROL;
					else
					{
						format |= DT_SINGLELINE;
						switch(m_element->m_vAlignment)
						{
						case Alignment::Top:
							format |= DT_TOP;
							break;
						case Alignment::Center:
							format |= DT_VCENTER;
							break;
						case Alignment::Bottom:
							format |= DT_BOTTOM;
							break;
						}
					}
					switch(m_element->m_hAlignment)
					{
					case Alignment::Left:
						format |= DT_LEFT;
						break;
					case Alignment::Center:
						format |= DT_CENTER;
						break;
					case Alignment::Right:
						format |= DT_RIGHT;
						break;
					}
					if(m_element->m_isWrapLine)
						format |= DT_WORDBREAK;
					if(m_element->m_isEllipse)
						format |= DT_END_ELLIPSIS;
					m_renderTarget->GetDC()->DrawText(m_element->m_text, bounds, format);
					if(m_oldMaxWidth != bounds.Width())
					{
						m_oldMaxWidth = bounds.Width();
						UpdateMinSize();
					}
				}
			}

			void GaSolidLabelElementRenderer::OnElementStateChanged()
			{
				const FontProperties& font = m_element->m_font;
				if(m_oldFontProperties != font)
					ResetFont(m_font, m_oldFontProperties, font);
				UpdateMinSize();
			}

			void GaSolidLabelElementRenderer::UpdateMinSize()
			{
				if(m_renderTarget)
				{
					auto pDC = m_renderTarget->GetDC();
					pDC->SelectFont(*m_font);
					CSize size;
					const std::wstring& text = m_element->m_text;
					if(m_element->m_isWrapLine)
					{
						if(m_element->m_isWrapLineHeightCalculation)
						{
							if(m_oldMaxWidth == -1 || text.length() == 0)
								size = pDC->MeasureBuffer(L" ");
							else
								size = pDC->MeasureWrapLineBuffer(text, m_oldMaxWidth);
						}
					}
					else
						size = text.length() == 0 ? pDC->MeasureBuffer(L" ") : pDC->MeasureBuffer(text);
					m_minSize = CSize(m_element->m_isEllipse ? 0 : size.cx, size.cy);
				}
				else
					m_minSize.SetSizeEmpty();
			}

			void GaSolidLabelElementRenderer::InitializeInternal()
			{
				m_oldFontProperties = m_element->m_font;
				m_font = GetGDIResourcesManager()->CreateFont(m_oldFontProperties);
			}

			void GaSolidLabelElementRenderer::FinalizeInternal()
			{
				GetGDIResourcesManager()->DestroyFont(m_oldFontProperties);
			}

			void GaSolidLabelElementRenderer::RenderTargetChangedInternal(IGDIRenderTarget* oldTarget, IGDIRenderTarget* newTarget)
			{
				UpdateMinSize();
			}

		}
	}
}