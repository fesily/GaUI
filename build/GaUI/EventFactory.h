#pragma once
#include "type_traits_ex.h"
#include <functional>
namespace GaUI
{
	namespace Event
	{
		namespace factory
		{
			template<typename Arg>
			class factory_wrapper
			{
			public:
				typedef const typename std::remove_reference<Arg>::type& arg_const_reference;
			public:
				//对函数进行封装的工厂模块
				typedef std::function<void(arg_const_reference)> product_type;
				template<typename Fn, bool isBind>
				struct factory
				{//Fn 是一个std::function对象 由bind而来
					static product_type build(Fn&& fn)
					{
						return std::move(fn);
					}
					static product_type build(const Fn& fn)
					{
						return fn;
					}
				};

				template<typename Fn>
				struct factory<Fn, false>//Fn 是一个类对象
				{
					typedef typename std::remove_reference<arg_const_reference>::type arg_type;
					typedef typename std::remove_reference<Fn>::type fn_type;
				public:
					//Tfn 是类的实例化对象
					//绑定类 函数重载 lambda是匿名类
					template<typename Tfn>
					static product_type build(Tfn&& fn)
					{
						//绑定Tfn 对象中operator ;
						//既 Tfn类必须重载 operator()运算符
						typedef typename std::remove_reference<Tfn>::type Tfn_type;
						return build_second(std::forward<Tfn>(fn), &Tfn_type::operator());
					}

					//无参数 类成员变量调用
					template<typename Tfn, typename Ret>
					static product_type build_second(Tfn&& fn, Ret(fn_type::*)())
					{
						return [fn](arg_const_reference) mutable {
							fn();
						};
					}

					template<typename Tfn, typename Ret>
					static product_type build_second(Tfn&& fn, Ret(fn_type::*)()const)
					{
						return [fn](arg_const_reference) mutable {
							fn();
						};
					}
				public:
					//有参数
					static product_type build_second(fn_type&& fn, void(fn_type::*)(arg_const_reference))
					{
						return std::move(fn);
					}
					static product_type build_second(fn_type&& fn, void(fn_type::*)(arg_const_reference)const)
					{
						return std::move(fn);
					}
#if 0//参数fn_type& 可以转为const fn_type&;
					static product_type build_second(fn_type& fn, void(fn_type::*)(arg_const_reference))
					{
						return fn;
					}
					static product_type build_second(fn_type& fn, void(fn_type::*)(arg_const_reference)const)
					{
						return fn;
					}
#endif
					static product_type build_second(const fn_type& fn, void(fn_type::*)(arg_const_reference))
					{
						return fn;
					}
					static product_type build_second(const fn_type& fn, void(fn_type::*)(arg_const_reference)const)
					{
						return fn;
					}

					//如果输入参数是派生类,并且模板参数为派生类的基类 则走以下两个分支
					template<typename Tfn, typename Ret, typename Arg2>
					static product_type build_second(Tfn&& fn, Ret(fn_type::*)(Arg2))
					{
						static_assert(std::is_convertible_v<arg_type, Arg2>,
									  "这个函数的参数是不匹配的,请检查");
						return [fn](arg_const_reference arg) mutable {
							fn(arg);
						}
					}

					template<typename Tfn, typename Ret, typename Arg2>
					static product_type build_second(Tfn&& fn, Ret(fn_type::*)(Arg2)const)
					{
						static_assert(std::is_convertible_v<arg_type, Arg2>,
									  "这个函数的参数是不匹配的,请检查");
						return [fn](arg_const_reference arg) mutable {
							fn(arg);
						}
					}
				};
			public:
				//Ret(Arg) 是指传递进来的直接是一个函数的名称,比如class::test;
				//Ret(*)(Arg) 是指一个函数的指针 比如&class:test;
				template<typename Ret, typename Arg2>
				struct factory<std::function<Ret(Arg2)>, false>
				{
					typedef typename std::remove_reference<arg_const_reference>::type arg_type;
					static_assert(std::is_convertible<arg_type, Arg2>::value,
								  "这个函数的参数是不匹配的,请检查");

					typedef std::function<Ret(Arg2)> factory_template_type;
					static product_type build(const factory_template_type& fn)
					{
						return [fn](arg_const_reference arg) mutable {
							fn(arg);
						}
					}
					static product_type build_second(product_type&& fn)
					{
						return std::move(fn);
					}
				};
				template<typename Ret>
				struct factory<std::function<Ret()>, false>
				{
					static product_type build(const std::function<Ret()>& fn)
					{
						return[fn](arg_const_reference) mutable {
							fn();
						};
					}
				};

				template<typename Ret>
				struct factory <Ret(*)(), false>
				{
					static product_type build(Ret(*fn)())
					{
						return[fn](arg_const_reference) mutable {
							fn();
						};
					}
				};
				template<typename Ret, typename Arg2>
				struct factory<Ret(*)(Arg2), false>
				{
					typedef typename std::remove_reference<arg_const_reference>::type arg_type;
					static_assert(std::is_convertible<arg_type, Arg2>::value,
								  "这个函数的参数是不匹配的,请检查");

					static product_type build(Ret(*fn)(Arg2))
					{
						return[fn](arg_const_reference arg) mutable {
							fn(arg);
						};
					}
				};

				template<typename Ret>
				struct factory<Ret(), false>
				{
					static product_type build(Ret(*fn)())
					{
						return[fn](arg_const_reference) {
							fn();
						};
					}
				};
				template<typename Ret, typename Arg2>
				struct factory<Ret(Arg2), false>
				{
					typedef typename std::remove_reference<arg_const_reference>::type arg_type;
					static_assert(std::is_convertible<arg_type, Arg2>::value,
								  "这个函数的参数是不匹配的,请检查");

					static product_type build(Ret(*fn)(Arg2))
					{
						return[fn](arg_const_reference arg) mutable {
							fn(arg);
						};
					}
				};
			};
		}
	}
}