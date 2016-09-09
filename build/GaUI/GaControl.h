#pragma once
#include <set>
#include "NativeWindowInterface.h"
namespace GaUI
{
	namespace Layout
	{
		class Composition;
		class GaGraphicesHost;
	}
	namespace Event
	{
		struct general_events;
		typedef general_events GeneralEventManager;
	}
	namespace Control
	{

		class GaControl
		{
			typedef std::set<GaControl*> ControlList;
		public:
			//依赖注入类,负责创建合理的子类化布局器,并且对其样式进行控制
			class IControlStyle
			{
			public:
				virtual ~IControlStyle() {}
				virtual Layout::Composition* GetComposition() = 0;
				//virtual void SetFont(IFont* pFont) = 0;
			};
		public:
			virtual void OnChildInsert(GaControl* pControl) {}
			virtual void OnChildRemove(GaControl* pControl) {}
		public:
			bool AddChild(GaControl* pControl);
			//bool InsertChild(GaControl* pControl, int nIndex);
			bool RemoveChild(GaControl* pControl);
			std::size_t GetChildCount()const;
		public:
			GaControl(IControlStyle* pStyle);
			virtual ~GaControl();

			Event::GeneralEventManager* GetEventManager();
		protected:
			IControlStyle* m_pContrlStyle;
			GaControl* m_pParent;
			ControlList m_listControl;//内部控件列表
			Layout::Composition*  m_pComposition;//布局器

			Event::GeneralEventManager* m_pEventManager;//指定事件管理器
		protected:
			//状态信息
			bool m_isVisible;
			bool m_isEnabled;
			std::wstring m_title;
		};

		class Gabutton
			:public GaControl
		{
		public:
			enum eStatus
			{
				Noraml,
				Active,
				Pressed,
			};
		public:
			class IButtonStyle
				:public GaControl::IControlStyle
			{
			public:
				virtual void Transf(eStatus newStatus) = 0;
			};
		public:
			Gabutton(IButtonStyle* pStyle);
			~Gabutton();

			void UpdateControlState();
		protected:
			void OnMouseEnter();
			void OnMouseLeave();
			void OnLButtonDown();
			void OnLButtonUp();
		public:
			bool m_isPressing;	//按住状态
			bool m_isHoving;	//悬浮状态
			eStatus m_eStatus;	//按钮状态
			IButtonStyle* m_pButtonStyle;//按钮的创建样式
		};


		class GaControlHost
			:public GaControl, public Native::INativeWindowListener
		{
			
		public:
			GaControlHost(GaControl::IControlStyle* pStyle);
			~GaControlHost();

// 		protected:
// 			virtual void OnNativeWindowChanged();
// 			virtual void OnVisualStatusChanged();
// 		protected:
// 			void MouseMoving(const arg_mouse& info)override;
// 			void MouseLeaved()override;
// 			void Moved()override;
// 			void Enabled()override;
// 			void Disabled()override;
// 			void GotFocus()override;
// 			void LostFocus()override;
// 			void Actived()override;
// 			void Deactived()override;
// 			void Opened()override;
// 			void Closing()override;
// 			void Closed()override;
// 			void Destroying()override;
		protected:
			Layout::GaGraphicesHost* m_pGraphicesHost;
		};

		class GaWindowControl
			:public GaControlHost 
		{
			
		};
	}
}