#include "stdafx.h"
#include "GaControl.h"
#include "Event.h"
#include "CompositionBase.h"
namespace GaUI
{

	GaControl::GaControl(IControlStyle* pStyle)
		:m_pComposition(pStyle->GetComposition())
		,m_pEventManager(nullptr)
	{

	}

	GaControl::~GaControl()
	{
		delete m_pComposition;
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

}