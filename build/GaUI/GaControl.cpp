#include "stdafx.h"
#include "GaControl.h"
#include "Event.h"
#include "CompositionBase.h"
namespace GaUI
{
	namespace Control
	{
		GaControl::GaControl(IControlStyle* pStyle)
			:m_pContrlStyle(pStyle)
			,m_pComposition(pStyle->GetComposition())
			, m_pEventManager(nullptr)
		{

		}

		GaControl::~GaControl()
		{
			delete m_pComposition;
			m_pComposition = nullptr;
		}

		Event::GeneralEventManager* GaControl::GetEventManager()
		{
			if(!m_pEventManager)
			{
				m_pEventManager = new Event::GeneralEventManager;
			}
			return m_pEventManager;
		}

		bool GaControl::AddChild(GaControl* pControl)
		{
			auto iter = m_listControl.lower_bound(pControl);
			if(iter != m_listControl.end())
			{
				m_listControl.emplace(pControl);
				return true;
			}
			return false;
		}

		bool GaControl::RemoveChild(GaControl* pControl)
		{
			auto iter = m_listControl.find(pControl);
			if(iter != m_listControl.end())
			{
				m_listControl.erase(iter);
				return true;
			}
			return false;
		}

		std::size_t GaControl::GetChildCount() const
		{
			return m_listControl.size();
		}
		//////////////////////////////////////////////////////////////////////////

		Gabutton::Gabutton(IButtonStyle* pStyle)
			: GaControl(pStyle)
			, m_isPressing(false)
			, m_isHoving(false)
			, m_eStatus(Noraml)

		{
			m_pButtonStyle = pStyle;
			pStyle->Transf(m_eStatus);
			//°ó¶¨ÏûÏ¢
			GetEventManager()->mouse_enter.attach(this, &Gabutton::OnMouseEnter);
			GetEventManager()->mouse_leave.attach(this, &Gabutton::OnMouseLeave);
			GetEventManager()->mouse_down.attach(this, &Gabutton::OnLButtonDown);
			GetEventManager()->mouse_up.attach(this, &Gabutton::OnLButtonUp);
		}

		Gabutton::~Gabutton()
		{

		}

		void Gabutton::UpdateControlState()
		{
			eStatus newState = Noraml;
			if(m_isPressing)
			{
				if(m_isHoving)
					newState = Pressed;
				else
					newState = Active;
			}
			else
			{
				if(m_isHoving)
					newState = Active;
				else
					newState = Noraml;
			}
			if(m_eStatus != newState)
			{
				m_eStatus = newState;
				m_pButtonStyle->Transf(m_eStatus);
			}
		}

		void Gabutton::OnMouseEnter()
		{
			m_isHoving = true;
			UpdateControlState();
		}

		void Gabutton::OnMouseLeave()
		{
			m_isHoving = false;
			UpdateControlState();
		}

		void Gabutton::OnLButtonDown()
		{
			m_isPressing = true;
			UpdateControlState();
		}

		void Gabutton::OnLButtonUp()
		{
			m_isPressing = false;
			UpdateControlState();
		}
		//////////////////////////////////////////////////////////////////////////
		GaControlHost::GaControlHost(GaControl::IControlStyle* pStyle)
			:GaControl(pStyle)
		{

		}

		GaControlHost::~GaControlHost()
		{

		}

	}
}