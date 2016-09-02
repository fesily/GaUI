// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef GaUITYPE_H__
#define GaUITYPE_H__
#include <string>
#ifdef _MSC_VER
#include <stdint.h>
#else
#error "还没写"
#endif // MSVC
namespace GaUI
{
	namespace Basetype
	{
		/////////////////////////////////////////////////////////////////////////////
		// Classes declared in this file

		class CSize;
		class CPoint;
		class CRect;
		/////////////////////////////////////////////////////////////////////////////
		// CSize - An extent, similar to Windows SIZE structure.

		class CSize :
			public tagSIZE
		{
		public:

			// Constructors
			// construct an uninitialized size
			CSize() throw();
			// create from two integers
			CSize(
				_In_ int initCX,
				_In_ int initCY) throw();
			// create from another size
			CSize(_In_ const SIZE& initSize) throw();
			//移动语义
			CSize(_In_ SIZE&& initSize) throw();
			// create from a point
			CSize(_In_ POINT initPt) throw();
			// create from a DWORD: cx = LOWORD(dw) cy = HIWORD(dw)
			CSize(_In_ DWORD dwSize) throw();

			//赋值语句
			CSize& operator=(_In_ const SIZE& size)throw();
			CSize& operator=(_In_ SIZE&& size)throw();
			// Operations
			BOOL operator==(_In_ SIZE size) const throw();
			BOOL operator!=(_In_ SIZE size) const throw();
			void operator+=(_In_ SIZE size) throw();
			void operator-=(_In_ SIZE size) throw();
			void SetSize(_In_ int CX, _In_ int CY) throw();
			void SetSizeEmpty() throw();
			void IntersectSize(const CSize& size) throw();

			// Operators returning CSize values
			CSize operator+(_In_ SIZE size) const throw();
			CSize operator-(_In_ SIZE size) const throw();
			CSize operator-() const throw();

			// Operators returning CPoint values
			CPoint operator+(_In_ POINT point) const throw();
			CPoint operator-(_In_ POINT point) const throw();

			// Operators returning CRect values
			CRect operator+(_In_ const RECT* lpRect) const throw();
			CRect operator-(_In_ const RECT* lpRect) const throw();
		};

		/////////////////////////////////////////////////////////////////////////////
		// CPoint - A 2-D point, similar to Windows POINT structure.

		class CPoint :
			public tagPOINT
		{
		public:
			// Constructors

			// create an uninitialized point
			CPoint() throw();
			// create from two integers
			CPoint(
				_In_ int initX,
				_In_ int initY) throw();
			// create from another point
			CPoint(_In_ const POINT& initPt) throw();
			CPoint(_In_ POINT&& initPt) throw();
			// create from a size
			CPoint(_In_ SIZE initSize) throw();
			// create from an LPARAM: x = LOWORD(dw) y = HIWORD(dw)
			CPoint(_In_ LPARAM dwPoint) throw();

			// Operations
			CPoint& operator=(_In_ const POINT& initPt) throw();
			CPoint& operator=(_In_ POINT&& initPt) throw();
			// translate the point
			void Offset(
				_In_ int xOffset,
				_In_ int yOffset) throw();
			void Offset(_In_ POINT point) throw();
			void Offset(_In_ SIZE size) throw();
			void SetPoint(
				_In_ int X,
				_In_ int Y) throw();

			BOOL operator==(_In_ POINT point) const throw();
			BOOL operator!=(_In_ POINT point) const throw();
			void operator+=(_In_ SIZE size) throw();
			void operator-=(_In_ SIZE size) throw();
			void operator+=(_In_ POINT point) throw();
			void operator-=(_In_ POINT point) throw();

			// Operators returning CPoint values
			CPoint operator+(_In_ SIZE size) const throw();
			CPoint operator-(_In_ SIZE size) const throw();
			CPoint operator-() const throw();
			CPoint operator+(_In_ POINT point) const throw();

			// Operators returning CSize values
			CSize operator-(_In_ POINT point) const throw();

			// Operators returning CRect values
			CRect operator+(_In_ const RECT* lpRect) const throw();
			CRect operator-(_In_ const RECT* lpRect) const throw();
		};

		/////////////////////////////////////////////////////////////////////////////
		// CRect - A 2-D rectangle, similar to Windows RECT structure.

		class CRect :
			public tagRECT
		{
			// Constructors
		public:
			// uninitialized rectangle
			CRect() throw();
			// from left, top, right, and bottom
			CRect(
				_In_ int l,
				_In_ int t,
				_In_ int r,
				_In_ int b) throw();
			// copy constructor
			CRect(_In_ const RECT& srcRect) throw();
			CRect(_In_ RECT&& srcRect) throw();

			// from a pointer to another rect
			CRect(_In_ LPCRECT lpSrcRect) throw();
			// from a point and size
			CRect(
				_In_ POINT point,
				_In_ SIZE size) throw();
			// from two points
			CRect(
				_In_ POINT topLeft,
				_In_ POINT bottomRight) throw();

			// Attributes (in addition to RECT members)

			// retrieves the width
			int Width() const throw();
			// returns the height
			int Height() const throw();
			// returns the size
			CSize Size() const throw();
			// reference to the top-left point
			CPoint& TopLeft() throw();
			// reference to the bottom-right point
			CPoint& BottomRight() throw();
			// const reference to the top-left point
			const CPoint& TopLeft() const throw();
			// const reference to the bottom-right point
			const CPoint& BottomRight() const throw();
			// the geometric center point of the rectangle
			CPoint CenterPoint() const throw();
			// swap the left and right
			void SwapLeftRight() throw();
			static void WINAPI SwapLeftRight(_Inout_ LPRECT lpRect) throw();

			// convert between CRect and LPRECT/LPCRECT (no need for &)
			operator LPRECT() throw();
			operator LPCRECT() const throw();

			// returns TRUE if rectangle has no area
			BOOL IsRectEmpty() const throw();
			// returns TRUE if rectangle is at (0,0) and has no area
			BOOL IsRectNull() const throw();
			// returns TRUE if point is within rectangle
			BOOL PtInRect(_In_ POINT point) const throw();
			//是合法矩形
			bool IsNormalize()const throw();
			// Operations

			// set rectangle from left, top, right, and bottom
			void SetRect(
				_In_ int x1,
				_In_ int y1,
				_In_ int x2,
				_In_ int y2) throw();
			void SetRect(
				_In_ POINT topLeft,
				_In_ POINT bottomRight) throw();
			// empty the rectangle
			void SetRectEmpty() throw();
			// copy from another rectangle
			void CopyRect(_In_ LPCRECT lpSrcRect) throw();
			// TRUE if exactly the same as another rectangle
			BOOL EqualRect(_In_ LPCRECT lpRect) const throw();

			// Inflate rectangle's width and height by
			// x units to the left and right ends of the rectangle
			// and y units to the top and bottom.
			void InflateRect(
				_In_ int x,
				_In_ int y) throw();
			// Inflate rectangle's width and height by
			// size.cx units to the left and right ends of the rectangle
			// and size.cy units to the top and bottom.
			void InflateRect(_In_ SIZE size) throw();
			// Inflate rectangle's width and height by moving individual sides.
			// Left side is moved to the left, right side is moved to the right,
			// top is moved up and bottom is moved down.
			void InflateRect(_In_ LPCRECT lpRect) throw();
			void InflateRect(
				_In_ int l,
				_In_ int t,
				_In_ int r,
				_In_ int b) throw();

			// deflate the rectangle's width and height without
			// moving its top or left
			void DeflateRect(
				_In_ int x,
				_In_ int y) throw();
			void DeflateRect(_In_ SIZE size) throw();
			void DeflateRect(_In_ LPCRECT lpRect) throw();
			void DeflateRect(
				_In_ int l,
				_In_ int t,
				_In_ int r,
				_In_ int b) throw();

			// translate the rectangle by moving its top and left
			void OffsetRect(
				_In_ int x,
				_In_ int y) throw();
			void OffsetRect(_In_ SIZE size) throw();
			void OffsetRect(_In_ POINT point) throw();
			void NormalizeRect() throw();
			//格式化成所有值都是非负数的矩形
			void FormatPositiveRect() throw();

			// absolute position of rectangle
			void MoveToY(_In_ int y) throw();
			void MoveToX(_In_ int x) throw();
			void MoveToXY(
				_In_ int x,
				_In_ int y) throw();
			void MoveToXY(_In_ POINT point) throw();

			// set this rectangle to intersection of two others
			BOOL IntersectRect(
				_In_ LPCRECT lpRect1,
				_In_ LPCRECT lpRect2) throw();

			// set this rectangle to bounding union of two others
			BOOL UnionRect(
				_In_ LPCRECT lpRect1,
				_In_ LPCRECT lpRect2) throw();

			// set this rectangle to minimum of two others
			BOOL SubtractRect(
				_In_ LPCRECT lpRectSrc1,
				_In_ LPCRECT lpRectSrc2) throw();

			// Additional Operations
			CRect& operator=(_In_ const RECT& srcRect) throw();
			CRect& operator=(_In_ RECT&& srcRect) throw();
			BOOL operator==(_In_ const RECT& rect) const throw();
			BOOL operator!=(_In_ const RECT& rect) const throw();
			void operator+=(_In_ POINT point) throw();
			void operator+=(_In_ SIZE size) throw();
			void operator+=(_In_ LPCRECT lpRect) throw();
			void operator-=(_In_ POINT point) throw();
			void operator-=(_In_ SIZE size) throw();
			void operator-=(_In_ LPCRECT lpRect) throw();
			void operator&=(_In_ const RECT& rect) throw();
			void operator|=(_In_ const RECT& rect) throw();

			// Operators returning CRect values
			CRect operator+(_In_ POINT point) const throw();
			CRect operator-(_In_ POINT point) const throw();
			CRect operator+(_In_ LPCRECT lpRect) const throw();
			CRect operator+(_In_ SIZE size) const throw();
			CRect operator-(_In_ SIZE size) const throw();
			CRect operator-(_In_ LPCRECT lpRect) const throw();
			CRect operator&(_In_ const RECT& rect2) const throw();
			CRect operator|(_In_ const RECT& rect2) const throw();
			CRect MulDiv(
				_In_ int nMultiplier,
				_In_ int nDivisor) const throw();
		};
		//////////////////////////////////////////////////////////////////////////
		class Color
		{
		public:
			union 
			{
				struct 
				{
					unsigned char r;
					unsigned char g;
					unsigned char b;
					unsigned char a;
				};
				uint32_t value;
			};
		public:
			Color()
				:r(0), g(0), b(0), a(255)
			{}
			Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 255)
				:r(_r),g(_g),b(_b),a(_a)
			{}
			
			operator uint32_t&()
			{//为了使用hash
				return value;
			}
			inline int32_t Compare(const Color& cr)const
			{
				return value - cr.value;
			}
			inline bool operator==(const Color& cr)const
			{
				return Compare(cr) == 0;
			}
			inline bool operator!=(const Color& cr)const
			{
				return Compare(cr) != 0;
			}
			inline bool operator<(const Color& cr)const
			{
				return Compare(cr) < 0;
			}
			inline bool operator<=(const Color& cr)const
			{
				return Compare(cr) <= 0;
			}
			inline bool operator>(const Color& cr)const
			{
				return Compare(cr) > 0;
			}
			inline bool operator>=(const Color& cr)const
			{
				return Compare(cr) >= 0;
			}
		};
		class FontProperties
		{
		public:
			FontProperties()
				:size(0)
				,bold(false)
				,italic(false)
				,underline(false)
				,strikeline(false)
				,antialias(true)
				,verticalAntialias(false)
			{

			}
		public:
			inline bool Compare(const FontProperties& value)
			{
				if(fontFamily != value.fontFamily
				   && size == value.size
				   && bold == value.bold
				   && italic == value.italic
				   && underline == value.underline
				   && strikeline == value.strikeline
				   && antialias == value.antialias
				   && verticalAntialias == value.verticalAntialias)
					return true;
				return false;
			}
			inline bool operator==(const FontProperties& value)
			{
				return Compare(value);
			}
		public:
			std::wstring fontFamily;//字体名
			int32_t size;//字体大小
			bool bold;//粗体
			bool italic;//斜体
			bool underline;//下划线
			bool strikeline;//有向线
			bool antialias;//反锯齿
			bool verticalAntialias;//垂直反锯齿
		};
	}

	typedef Basetype::CPoint CPoint;
	typedef Basetype::CRect CRect;
	typedef Basetype::CSize CSize;
	typedef Basetype::Color Color;
	typedef Basetype::FontProperties FontProperties;
}

#include "GaUI_Type_Size.inl"
#include "GaUI_Type_Point.inl"
#include "GaUI_Type_Rect.inl"

#endif // GaUITYPE_H__
