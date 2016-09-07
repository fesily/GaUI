#pragma once
namespace GaUI
{
	namespace Window
	{
		namespace GDI
		{
			class Pen :public WTL::CPen
			{
			public:
				Pen(int nPenStyle, int nWidth, COLORREF crColor);
			};
			class Brush :public WTL::CBrush
			{
			public:
				Brush(COLORREF crColor);
			};
			class Font :public WTL::CFont
			{

			};
			class Bitmap :public WTL::CBitmap
			{
			};
			class Region :public WTL::CRgn
			{
			public:
				Region(WTL::CRgn&& value);
				Region(const WTL::CRgn& value);

				Region(int32_t left, int32_t top, int32_t right, int32_t bottom, bool bRectangle);
				Region(const CRect& rc, bool bRectangle);
				Region(const Region& rgn1, const Region& rgn2, int32_t CombineMode);
			};
			class DC :public WTL::CDC
			{
			public:
				Region GetClipRgn()const;

				///string
				void DrawText(const std::wstring& text, CRect& rc, UINT format);
				CSize MeasureBuffer(const std::wstring& Text, int32_t TabSize = -1);
				CSize MeasureBuffer(const wchar_t* Text, int32_t TabSize = -1);
				CSize MeasureBuffer(const wchar_t* Text, int32_t CharCount, int32_t TabSize = -1);
				CSize MeasureWrapLineBuffer(const std::wstring& Text, int32_t maxWidth);
				CSize MeasureWrapLineBuffer(const wchar_t* Text, int32_t maxWidth);
				CSize MeasureWrapLineBuffer(const wchar_t* Text, int32_t CharCount, int32_t maxWidth);
			};
		}
	}
}