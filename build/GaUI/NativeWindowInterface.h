#pragma once
#include "GaBaseClass.h"
#include "EventBase.h"
namespace GaUI
{
	namespace Native
	{
#if 0
		class INativeWindow
			:public virtual Interface
		{
		public:
			enum eWindowSizeStatus
			{
				Minimized,
				Restored,
				Maximized,
			};
		public:
			virtual CRect GetBounds() = 0;
			virtual void SetBounds(const CRect& bounds) = 0;

			virtual CSize GetClientSize() = 0;
			virtual void SetClientSize(const CSize& size) = 0;

			virtual CRect GetClientBoundsInScreen() = 0;

			virtual std::wstring GetTitle() = 0;
			virtual void SetTitle(const std::wstring& title) = 0;

			virtual INativeCursor* GetWindowCursor() = 0;
			virtual void SetWindowCursor(INativeCursor* cursor) = 0;

			virtual CPoint GetCarePoint() = 0;
			virtual void SetCarePoint(Point point) = 0;

			virtual INativeWindow* GetParent() = 0;
			virtual void SetParent(INativeWindow* parent) = 0;

			virtual bool GetAlwaysPassFocusToParent() = 0;
			virtual void SetAlwaysPassFocusToParent(bool value) = 0;

			virtual void EnableCustomFrameMode() = 0;
			virtual void DisableCustomFrameMode() = 0;
			virtual bool IsCustomFrameModeEnabled() = 0;

			virtual eWindowSizeStatus GetSizeStatus() = 0;
			virtual void Show() = 0;
			virtual void ShowDeactiveated() = 0;
			virtual void ShowRestored() = 0;
			virtual void ShowMaximized() = 0;
			virtual void ShowMinimized() = 0;
			virtual void Hide() = 0;
			virtual bool IsVisible() = 0;

			virtual void Enable() = 0;
			virtual void Disable() = 0;
			virtual bool IsEnable() = 0;

			virtual void SetFocus() = 0;
			virtual bool IsFocus() = 0;

			virtual void SetActivate() = 0;
			virtual bool IsActivated() = 0;

			virtual void ShowInTaskBar() = 0;
			virtual void HideInTaskBar() = 0;
			virtual bool IsAppearedIntaskBar() = 0;
			
			virtual void EnableActivate() = 0;
			virtual void DisableActivate() = 0;
			virtual bool IsActivateEnabled() = 0;

			

		};
#else
		typedef ATL::CWinTraits<WS_BORDER | WS_CAPTION | WS_SIZEBOX | WS_SYSMENU | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
			WS_EX_APPWINDOW | WS_EX_CONTROLPARENT> NativeWindowTraits;
		class INativeWindow
			:public CWindowImpl<INativeWindow,ATL::CWindow, NativeWindowTraits>, public virtual Interface
		{
		public:
			DECLARE_WND_CLASS(NULL)
		public:
			virtual	CSize	GetClientSize();
			virtual void RedrawWindow() = 0;
		};
#endif
		class INativeWindowListener
			:public virtual Interface
		{
			enum eHitTestResult
			{
				Border_NoSizing,
				Border_Left,
				Border_Right,
				Border_Top,
				Border_Bottom,
				Border_LeftTop,
				Border_RightTop,
				Border_LeftBottom,
				Border_RightBottom,
				Title,
				Button_Minimum,
				Button_Maximum,
				Button_close,
				Client,
				Icon,
				NoDecision,
			};

			virtual eHitTestResult HitTest(const CPoint& cpt);
			virtual void Moving(const CRect& bounds, bool fixSizeOnly1) {}
			virtual void Moved() {}
			virtual void Enabled() {}
			virtual void Disabled() {}
			virtual void GotFocus() {}
			virtual void LostFocus() {}

			virtual void Actived() {}
			virtual void Deactived() {}
			virtual void Opened() {}
			virtual void Closing() {}
			virtual void Closed() {}
			virtual void Paint() {}
			virtual void Destroying() {}
			virtual void Destroyed() {}

			virtual void MouseButtonDown(const arg_mouse& info) {}
			virtual void MouseButtonUp(const arg_mouse& info) {}
			virtual void MouseButtonDbClick(const arg_mouse& info) {}

			virtual void HorizontalWheel(const arg_wheel& info) {}
			virtual void VerticalWheel(const arg_wheel& info) {}

			virtual void MouseMoving(const arg_mouse& info) {}

			virtual void MouseEntered() {}
			virtual void MouseLeaved() {}

			virtual void KeyDown() {}
			virtual void KeyUp() {}

			virtual void SysKeyDown() {}
			virtual void SysKeyUp() {}

			virtual void Char() {}
		};

		class INativeControllerListener
			:public virtual Interface
		{
		public:
			virtual void LeftButtonDown(const CPoint& position) {}
			virtual void LeftButtonUp(const CPoint& position) {}

			virtual void RightButtonDown(const CPoint& position) {}
			virtual void RightButtonUp(const CPoint& position) {}

			virtual void MouseMoving(const CPoint& position) {}

			virtual void GlobalTimer() {}
			virtual void ClipboardUpdated() {}

			virtual void NativeWindowCreated(INativeWindow* window) {}
			virtual void NativeWindowDestroying(INativeWindow* window) {}
		};

		//提供native窗口生存期以及查询相关操作
		class INativeWindowServer :public virtual Interface
		{
		public:
			virtual	INativeWindow*	CreateNatvieWindow() = 0;
			virtual	void			DestroyNatvieWindow(INativeWindow* window) = 0;
			virtual	INativeWindow*	GetMainNatvieWindow() = 0;
			virtual	INativeWindow*	GetNatvieWindow(const CPoint& location) = 0;
			virtual	void			Run(INativeWindow* windows) = 0;
		};

		class INativeController :public virtual Interface
		{
		public:
			virtual INativeWindowServer* WindowServer() = 0;
			virtual bool HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& result) = 0;
		};

		extern void SetCurrentController(INativeController* controller);
		extern INativeController* GetCurrentController();
	}
}