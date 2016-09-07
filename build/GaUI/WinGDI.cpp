#include "stdafx.h"
#include "WinGDI.h"

namespace GaUI
{
	namespace Window
	{
		namespace GDI
		{
			
			Pen::Pen(int nPenStyle, int nWidth, COLORREF crColor)
			{
				CPen::CreatePen(nPenStyle, nWidth, crColor);
			}

			Brush::Brush(COLORREF crColor)
			{
				CBrush::CreateSolidBrush(crColor);
			}

			Region::Region(int32_t left, int32_t top, int32_t right, int32_t bottom, bool bRectangle)
			{
				if(bRectangle)
					CRgn::CreateRectRgn(left, top, right, bottom);
				else
					CRgn::CreateEllipticRgn(left, top, right, bottom);
			}

			Region::Region(const CRect& rc, bool bRectangle)
			{
				if(bRectangle)
					CRgn::CreateRectRgnIndirect(&rc);
				else
					CRgn::CreateEllipticRgnIndirect(&rc);
			}

			Region::Region(WTL::CRgn&& value)
				:CRgn(value.m_hRgn)
			{

			}

			Region::Region(const WTL::CRgn& value)
				:CRgn(value.m_hRgn)
			{

			}

			Region::Region(const Region& rgn1, const Region& rgn2, int32_t CombineMode)
			{
				CRgn::CreateRectRgn(0, 0, 1, 1);
				CRgn::CombineRgn(rgn1, rgn2, CombineMode);
			}
			//////////////////////////////////////////////////////////////////////////
			Region DC::GetClipRgn()const
			{
				WTL::CRgn rgn;
				CDC::GetClipRgn(rgn);
				return rgn;
			}

			void DC::DrawText(const std::wstring& text, CRect& rc, UINT format)
			{
				CDC::DrawText(text.c_str(), (int)text.length(), rc, format);
			}

			CSize DC::MeasureBuffer(const std::wstring& Text, int32_t TabSize)
			{
				return MeasureBuffer(Text.c_str(), Text.length(), TabSize);
			}

			CSize DC::MeasureBuffer(const wchar_t* Text, int32_t TabSize)
			{
				return MeasureBuffer(Text, wcslen(Text), TabSize);
			}

			CSize DC::MeasureBuffer(const wchar_t* Text, int32_t CharCount, int32_t TabSize)
			{
				CSize size;
				if(TabSize == -1)
					::GetTextExtentPoint32(m_hDC, Text, CharCount, &size);
				else
					size = CSize(CDC::GetTabbedTextExtent(Text, CharCount, 1, &TabSize));
				return size;
			}

			CSize DC::MeasureWrapLineBuffer(const std::wstring& Text, int32_t maxWidth)
			{
				return MeasureWrapLineBuffer(Text.c_str(), Text.length(), maxWidth);
			}

			CSize DC::MeasureWrapLineBuffer(const wchar_t* Text, int32_t maxWidth)
			{
				return MeasureWrapLineBuffer(Text, wcslen(Text), maxWidth);
			}

			CSize DC::MeasureWrapLineBuffer(const wchar_t* Text, int32_t CharCount, int32_t maxWidth)
			{
				ATLASSERT(false);
				CSize size;
				int32_t lineCount = 0;
				const wchar_t* reading = Text;
				INT* dx = new INT[CharCount];
				while (*reading)
				{
					INT fit = 0;
					::GetTextExtentExPoint(m_hDC, reading, CharCount - (reading - Text), maxWidth, &fit, dx, &size);
					reading += fit;
					lineCount++;
				}
				delete[] dx;
				size.cx = 0;
				size.cy *= lineCount;///
				return size;
			}

		}
	}
}