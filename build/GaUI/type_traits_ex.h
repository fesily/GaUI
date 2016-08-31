#pragma once
#include <type_traits>
#include "defines.h"
#ifdef __USE_STD_EX__
namespace std
{
	template<typename _Tx>
	struct is_bind_expression<const _Tx>
		:is_bind_expression<_Tx>
	{
	};

	template<typename _Tx>
	struct is_bind_expression<volatile _Tx>
		:is_bind_expression<_Tx>
	{
	};

	template<typename _Tx>
	struct is_bind_expression<const volatile _Tx>
		:is_bind_expression<_Tx>
	{
	};
}
#endif
