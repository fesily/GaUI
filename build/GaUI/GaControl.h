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
			//����ע����,���𴴽���������໯������
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
			ControlList m_listControl;//�ڲ��ؼ��б�
			Layout::Composition*  m_pComposition;//������

			Event::GeneralEventManager* m_pEventManager;//ָ���¼�������
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
			eState m_eState;	//��ť״̬
			IButtonStyle* m_pButtonStyle;//��ť�Ĵ�����ʽ
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