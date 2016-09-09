#pragma once
#include "GaBaseClass.h"
#include "EventBase.h"
namespace GaUI
{
	namespace Native
	{
#if 0
		class INativeWindow
			:public Interface
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
		class INativeWindow
			:public ATL::CWindow, public Interface
		{
		public:
			virtual CSize GetClientSize();
		};
#endif
		class INativeWindowListener
			:public Interface
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
			:public Interface
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
	}
}