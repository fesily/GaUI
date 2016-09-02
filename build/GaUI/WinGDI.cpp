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
		}
	}
}