#ifndef GaUI_Type_Rect_inl__
#define GaUI_Type_Rect_inl__
namespace GaUI
{
	namespace Basetype
	{
		// CRect
		inline CRect::CRect() throw()
		{
			left = 0;
			top = 0;
			right = 0;
			bottom = 0;
		}

		inline CRect::CRect(
			_In_ int l,
			_In_ int t,
			_In_ int r,
			_In_ int b) throw()
		{
			left = l;
			top = t;
			right = r;
			bottom = b;
		}

		inline CRect::CRect(_In_ const RECT& srcRect) throw()
		{
			::CopyRect(this, &srcRect);
		}

		inline CRect::CRect(RECT&& srcRect) throw()
		{
			*(RECT*)this = srcRect;
		}

		inline CRect::CRect(_In_ LPCRECT lpSrcRect) throw()
		{
			::CopyRect(this, lpSrcRect);
		}

		inline CRect::CRect(
			_In_ POINT point,
			_In_ SIZE size) throw()
		{
			right = (left = point.x) + size.cx;
			bottom = (top = point.y) + size.cy;
		}

		inline CRect::CRect(
			_In_ POINT topLeft,
			_In_ POINT bottomRight) throw()
		{
			left = topLeft.x;
			top = topLeft.y;
			right = bottomRight.x;
			bottom = bottomRight.y;
		}

		inline int CRect::Width() const throw()
		{
			return right - left;
		}

		inline int CRect::Height() const throw()
		{
			return bottom - top;
		}

		inline CSize CRect::Size() const throw()
		{
			return CSize(right - left, bottom - top);
		}

		inline CPoint& CRect::TopLeft() throw()
		{
			return *((CPoint*)this);
		}

		inline CPoint& CRect::BottomRight() throw()
		{
			return *((CPoint*)this + 1);
		}

		inline const CPoint& CRect::TopLeft() const throw()
		{
			return *((CPoint*)this);
		}

		inline const CPoint& CRect::BottomRight() const throw()
		{
			return *((CPoint*)this + 1);
		}

		inline CPoint CRect::CenterPoint() const throw()
		{
			return CPoint((left + right) / 2, (top + bottom) / 2);
		}

		inline void CRect::SwapLeftRight() throw()
		{
			SwapLeftRight(LPRECT(this));
		}

		inline void WINAPI CRect::SwapLeftRight(_Inout_ LPRECT lpRect) throw()
		{
			LONG temp = lpRect->left;
			lpRect->left = lpRect->right;
			lpRect->right = temp;
		}

		inline CRect::operator LPRECT() throw()
		{
			return this;
		}

		inline CRect::operator LPCRECT() const throw()
		{
			return this;
		}

		inline BOOL CRect::IsRectEmpty() const throw()
		{
			return ::IsRectEmpty(this);
		}

		inline BOOL CRect::IsRectNull() const throw()
		{
			return (left == 0 && right == 0 && top == 0 && bottom == 0);
		}

		inline bool CRect::IsNormalize() const
		{
			return left < right && top < bottom;
		}

		inline BOOL CRect::PtInRect(_In_ POINT point) const throw()
		{
			return ::PtInRect(this, point);
		}

		inline void CRect::SetRect(
			_In_ int x1,
			_In_ int y1,
			_In_ int x2,
			_In_ int y2) throw()
		{
			::SetRect(this, x1, y1, x2, y2);
		}

		inline void CRect::SetRect(
			_In_ POINT topLeft,
			_In_ POINT bottomRight) throw()
		{
			::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
		}

		inline void CRect::SetRectEmpty() throw()
		{
			::SetRectEmpty(this);
		}

		inline void CRect::CopyRect(_In_ LPCRECT lpSrcRect) throw()
		{
			::CopyRect(this, lpSrcRect);
		}

		inline BOOL CRect::EqualRect(_In_ LPCRECT lpRect) const throw()
		{
			return ::EqualRect(this, lpRect);
		}

		inline void CRect::InflateRect(
			_In_ int x,
			_In_ int y) throw()
		{
			::InflateRect(this, x, y);
		}

		inline void CRect::InflateRect(_In_ SIZE size) throw()
		{
			::InflateRect(this, size.cx, size.cy);
		}

		inline void CRect::DeflateRect(
			_In_ int x,
			_In_ int y) throw()
		{
			::InflateRect(this, -x, -y);
		}

		inline void CRect::DeflateRect(_In_ SIZE size) throw()
		{
			::InflateRect(this, -size.cx, -size.cy);
		}

		inline void CRect::OffsetRect(
			_In_ int x,
			_In_ int y) throw()
		{
			::OffsetRect(this, x, y);
		}

		inline void CRect::OffsetRect(_In_ POINT point) throw()
		{
			::OffsetRect(this, point.x, point.y);
		}

		inline void CRect::OffsetRect(_In_ SIZE size) throw()
		{
			::OffsetRect(this, size.cx, size.cy);
		}

		inline void CRect::MoveToY(_In_ int y) throw()
		{
			bottom = Height() + y;
			top = y;
		}

		inline void CRect::MoveToX(_In_ int x) throw()
		{
			right = Width() + x;
			left = x;
		}

		inline void CRect::MoveToXY(
			_In_ int x,
			_In_ int y) throw()
		{
			MoveToX(x);
			MoveToY(y);
		}

		inline void CRect::MoveToXY(_In_ POINT pt) throw()
		{
			MoveToX(pt.x);
			MoveToY(pt.y);
		}

		inline BOOL CRect::IntersectRect(
			_In_ LPCRECT lpRect1,
			_In_ LPCRECT lpRect2) throw()
		{
			return ::IntersectRect(this, lpRect1, lpRect2);
		}

		inline BOOL CRect::UnionRect(
			_In_ LPCRECT lpRect1,
			_In_ LPCRECT lpRect2) throw()
		{
			return ::UnionRect(this, lpRect1, lpRect2);
		}

		inline CRect& CRect::operator=(_In_ const RECT& srcRect) throw()
		{
			::CopyRect(this, &srcRect);
			return *this;
		}

		inline CRect& CRect::operator=(RECT&& srcRect) throw()
		{
			*(RECT*)this = srcRect;
			return *this;
		}

		inline BOOL CRect::operator==(_In_ const RECT& rect) const throw()
		{
			return ::EqualRect(this, &rect);
		}

		inline BOOL CRect::operator!=(_In_ const RECT& rect) const throw()
		{
			return !::EqualRect(this, &rect);
		}

		inline void CRect::operator+=(_In_ POINT point) throw()
		{
			::OffsetRect(this, point.x, point.y);
		}

		inline void CRect::operator+=(_In_ SIZE size) throw()
		{
			::OffsetRect(this, size.cx, size.cy);
		}

		inline void CRect::operator+=(_In_ LPCRECT lpRect) throw()
		{
			InflateRect(lpRect);
		}

		inline void CRect::operator-=(_In_ POINT point) throw()
		{
			::OffsetRect(this, -point.x, -point.y);
		}

		inline void CRect::operator-=(_In_ SIZE size) throw()
		{
			::OffsetRect(this, -size.cx, -size.cy);
		}

		inline void CRect::operator-=(_In_ LPCRECT lpRect) throw()
		{
			DeflateRect(lpRect);
		}

		inline void CRect::operator&=(_In_ const RECT& rect) throw()
		{
			::IntersectRect(this, this, &rect);
		}

		inline void CRect::operator|=(_In_ const RECT& rect) throw()
		{
			::UnionRect(this, this, &rect);
		}

		inline CRect CRect::operator+(_In_ POINT pt) const throw()
		{
			CRect rect(*this);
			::OffsetRect(&rect, pt.x, pt.y);
			return rect;
		}

		inline CRect CRect::operator-(_In_ POINT pt) const throw()
		{
			CRect rect(*this);
			::OffsetRect(&rect, -pt.x, -pt.y);
			return rect;
		}

		inline CRect CRect::operator+(_In_ SIZE size) const throw()
		{
			CRect rect(*this);
			::OffsetRect(&rect, size.cx, size.cy);
			return rect;
		}

		inline CRect CRect::operator-(_In_ SIZE size) const throw()
		{
			CRect rect(*this);
			::OffsetRect(&rect, -size.cx, -size.cy);
			return rect;
		}

		inline CRect CRect::operator+(_In_ LPCRECT lpRect) const throw()
		{
			CRect rect(this);
			rect.InflateRect(lpRect);
			return rect;
		}

		inline CRect CRect::operator-(_In_ LPCRECT lpRect) const throw()
		{
			CRect rect(this);
			rect.DeflateRect(lpRect);
			return rect;
		}

		inline CRect CRect::operator&(_In_ const RECT& rect2) const throw()
		{
			CRect rect;
			::IntersectRect(&rect, this, &rect2);
			return rect;
		}

		inline CRect CRect::operator|(_In_ const RECT& rect2) const throw()
		{
			CRect rect;
			::UnionRect(&rect, this, &rect2);
			return rect;
		}

		inline BOOL CRect::SubtractRect(
			_In_ LPCRECT lpRectSrc1,
			_In_ LPCRECT lpRectSrc2) throw()
		{
			return ::SubtractRect(this, lpRectSrc1, lpRectSrc2);
		}

		inline void CRect::NormalizeRect() throw()
		{
			int nTemp;
			if(left > right)
			{
				nTemp = left;
				left = right;
				right = nTemp;
			}
			if(top > bottom)
			{
				nTemp = top;
				top = bottom;
				bottom = nTemp;
			}
		}
		inline void CRect::FormatPositiveRect() throw()
		{
			if(left < 0)
				left = 0;
			if(top < 0)
				top = 0;
			if(right < 0)
				right = 0;
			if(bottom < 0)
				bottom = 0;
		}

		inline void CRect::InflateRect(_In_ LPCRECT lpRect) throw()
		{
			left -= lpRect->left;
			top -= lpRect->top;
			right += lpRect->right;
			bottom += lpRect->bottom;
		}

		inline void CRect::InflateRect(
			_In_ int l,
			_In_ int t,
			_In_ int r,
			_In_ int b) throw()
		{
			left -= l;
			top -= t;
			right += r;
			bottom += b;
		}

		inline void CRect::DeflateRect(_In_ LPCRECT lpRect) throw()
		{
			left += lpRect->left;
			top += lpRect->top;
			right -= lpRect->right;
			bottom -= lpRect->bottom;
		}

		inline void CRect::DeflateRect(
			_In_ int l,
			_In_ int t,
			_In_ int r,
			_In_ int b) throw()
		{
			left += l;
			top += t;
			right -= r;
			bottom -= b;
		}

		inline CRect CRect::MulDiv(
			_In_ int nMultiplier,
			_In_ int nDivisor) const throw()
		{
			return CRect(
				::MulDiv(left, nMultiplier, nDivisor),
				::MulDiv(top, nMultiplier, nDivisor),
				::MulDiv(right, nMultiplier, nDivisor),
				::MulDiv(bottom, nMultiplier, nDivisor));
		}
	}
}
#endif // GaUI_Type_Rect_h__
