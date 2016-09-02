#pragma once
#include <memory>
#include "defines.h"

#ifdef __USE_STD_EX__

namespace std
{
	// TEMPLATE FUNCTION make_unique
	template<class _Ty,
		class... _Types> inline
		typename enable_if<!is_array<_Ty>::value,
		unique_ptr<_Ty> >::type make_unique(_Types&&... _Args)
	{	// make a unique_ptr
		return (unique_ptr<_Ty>(new _Ty(_STD forward<_Types>(_Args)...)));
	}

	template<class _Ty> inline
		typename enable_if<is_array<_Ty>::value && extent<_Ty>::value == 0,
		unique_ptr<_Ty> >::type make_unique(size_t _Size)
	{	// make a unique_ptr
		typedef typename remove_extent<_Ty>::type _Elem;
		return (unique_ptr<_Ty>(new _Elem[_Size]()));
	}

	template<class _Ty,
		class... _Types>
		typename enable_if<extent<_Ty>::value != 0,
		void>::type make_unique(_Types&&...)
	{
		static_assert(false,"这种调用不支持");
		return (unique_ptr<_Ty>(new _Ty(_STD forward<_Types>(_Args)...)));
	}

}
#endif // __USE_STD_EX__
