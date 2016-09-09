#pragma once
#include <list>
#include "EventCode.h"
namespace GaUI
{
	namespace Event
	{
		struct event_handle_impl {};
		typedef event_handle_impl* event_handle;
		struct window_handle_impl {};
		typedef window_handle_impl* window_handle;
		struct native_window_handle_impl {};
		typedef native_window_handle_impl* native_window_handle;

		namespace Arg
		{
			class event_arg
			{//所有事件属性的基本类
			public:
				event_arg() :stop_propagation_(false) {}
				virtual ~event_arg() {}


				void stop_propagation()const
				{
					stop_propagation_ = true;
				}
				bool propagation_stoped() const
				{
					return stop_propagation_;
				}
			private:
				mutable bool stop_propagation_;//禁止继续广播标记
			};

			struct arg_mouse
				:public event_arg
			{
				event_code evt_code;
				window_handle handle_;
				CPoint pos;

				bool left_button;
				bool mid_button;
				bool right_buton;
				bool atl;
				bool shift;
				bool ctrl;

				bool is_left_button() const
				{
					return false;
				}
			};

			struct arg_wheel : public arg_mouse
			{
				ENUM_CLASS_BEGIN(wheel)
					vertical,
					horizontal
					ENUM_CLASS_END()
			public:
				wheel which;
				bool upwards;
				int32_t distance;
			};

			struct arg_dropfiles : public event_arg
			{
				window_handle handle_;	    ///<  A handle to the event window
				CPoint pos;	            ///<  cursor position in the event window
				std::list<std::string>	files;	///<  external filenames
			};

			struct arg_expose : public event_arg
			{
				window_handle handle_;	    ///<  A handle to the event window
				bool exposed;	                ///< the window is visible?
			};

			struct arg_focus : public event_arg
			{
				/// A constant to indicate how keyboard focus emitted.
				ENUM_CLASS_BEGIN(reason)
					general,	///< the focus is received by OS native window manager.
					tabstop,	///< the focus is received by pressing tab.
					mouse_press ///< the focus is received by pressing a mouse button.
					ENUM_CLASS_END()

					window_handle handle_;	    ///<  A handle to the event window
				native_window_handle receiver;	///< it is a native window handle, and specified which window receives focus
				bool	getting;						///< the window received focus?
				reason	focus_reason;					///< determines how the widget receives keyboard focus, it is ignored when 'getting' is equal to false
			};

			struct arg_keyboard : public event_arg
			{
				event_code evt_code;	    ///< it is event_code::key_press in current event
				window_handle handle_;	    ///<  A handle to the event window
				mutable wchar_t key;	///< the key corresponding to the key pressed
				mutable bool ignore;	    ///< this member is only available for key_char event, set 'true' to ignore the input.
				bool ctrl;	                ///< keyboard Ctrl is pressed?
				bool shift;	                ///< keyboard Shift is pressed
			};

			struct arg_move : public event_arg
			{
				window_handle handle_;	    ///<  A handle to the event window
				int32_t x;	                        ///< 
				int32_t y;	                        ///< 
			};

			struct arg_resized : public event_arg
			{
				window_handle handle_;	    ///<  A handle to the event window
				int32_t width;	                ///< new width in pixels.
				int32_t height;	            ///< new height in pixels.
			};

			struct arg_resizing : public event_arg
			{
				ENUM_CLASS_BEGIN(window_border)
					none,
					left, right, top, bottom,
					top_left, top_right, bottom_left, bottom_right
					ENUM_CLASS_END()

					window_handle handle_;	    ///<  A handle to the event window
				window_border border;	        ///< the window is being resized by moving border
				mutable int32_t width;	        ///< new width in pixels. If it is modified, the window's width will be the modified value
				mutable int32_t height;	    ///< new height in pixels. If it is modified, the window's height will be the modified value
			};

			struct arg_unload : public event_arg
			{
				window_handle handle_;	    ///<  A handle to the event window
				mutable bool cancel;	        ///< 
			};

			struct arg_destroy : public event_arg
			{
				window_handle handle_;	    ///<  A handle to the event window
			};
			/// a higher level event argument than just mouse down
			struct arg_click : public event_arg
			{
				window_handle handle_;	    ///<  A handle to the event window
				const arg_mouse* mouse_args{};	///< If it is not null, it refers to the mouse arguments for click event emitted by mouse, nullptr otherwise.
			};

			struct arg_Notify
			{
				window_handle handle_;
			};
		}
	}
	using namespace Event::Arg;
}