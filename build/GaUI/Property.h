#pragma once
#include "type_traits_ex.h"
namespace GaUI
{
	namespace GaProperty
	{
		template<typename _Ty>
		class _property_base_value
		{
		public:
			typedef typename std::remove_reference<_Ty>::type value_type;
			typedef value_type* value_point;
			typedef value_type& value_reference;
			typedef const value_type& value_const_reference;
		public:
			_property_base_value() {}
			_property_base_value(const _property_base_value& _Other)
				:_Myvalue(_Other._Myvalue)
			{

			}
			_property_base_value(_property_base_value&& _Other)
				:_Myvalue(_Other._Myvalue)
			{

			}

#if (defined _MSC_VER) && (_MSC_VER <= 1600)
			template<typename _T1>
			_property_base_value(const _T1& _t1)
				:_Myvalue(_t1)
			{
			}
			template<typename _T1, typename _T2>
			_property_base_value(const _T1& _t1, const _T2& _t2)
				: _Myvalue(_t1, _t2)
			{
			}

			template<typename _T1, typename _T2, typename _T3>
			_property_base_value(const _T1& _t1, const _T2& _t2, const _T3& _t3)
				: _Myvalue(_t1, _t2, _t3)
			{
			}

			template<typename _T1, typename _T2, typename _T3, typename _T4>
			_property_base_value(const _T1& _t1, const _T2& _t2, const _T3& _t3, const _T4& _t4)
				: _Myvalue(_t1, _t2, _t3, _t4)
			{
			}

			template<typename _T1, typename _T2, typename _T3, typename _T4, typename _T5>
			_property_base_value(const _T1& _t1, const _T2& _t2, const _T3& _t3, const _T4& _t4, const _T5& _t5)
				: _Myvalue(_t1, _t2, _t3, _t4, _t5)
			{
			}

			template<typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6>
			_property_base_value(const _T1& _t1, const _T2& _t2, const _T3& _t3, const _T4& _t4, const _T5& _t5, const _T6& _t6)
				: _Myvalue(_t1, _t2, _t3, _t4, _t5, _t6)
			{
			}

			template<typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7>
			_property_base_value(const _T1& _t1, const _T2& _t2, const _T3& _t3, const _T4& _t4, const _T5& _t5, const _T6& _t6, const _T7& _t7)
				: _Myvalue(_t1, _t2, _t3, _t4, _t5, _t6, _t7)
			{
			}

#else
			template<typename ...Arg>
			_property_base_value(Arg&&... args)
				: _Myvalue(std::forward<Arg>(args)...)
			{

			}
#endif // _MSC_VER && _MSC_VER <= 1600


			template<typename _TValue>
			void Set(const _TValue& value)
			{
				_Myvalue = value;
			}

			value_reference Get()const throw()
			{
				return _Myvalue;
			}

			value_reference Get()throw()
			{
				return _Myvalue;
			}

			value_point operator->()throw()
			{
				return &_Myvalue;
			}

			value_point operator->()const throw()
			{
				return &_Myvalue;
			}
		private:
			value_type _Myvalue;
		};

		template<typename _TContainer>
		class _property_base_container
		{
		public:
			typedef _TContainer container_type;
			typedef container_type* container_type_pointer;
		public:
			_property_base_container(container_type_pointer _containerPoint)
				: container_point(_containerPoint)
			{}
			_property_base_container(const _property_base_container& _Other)
				: container_point(_Other.m_pContainer)
			{

			}
			_property_base_container(_property_base_container&& _Other)
				: container_point(_Other.m_pContainer)
			{

			}
			void InitializeContainer(container_type_pointer _containerPoint)
			{
				container_point = _containerPoint;
			}

			inline container_type_pointer GetContainer()
			{
				return container_point;
			}
		protected:
			container_type_pointer container_point;
		};

		template<typename _Ty, typename _TContainer,
			void(_TContainer::*func_put)(const _Ty&) = nullptr,
			_Ty&(_TContainer::*func_get)(void) = nullptr>
		class Property
			:public _property_base_value<_Ty>, public _property_base_container<_TContainer>
		{
		private:
			struct _Call_lock
			{
				_Call_lock()
					:_Is_call(false)
				{

				}
				void operator=(const bool& _call)
				{
					_Is_call = _call;
				}
				void operator=(bool&& _call)
				{
					_Is_call = _call;
				}
				operator bool&()
				{
					return _Is_call;
				}
				operator bool&()const
				{
					return _Is_call;
				}
				bool _Is_call;
			};
		public:
			Property(container_type_pointer _containerPoint = nullptr)
				:_property_base_container(_containerPoint)
			{}
			Property(const Property& _Other)
				:_property_base_value(std::forward(_Other._Myvalue))
				, _property_base_container(std::forward(_Other.container_point))
			{}
			Property(Property&& _Other)
				:_property_base_value(std::forward(_Other._Myvalue))
				, _property_base_container(std::forward(_Other.container_point))
			{}

			Property& operator=(const Property& _Other)
			{
				_Myvalue = _Other._Myvalue;
				container_point = _Other.container_point;
				return *this;
			}
			Property& operator=(Property&& _Other)
			{
				_Myvalue = _Other._Myvalue;
				container_point = _Other.container_point;
				return *this;
			}

#if (defined _MSC_VER) && (_MSC_VER <= 1600)
			template<typename _T1>
			Property(container_type_pointer _container, const _T1& _t1)
				: _property_base_value(_t1)
				, _property_base_container(_container)
			{
			}
			template<typename _T1, typename _T2>
			Property(container_type_pointer _container, const _T1& _t1, const _T2& _t2)
				: _property_base_value(_t1, _t2)
				, _property_base_container(_container)
			{
			}

			template<typename _T1, typename _T2, typename _T3>
			Property(container_type_pointer _container, const _T1& _t1, const _T2& _t2, const _T3& _t3)
				: _property_base_value(_t1, _t2, _t3)
				, _property_base_container(_container)
			{
			}

			template<typename _T1, typename _T2, typename _T3, typename _T4>
			Property(container_type_pointer _container, const _T1& _t1, const _T2& _t2, const _T3& _t3, const _T4& _t4)
				: _property_base_value(_t1, _t2, _t3, _t4)
				, _property_base_container(_container)
			{
			}

			template<typename _T1, typename _T2, typename _T3, typename _T4, typename _T5>
			Property(container_type_pointer _container, const _T1& _t1, const _T2& _t2, const _T3& _t3, const _T4& _t4, const _T5& _t5)
				: _property_base_value(_t1, _t2, _t3, _t4, _t5)
				, _property_base_container(_container)
			{
			}

			template<typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6>
			Property(container_type_pointer _container, const _T1& _t1, const _T2& _t2, const _T3& _t3, const _T4& _t4, const _T5& _t5, const _T6& _t6)
				: _property_base_value(_t1, _t2, _t3, _t4, _t5, _t6)
				, _property_base_container(_container)
			{
			}

			template<typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6, typename _T7>
			Property(container_type_pointer _container, const _T1& _t1, const _T2& _t2, const _T3& _t3, const _T4& _t4, const _T5& _t5, const _T6& _t6, const _T7& _t7)
				: _property_base_value(_t1, _t2, _t3, _t4, _t5, _t6, _t7)
				, _property_base_container(_container)
			{
			}

#else
			template<typename ...Arg>
			Property(container_type_pointer _container, Arg&&... args)
				: _property_base_value(std::forward<Arg>(args)...)
				, _property_base_container(_container)
			{

			}
#endif // _MSC_VER && _MSC_VER <= 1600

			void operator=(value_const_reference value)
			{
				if(func_put == nullptr || _Is_call)
					this->Set(value);
				else
				{
					_Is_call = true;
					(GetContainer()->*func_put)(value);
					_Is_call = false;
				}
			}

			operator value_reference()throw()
			{
				if(func_get == nullptr)
					return Get();
				else
					return (GetContainer()->*func_get)();
			}
			operator value_reference()const throw()
			{
				if(func_get == nullptr)
					return Get();
				else
					return (GetContainer()->*func_get)();
			}
			operator value_type*()throw()
			{
				if(func_get == nullptr)
					return &Get();
				else
					return &(GetContainer()->*func_get)();
			}
			operator value_type*()const throw()
			{
				if(func_get == nullptr)
					return &Get();
				else
					return &(GetContainer()->*func_get)();
			}



			friend bool operator==(const Property& value1, const Property& value2)
			{
				return value1.operator==(value2);
			}
			friend bool operator!=(const Property& value1, const Property& value2)
			{
				return value1.operator!=(value2);
			}
			inline bool operator==(const Property& value)
			{
				return operator==(value.Get());
			}
			inline bool operator==(value_const_reference value)
			{
				return Get() == value;
			}
			inline bool operator!=(const Property& value)
			{
				return operator!=(value.Get());
			}
			inline bool operator!=(value_const_reference value)
			{
				return Get() != value;
			}
		private:
			_Call_lock _Is_call;//∑¿÷π—≠ª∑∏≥÷µ
		};
	}

	using GaProperty::Property;
}