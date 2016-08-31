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
				//�Ժ������з�װ�Ĺ���ģ��
				typedef std::function<void(arg_const_reference)> product_type;
				template<typename Fn, bool isBind>
				struct factory
				{//Fn ��һ��std::function���� ��bind����
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
				struct factory<Fn, false>//Fn ��һ�������
				{
					typedef typename std::remove_reference<arg_const_reference>::type arg_type;
					typedef typename std::remove_reference<Fn>::type fn_type;
				public:
					//Tfn �����ʵ��������
					//���� �������� lambda��������
					template<typename Tfn>
					static product_type build(Tfn&& fn)
					{
						//��Tfn ������operator ;
						//�� Tfn��������� operator()�����
						typedef typename std::remove_reference<Tfn>::type Tfn_type;
						return build_second(std::forward<Tfn>(fn), &Tfn_type::operator());
					}

					//�޲��� ���Ա��������
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
					//�в���
					static product_type build_second(fn_type&& fn, void(fn_type::*)(arg_const_reference))
					{
						return std::move(fn);
					}
					static product_type build_second(fn_type&& fn, void(fn_type::*)(arg_const_reference)const)
					{
						return std::move(fn);
					}
#if 0//����fn_type& ����תΪconst fn_type&;
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

					//������������������,����ģ�����Ϊ������Ļ��� ��������������֧
					template<typename Tfn, typename Ret, typename Arg2>
					static product_type build_second(Tfn&& fn, Ret(fn_type::*)(Arg2))
					{
						static_assert(std::is_convertible_v<arg_type, Arg2>,
									  "��������Ĳ����ǲ�ƥ���,����");
						return [fn](arg_const_reference arg) mutable {
							fn(arg);
						}
					}

					template<typename Tfn, typename Ret, typename Arg2>
					static product_type build_second(Tfn&& fn, Ret(fn_type::*)(Arg2)const)
					{
						static_assert(std::is_convertible_v<arg_type, Arg2>,
									  "��������Ĳ����ǲ�ƥ���,����");
						return [fn](arg_const_reference arg) mutable {
							fn(arg);
						}
					}
				};
			public:
				//Ret(Arg) ��ָ���ݽ�����ֱ����һ������������,����class::test;
				//Ret(*)(Arg) ��ָһ��������ָ�� ����&class:test;
				template<typename Ret, typename Arg2>
				struct factory<std::function<Ret(Arg2)>, false>
				{
					typedef typename std::remove_reference<arg_const_reference>::type arg_type;
					static_assert(std::is_convertible<arg_type, Arg2>::value,
								  "��������Ĳ����ǲ�ƥ���,����");

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
								  "��������Ĳ����ǲ�ƥ���,����");

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
								  "��������Ĳ����ǲ�ƥ���,����");

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