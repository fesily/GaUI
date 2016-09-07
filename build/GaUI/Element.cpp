#include "stdafx.h"
#include "Element.h"

namespace GaUI
{
	namespace Element
	{


		GaSolidBorderElement::GaSolidBorderElement()
			: m_eShape(Rectangle)
			, m_color(this, Color(255, 255, 255))
		{
		}
		GaSolidBorderElement::~GaSolidBorderElement()
		{

		}

//////////////////////////////////////////////////////////////////////////
		GaGradientBackgroundElement::GaGradientBackgroundElement()
			: m_eShape(Rectangle)
			, m_color1(this)
			, m_color2(this)
			, m_eDirection(this, Horizontal)
		{

		}
		GaGradientBackgroundElement::~GaGradientBackgroundElement()
		{

		}

		void GaGradientBackgroundElement::SetColor(const Color& value1, const Color& value2)
		{
			bool bNoity = false;
			if(m_color1 != value1)
			{
				bNoity = true;
				m_color1.Set(value1);
			}
			if(m_color2 != value2)
			{
				bNoity = true;
				m_color2.Set(value2);
			}
			if(bNoity)
				NotifyRendererStateChanged();
		}

//////////////////////////////////////////////////////////////////////////
		GaSolidLabelElement::GaSolidLabelElement()
			: m_isWrapLine(this, false)
			, m_isEllipse(this, false)
			, m_isMulitiline(this, false)
			, m_isWrapLineHeightCalculation(this, false)
			, m_hAlignment(this, Alignment::Left)
			, m_vAlignment(this, Alignment::Top)
			, m_font(this)
			, m_color(this)
			, m_text(this)
		{
			m_font->fontFamily = L"Lucida Console";
			m_font->size = 12;
		}

		GaSolidLabelElement::~GaSolidLabelElement()
		{
			m_renderer->Finalize();
		}

		void GaSolidLabelElement::SetAlignments(const Alignment& h, const Alignment& v)
		{
			bool bNoity = false;
			if(m_hAlignment != h)
			{
				bNoity = true;
				m_hAlignment.Set(h);
			}
			if(m_vAlignment != v)
			{
				bNoity = true;
				m_vAlignment.Set(v);
			}
			if(bNoity)
				NotifyRendererStateChanged();
		}

	}
}