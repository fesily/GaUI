#ifndef GaUI_Type_Size_inl__
#define GaUI_Type_Size_inl__
namespace GaUI
{
	namespace Basetype
	{
		// CSize
		inline CSize::CSize() throw()
		{
			cx = 0;
			cy = 0;
		}

		inline CSize::CSize(
			_In_ int initCX,
			_In_ int initCY) throw()
		{
			cx = initCX;
			cy = initCY;
		}

		inline CSize::CSize(_In_ const SIZE& initSize) throw()
		{
			*(SIZE*)this = initSize;
		}

		inline CSize::CSize(_In_ SIZE&& initSize) throw()
		{
			*(SIZE*)this = initSize;
		}

		inline CSize::CSize(_In_ POINT initPt) throw()
		{
			*(POINT*)this = initPt;
		}

		inline CSize::CSize(_In_ DWORD dwSize) throw()
		{
			cx = (short)LOWORD(dwSize);
			cy = (short)HIWORD(dwSize);
		}

		inline CSize& CSize::operator=(_In_ const SIZE& size) throw()
		{
			*(SIZE*)this = size;
			return *this;
		}

		inline CSize& CSize::operator=(_In_ SIZE&& size) throw()
		{
			*(SIZE*)this = size;
			return *this;
		}

		inline BOOL CSize::operator==(_In_ SIZE size) const throw()
		{
			return (cx == size.cx && cy == size.cy);
		}

		inline BOOL CSize::operator!=(_In_ SIZE size) const throw()
		{
			return (cx != size.cx || cy != size.cy);
		}

		inline void CSize::operator+=(_In_ SIZE size) throw()
		{
			cx += size.cx;
			cy += size.cy;
		}

		inline void CSize::operator-=(_In_ SIZE size) throw()
		{
			cx -= size.cx;
			cy -= size.cy;
		}

		inline void CSize::SetSize(
			_In_ int CX,
			_In_ int CY) throw()
		{
			cx = CX;
			cy = CY;
		}

		inline void CSize::SetSizeEmpty() throw()
		{
			SetSize(0, 0);
		}

		inline void CSize::IntersectSize(const CSize& size) throw()
		{
			if(cx < size.cx)
				cx = size.cx;
			if(cy < size.cy)
				cy = size.cy;
		}

		inline CSize CSize::operator+(_In_ SIZE size) const throw()
		{
			return CSize(cx + size.cx, cy + size.cy);
		}

		inline CSize CSize::operator-(_In_ SIZE size) const throw()
		{
			return CSize(cx - size.cx, cy - size.cy);
		}

		inline CSize CSize::operator-() const throw()
		{
			return CSize(-cx, -cy);
		}

		inline CPoint CSize::operator+(_In_ POINT point) const throw()
		{
			return CPoint(cx + point.x, cy + point.y);
		}

		inline CPoint CSize::operator-(_In_ POINT point) const throw()
		{
			return CPoint(cx - point.x, cy - point.y);
		}

		inline CRect CSize::operator+(_In_ const RECT* lpRect) const throw()
		{
			return CRect(lpRect) + *this;
		}

		inline CRect CSize::operator-(_In_ const RECT* lpRect) const throw()
		{
			return CRect(lpRect) - *this;
		}
	}
}
#endif // GaUI_Type_Size_h__
