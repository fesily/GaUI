#include "stdafx.h"
#include "NativeWindow.h"
#include <map>
namespace GaUI
{
	namespace Native
	{
		class WindowTimerServer
			:public INativeTimerServer
		{
			class TimerWnd
				:public CWindowImpl<TimerWnd, ATL::CWindow, ATL::CWinTraits<WS_OVERLAPPEDWINDOW, WS_EX_CONTROLPARENT>>
			{
			public:
				DECLARE_WND_CLASS(_T("timerWnd"))
			public:
				TimerWnd(WindowTimerServer* server)
					:m_pServer(server)
				{
					Create(NULL, CRect(), _T("timerWnd"));
					ShowWindow(SW_HIDE);

				}
				~TimerWnd()
				{
					DestroyWindow();
					m_pServer = nullptr;
				}
				virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT & lResult, DWORD dwMsgMapID) override
				{
					if(uMsg == WM_TIMER)
					{
						m_pServer->Timer(wParam);
						return TRUE;
					}
					return FALSE;
				}
			protected:
				WindowTimerServer* m_pServer;
			};
		public:
			WindowTimerServer()
				:m_timerWnd(this)
			{
			}
			~WindowTimerServer()
			{
				if(!m_mapTimer.empty())
				{
					for each (auto& var in m_mapTimer)
						m_timerWnd.KillTimer(var.first);
					m_mapTimer.clear();
				}
			}
			void Timer(uint32_t id)
			{
				auto iter = m_mapTimer.find(id);
				if(iter != m_mapTimer.end())
				{
					const auto& func = iter->second.func;
					if(func)
						func();
				}
			}

			virtual HTimer SetTimer(const TimerInfomation & info) override
			{
				auto id = FindAvailableID();
				if(id != -1)
				{
					m_timerWnd.SetTimer(id, info.elapse, nullptr);
					auto iter = m_mapTimer.emplace(id, info);
					if(iter.second)
						return reinterpret_cast<HTimer>(&iter.first);
				}
				return nullptr;
			}
			virtual HTimer SetTimer(TimerInfomation && info) override
			{
				auto id = FindAvailableID();
				if(id != -1)
				{
					m_timerWnd.SetTimer(id, info.elapse, nullptr);
					auto iter = m_mapTimer.emplace(id, std::forward<TimerInfomation>(info));
					if(iter.second)
						return reinterpret_cast<HTimer>(&iter.first);
				}
				return nullptr;
			}

			virtual void DestroyTimer(HTimer hTimer) override
			{
				typedef decltype(m_mapTimer)::iterator iterator;
				if(hTimer != nullptr)
				{
					auto pIter = reinterpret_cast<iterator*>(hTimer);
					m_timerWnd.KillTimer((*pIter)->first);
					m_mapTimer.erase(*pIter);
				}
			}
			virtual void DestroyTimer(const std::wstring & name) override
			{
				auto end = m_mapTimer.end();
				for(auto iter = m_mapTimer.begin(); iter != end; iter++)
				{
					if(iter->second.name == name)
					{
						m_timerWnd.KillTimer(iter->first);
						m_mapTimer.erase(iter);
						break;
					}
				}
			}
		protected:
			uint32_t FindAvailableID()
			{
				decltype(m_mapTimer)::key_compare compare;
				uint32_t i = 0;
				auto end = m_mapTimer.rend();
				for(auto iter = m_mapTimer.rbegin(); iter != end; iter++, i++)
				{
					if(!compare(iter->first, i))
					{
						iter++;
						if(compare(iter->first, i))
							return i;
					}
				}
				return -1;
			}
		protected:
			TimerWnd m_timerWnd;
			std::map<uint32_t, TimerInfomation, std::less<uint32_t>> m_mapTimer;
		};


		class WindowForm
			:public INativeWindow, public IWindowForm
		{
		public:
			WindowForm(HWND parent, std::wstring className, HINSTANCE hInstance)
			{
				GetWndClassInfo().m_wc.lpszClassName = className.c_str();
				Create(parent, CRect());
			}

			BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT & result, DWORD uMsgID)override
			{
				return GetCurrentController()->HandleMessage(hWnd, uMsg, wParam, lParam, result);
			}
			

			bool HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT & result)
			{
				switch(uMsg)
				{
				case WM_CREATE:
				case WM_DESTROY:
				default:
					break;
				}
				return false;
			}

			virtual void RedrawWindow() override
			{
				if(IsWindow())
					SendMessage(WM_PAINT);
			}

		};
		class WindowsController
			:public virtual INativeController, public virtual INativeWindowServer
		{
		public:
			WindowsController(HINSTANCE hInstance)
				:m_hInstance(hInstance)
			{}
			// 通过 INativeController 继承
			virtual INativeWindowServer * WindowServer() override
			{
				return this;
			}

			virtual bool HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT & result) override
			{
				bool bHandled = false;
				WindowForm* window = reinterpret_cast<WindowForm*>(hWnd);
				bHandled = window->HandleMessage(uMsg, wParam, lParam, result);
				switch(uMsg)
				{
				case WM_CLOSE:
					if(!bHandled)
					{
						window->ShowWindow(SW_HIDE);
						if(window != m_pMainWnd)
							bHandled = true;
					}
					break;
				case WM_DESTROY:
					DestroyNatvieWindow(window);
					break;
				}
				if(window->m_hWnd == m_hMainWnd && uMsg == WM_DESTROY)
				{
					DestroyAllNativeWindow();
					::PostQuitMessage(0);
				}
				return bHandled;
			}
			// 通过 INativeWindowServer 继承
			virtual INativeWindow * CreateNatvieWindow() override
			{
				ATLASSERT(!m_hMainWnd || ::IsWindow(m_hMainWnd));
				WindowForm* form = new WindowForm(m_hMainWnd, _T("GaWindow"), m_hInstance);
				if(form->IsWindow())
				{
					m_mapWindows.emplace(form->m_hWnd, form);
				}
				else
				{
					ATLASSERT(FALSE);
					delete form;
					form = nullptr;
				}
				return form;
			}
			virtual void DestroyNatvieWindow(INativeWindow * window) override
			{
				auto iter = m_mapWindows.find(window->m_hWnd);
				if(iter != m_mapWindows.end())
					m_mapWindows.erase(iter);
				if(window->IsWindow())
					window->DestroyWindow();
				delete window;
			}
			virtual INativeWindow * GetMainNatvieWindow() override
			{
				return m_pMainWnd;
			}
			virtual INativeWindow * GetNatvieWindow(const CPoint & location) override
			{
				HWND hWnd = ::WindowFromPoint(location);
				return FindWindowFromHandle(hWnd);
			}

			virtual void Run(INativeWindow * windows) override
			{
				m_pMainWnd = windows;
				m_hMainWnd = m_pMainWnd->m_hWnd;
				ATLASSERT(m_pMainWnd->IsWindow());
				GetModule()->GetMessageLoop()->Run();
				m_pMainWnd = nullptr;
				m_hMainWnd = nullptr;
			}
			WindowForm* FindWindowFromHandle(HWND hWnd)
			{
				auto iter = m_mapWindows.find(m_hMainWnd);
				if(iter != m_mapWindows.end())
					return iter->second;
				return nullptr;
			}
		protected:
			void DestroyAllNativeWindow()
			{
				for each (auto& var in m_mapWindows)
				{
					var.second->ShowWindow(SW_HIDE);
					DestroyNatvieWindow(var.second);
				}
				m_mapWindows.clear();
			}
		protected:
			WindowTimerServer m_TimerServer;

			HWND m_hMainWnd;
			INativeWindow* m_pMainWnd;
			HINSTANCE	m_hInstance;
			std::map<HWND, WindowForm*> m_mapWindows;
		};

		extern INativeController* InitializeWindowNativeController(HINSTANCE hInstance)
		{
			return new WindowsController(hInstance);
		}

		extern IWindowForm* GetWindowFormFromHandle(HWND hwnd)
		{
			auto controller = dynamic_cast<WindowsController*>(GetCurrentController());
			if(controller)
				return controller->FindWindowFromHandle(hwnd);
			return nullptr;
		}

		extern IWindowForm* GetWindowForm(INativeWindow* window)
		{
			return static_cast<WindowForm*>(window);
		}

		extern void UninitizlizeWindowNativeController(INativeController* controller)
		{
			delete controller;
		}

	}
}