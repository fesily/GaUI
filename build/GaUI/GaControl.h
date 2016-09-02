#pragma once
#include <set>
namespace GaUI
{
	namespace Layout
	{
		class Composition;
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
			//依赖注入类,负责创建合理的子类化布局器
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
			ControlList m_listControl;//内部控件列表
			Layout::Composition*  m_pComposition;//布局器

			Event::GeneralEventManager* m_pEventManager;//指定事件管理器
		};

		class Gabutton
			:public GaControl
		{
		public:
			enum eState
			{
				Noraml,
				Active,
				Pressed,
			};
		public:
			class IButtonStyle
				:public GaControl::IControlStyle
			{
				virtual void Transf(eState newState) = 0;
			};
		public:
			Gabutton(IButtonStyle* pStyle);
			~Gabutton();

		public:
			eState m_eState;	//按钮状态
			IButtonStyle* m_pButtonStyle;//按钮的创建样式
		};


		class GaControlHost
		{

		};
		class GaWindowControl
			:public GaControlHost
		{

		};
	}
}