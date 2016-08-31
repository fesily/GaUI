#ifndef GaUI_Type_Point_h__
#define GaUI_Type_Point_h__
namespace GaUI
{
	namespace Basetype
	{
		// CPoint
		inline CPoint::CPoint() throw()
		{
			x = 0;
			y = 0;
		}

		inline CPoint::CPoint(
			_In_ int initX,
			_In_ int initY) throw()
		{
			x = initX;
			y = initY;
		}

		inline CPoint::CPoint(const POINT& initPt) throw()
		{
			*(POINT*)this = initPt;
		}

		inline CPoint::CPoint(POINT&& initPt) throw()
		{
			*(POINT*)this = initPt;
		}


		inline CPoint::CPoint(_In_ SIZE initSize) throw()
		{
			*(SIZE*)this = initSize;
		}

		inline CPoint::CPoint(_In_ LPARAM dwPoint) throw()
		{
			x = (short)LOWORD(dwPoint);
			y = (short)HIWORD(dwPoint);
		}

		inline CPoint& CPoint::operator=(const POINT& initPt) throw()
		{
			*(POINT*)this = initPt;
			return *this;
		}

		inline CPoint& CPoint::operator=(POINT&& initPt) throw()
		{
			*(POINT*)this = initPt;
			return *this;
		}

		inline void CPoint::Offset(
			_In_ int xOffset,
			_In_ int yOffset) throw()
		{
			x += xOffset;
			y += yOffset;
		}

		inline void CPoint::Offset(_In_ POINT point) throw()
		{
			x += point.x;
			y += point.y;
		}

		inline void CPoint::Offset(_In_ SIZE size) throw()
		{
			x += size.cx;
			y += size.cy;
		}

		inline void CPoint::SetPoint(
			_In_ int X,
			_In_ int Y) throw()
		{
			x = X;
			y = Y;
		}

		inline BOOL CPoint::operator==(_In_ POINT point) const throw()
		{
			return (x == point.x && y == point.y);
		}

		inline BOOL CPoint::operator!=(_In_ POINT point) const throw()
		{
			return (x != point.x || y != point.y);
		}

		inline void CPoint::operator+=(_In_ SIZE size) throw()
		{
			x += size.cx;
			y += size.cy;
		}

		inline void CPoint::operator-=(_In_ SIZE size) throw()
		{
			x -= size.cx;
			y -= size.cy;
		}

		inline void CPoint::operator+=(_In_ POINT point) throw()
		{
			x += point.x;
			y += point.y;
		}

		inline void CPoint::operator-=(_In_ POINT point) throw()
		{
			x -= point.x;
			y -= point.y;
		}

		inline CPoint CPoint::operator+(_In_ SIZE size) const throw()
		{
			return CPoint(x + size.cx, y + size.cy);
		}

		inline CPoint CPoint::operator-(_In_ SIZE size) const throw()
		{
			return CPoint(x - size.cx, y - size.cy);
		}

		inline CPoint CPoint::operator-() const throw()
		{
			return CPoint(-x, -y);
		}

		inline CPoint CPoint::operator+(_In_ POINT point) const throw()
		{
			return CPoint(x + point.x, y + point.y);
		}

		inline CSize CPoint::operator-(_In_ POINT point) const throw()
		{
			return CSize(x - point.x, y - point.y);
		}

		inline CRect CPoint::operator+(_In_ const RECT* lpRect) const throw()
		{
			return CRect(lpRect) + *this;
		}

		inline CRect CPoint::operator-(_In_ const RECT* lpRect) const throw()
		{
			return CRect(lpRect) - *this;
		}

	}
}
#endif // GaUI_Type_Point_h__

