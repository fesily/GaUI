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
			};
			class Bitmap :public WTL::CBitmap
			{
			};
			class DC :public WTL::CDC
			{
			};
		}
	}
}