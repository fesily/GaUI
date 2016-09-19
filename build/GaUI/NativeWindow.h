#pragma once
#include "NativeWindowInterface.h"
#include <functional>
namespace GaUI
{
	namespace Native
	{
		namespace Timer
		{
			struct Timer {};
			typedef Timer* HTimer;
			struct TimerInfomation
			{
			public:
				typedef std::function<void(void)> CallBackFunction;
			public:
				TimerInfomation(const CallBackFunction& fn, uint32_t nElapse = 10)
					:func(fn), elapse(nElapse)
				{
				}
				TimerInfomation(CallBackFunction&& fn , uint32_t nElapse = 10)
					:func(fn),elapse(nElapse)
				{
				}
				TimerInfomation(const TimerInfomation& value)
					:func(value.func)
					, name(value.name)
					, elapse(value.elapse)
				{

				}
				TimerInfomation(TimerInfomation&& value)
					:func(std::forward<CallBackFunction>(value.func))
					, name(std::forward<std::wstring>(value.name))
					, elapse(value.elapse)
				{

				}
			public:
				CallBackFunction func;
				std::wstring name;
				uint32_t elapse;
			};
			class INativeTimerServer :public virtual Interface
			{
			public:
				typedef TimerInfomation::CallBackFunction CallBackFunction;
			public:
				//创建对象
				virtual HTimer SetTimer(const TimerInfomation& info) = 0;
				virtual HTimer SetTimer(TimerInfomation&& info) = 0;

				virtual void DestroyTimer(HTimer hTimer) = 0;
				virtual void DestroyTimer (const std::wstring& name) = 0;
			};
		}
		class IWindowForm
			:public virtual Interface
		{

		};

		extern INativeController*	InitializeWindowNativeController(HINSTANCE hInstance);
		extern IWindowForm*			GetWindowFormFromHandle(HWND hwnd);
		extern IWindowForm*			GetWindowForm(INativeWindow* window);
		extern void					UninitizlizeWindowNativeController(INativeController* controller);
		using namespace Timer;
	}
}