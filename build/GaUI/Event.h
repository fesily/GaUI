#pragma once
#include <list>
#include "EventBase.h"
#include "EventFactory.h"
namespace GaUI
{
	namespace Event
	{
		namespace detail
		{
			bool check_window(window_handle handle)
			{
				return false;
			}
			class event_interface
			{//�¼������ӿ�
			public:
				virtual ~event_interface() {};

				virtual void remove(event_handle) = 0;//�Ƴ�һ���¼�����
			};
			class docker_interface
			{//��װevent_handle������ӿ�
			public:
				virtual ~docker_interface() {};

				virtual event_interface* get_event() const = 0;
			};

			class docker_base
				:public docker_interface
			{//��װ�� ��������
			public:
				event_interface* event_ptr;//�¼�����ָ��
				bool flag_deleted;//��Ҫɾ���Լ���־
				const bool unignorable;//���ɺ���

				docker_base(event_interface* event_prt_, bool unignorable_flag)
					:event_ptr(event_prt_), unignorable(unignorable_flag)
					, flag_deleted(false)
				{

				}
				detail::event_interface* get_event() const override
				{
					return event_ptr;
				}
			};
			class event_base
				:public event_interface
			{
			public:
				event_base()
					:emitting_count_(0)
					, flag_deleted(false)
					, dockers_(nullptr)
				{

				}
				~event_base()
				{
					clear();
				}

				std::size_t length()const
				{
					//ȫ����TODO
					return dockers_ ? dockers_->size() : 0;
				}

				void clear()
				{
					//ȫ����TODO
					if(dockers_)
					{
						dockers_->clear();
						dockers_ = nullptr;
					}
				}
				void remove(event_handle evt) override
				{
					//ȫ����TODO
					if(dockers_)
					{
						auto evt_ = reinterpret_cast<docker_base*>(evt);
						//��һ������������ ��ֹ���̷߳���ʱ��ɾ����������ɺ�ɾ���ö���
						if(emitting_count_ > 1)
						{//��ǰ���������̷߳����������,�ӳ�ɾ���¼�����;
							evt_->flag_deleted = true;
							flag_deleted = true;
						}
						dockers_->remove(evt_);
					}
				}
			protected:
				event_handle _m_emplace(docker_base* docker_ptr, bool front)
				{
					//ȫ����TODO
					if(!dockers_)
						dockers_ = new std::list<docker_base *>;

					auto evt = reinterpret_cast<event_handle>(docker_ptr);
					if(front)
						dockers_->emplace_front(docker_ptr);
					else
						dockers_->emplace_back(docker_ptr);

					//ע���¼����evt
					return evt;
				}
			protected:
				class emit_counter
				{//�ӳ�ɾ����
				public:
					emit_counter(event_base* base)
						:evt_(base)
					{
						++evt_->emitting_count_;
					}
					~emit_counter()
					{
						if((0 == --evt_->emitting_count_) && evt_->flag_deleted)
						{//������ʶ���Ϊ0,�����ж�����Ҫɾ��,��Ѱ�Ҹ�ɾ������
							evt_->flag_deleted = false;
							for(auto iter = evt_->dockers_->begin(); iter != evt_->dockers_->end();)
							{
								if((*iter)->flag_deleted)
									iter = evt_->dockers_->erase(iter);
								else
									++iter;
							}
						}
					}
				private:
					event_base* const evt_;
				};
				unsigned emitting_count_;//��ǰ���ʸö�����߳�����;
				bool flag_deleted;//��ʾdockers_�б����ж�����Ҫɾ��;
				std::list<docker_base* >* dockers_;
			};
		}

		struct general_events;

		template<typename Arg>
		class basic_event
			:public detail::event_base, private factory::factory_wrapper<Arg>
		{
		public:
			struct docker
				:public detail::docker_base
			{//��װ��
				std::function<void(arg_const_reference)> invoke;//�¼��������õĺ���

				docker(basic_event* evt, std::function<void(arg_const_reference)>&& ivk, bool unignorable)
					:docker_base(evt, unignorable), invoke(std::move(ivk))
				{}
				docker(basic_event* evt, std::function<const void(arg_const_reference)>& ivk, bool unignorable)
					:docker_base(evt, unignorable), invoke(ivk)
				{}
			};
		public:
			template<typename TClass,typename TMethod>
			event_handle attach(TClass* point, TMethod TClass::* method)
			{
				return connect(std::bind(method, point));
			}
			template<typename Function>
			event_handle connect_front(Function&& fn)
			{
				return connect(std::forward<Function>(fn), true);
			}

			event_handle connect(void(*fn)(arg_const_reference))
			{
				return connect([fn](arg_const_reference arg) {
					fn(arg);
				});
			}

			template<typename Function>
			event_handle connect(Function&& fn, bool in_front = false)
			{
				return _m_emplace(CreateDocker(std::forward<Function>(fn), false), in_front);
			}

			template<typename Function>
			event_handle operator()(Function&& fn)
			{
				return connect(std::forward<Function>(fn));
			}

			template<typename Function>
			event_handle connect_unignorable(Function&& fn, bool in_front = false)
			{
				return _m_emplace(CreateDocker(std::forward<Function>(fn), true), in_front);
			}
		protected:
			template<typename Function>
			inline docker* CreateDocker(Function&& fn, bool unignorable)
			{
				typedef typename std::remove_reference<Function>::type prototype;
				return new docker(
					this,
					factory<prototype,
					std::is_bind_expression<prototype>::value/*�����Bind��,��ôģ�������һ����*/>::build(std::forward<Function>(fn)), unignorable);
			}

#ifdef __USE_STD_EX__
			template<typename Function>//�����ģ���Ǻ���ָ��,���ߺ�����
			inline docker* CreateDocker(typename std::enable_if<std::is_function<Function>::value, Function>::type& fn, bool unignorable)
			{
				typedef typename std::remove_reference<Function>::type prototype;
				return new docker(
					this,
					factory<prototype,
					std::is_bind_expression<prototype>::value/*�����Bind��,��ôģ�������һ����*/>::build(std::forward<Function>(fn)), unignorable);
			}
#endif
		public:
			//���������Ѿ�ע����¼���������
			void emit(arg_const_reference& arg, window_handle handle_)
			{
				//ȫ����TODO
				if(!dockers_)
					return;

				emit_counter ec(this);//ʹ�ü����� ����,Ӧ��ֻ��һ������������

				const auto& end = dockers_->end();
				for(auto iter = dockers_->begin(); iter != end; ++iter)
				{//����������
					const auto& var = *iter;
					if(var->flag_deleted)
						continue;

					static_cast<docker*>(var)->invoke(arg);

					if(handle_ && (!detail::check_window(handle_)))
						break;
					if(arg.propagation_stoped())
					{
						for(++iter; iter != end; ++iter)
						{
							const auto& var = static_cast<docker*>(*iter);

							if(var->unignorable || var->flag_deleted)
								continue;

							var->invoke(arg);
							if(handle_ && (!detail::check_window(handle_)))
								break;
						}
						break;
					}
				}
			}
		};
		
		/// provides some fundamental events that every widget owns.
		struct general_events
		{
			virtual ~general_events() {};
			basic_event<arg_mouse> mouse_enter;	///< the cursor enters the window
			basic_event<arg_mouse> mouse_move;	///< the cursor moves on the window
			basic_event<arg_mouse> mouse_leave;	///< the cursor leaves the window
			basic_event<arg_mouse> mouse_down;	///< the user presses the mouse button
			basic_event<arg_mouse> mouse_up;	///< the user presses the mouse button
			basic_event<arg_click> click;		///< the window is clicked, but occurs after mouse_down and before mouse_up
			basic_event<arg_mouse> dbl_click;	///< the window is double clicked
			basic_event<arg_wheel> mouse_wheel;	///< the mouse wheel rotates while the window has focus
			basic_event<arg_dropfiles>	mouse_dropfiles; ///< the mouse drops some external data while the window enable accepting files
			basic_event<arg_expose>	expose;		///< the visibility changes
			basic_event<arg_focus>	focus;		///< the window receives or loses keyboard focus
			basic_event<arg_keyboard>	key_press;   ///< a key is pressed while the window has focus. event code is event_code::key_press
			basic_event<arg_keyboard>	key_release; ///< a key is released while the window has focus. event code is event_code::key_release
			basic_event<arg_keyboard>	key_char;	///< a character, whitespace or backspace is pressed. event code is event_code::key_char
			basic_event<arg_keyboard>	shortkey;	///< a defined short key is pressed. event code is event_code::shortkey

			basic_event<arg_move>		move;		///< the window changes position
			basic_event<arg_resizing>	resizing;	///< the window is changing its size
			basic_event<arg_resized>	resized;	///< the window is changing its size

			basic_event<arg_destroy>	destroy;	///< the window is destroyed, but occurs when all children have been destroyed
		};
		typedef basic_event<arg_Notify>	EventNotify;
	}
}
