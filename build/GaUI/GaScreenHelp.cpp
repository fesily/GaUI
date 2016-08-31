#include "stdafx.h"
#include "GaScreenHelp.h"
#include "memory.h"
#include <map>
namespace GaUI
{
	GaScreenHelp* GaScreenHelp::instance = nullptr;

	//删除单例
	class GaScreenHelp::SafeDelete
	{
		~SafeDelete()
		{
			if(GaScreenHelp::instance != nullptr)
				delete GaScreenHelp::instance;
		}
	};

	void GaScreenHelp::TaskInfo::Update(const MONITORINFOEX& monitorInfo)
	{
		m_rcTask.SubtractRect(&monitorInfo.rcMonitor, &monitorInfo.rcWork);
		m_eTaskPos = UpdateTaskPos(m_rcTask, static_cast<const CRect&>(monitorInfo.rcWork));
	}

	GaScreenHelp::TaskInfo::eTaskPos GaScreenHelp::TaskInfo::UpdateTaskPos(const CRect& rcTask, const CRect& rcWorkeArea)
	{
		if(rcTask.TopLeft() == rcWorkeArea.TopLeft())
		{
			if(rcTask.right >= rcWorkeArea.right)
				return Top;
			else
				return Left;
		}
		else
		{
			if(rcTask.left > rcWorkeArea.left)
				return Right;
			else
				return Bottom;
		}
	}

	GaScreenHelp::MonitorInfo::MonitorInfo()
	{
		m_monitorInfo = {};
		m_monitorInfo.cbSize = sizeof(MONITORINFOEX);
	}

	void GaScreenHelp::MonitorInfo::Update(HMONITOR hMonitor)
	{
		::GetMonitorInfo(hMonitor, &m_monitorInfo);
		m_taskInfo.Update(m_monitorInfo);
	}

	bool GaScreenHelp::MonitorInfo::IsPrimary()
	{
		return m_monitorInfo.dwFlags == MONITORINFOF_PRIMARY;
	}

	//显示器信息相关
	class GaScreenHelp::DispalyMonitor
	{
	public:
		void Update()
		{
			m_listMonitorInfo.clear();
			::EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)this);
			ATLASSERT(m_listMonitorInfo.size() == ::GetSystemMetrics(SM_CMONITORS));
		}
	private:
		static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor,
											 HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
		{
			auto pDispaly = reinterpret_cast<DispalyMonitor*>(dwData);

			MonitorInfo* pInfo = new MonitorInfo;
			pInfo->Update(hMonitor);

			if(pInfo->IsPrimary())
				pDispaly->m_pMainMonitorInfo = pInfo;

			pDispaly->m_listMonitorInfo[hMonitor].reset(pInfo);
			return TRUE;
		}
	public:
		std::map<HMONITOR,std::unique_ptr<MonitorInfo>> m_listMonitorInfo;
		MonitorInfo* m_pMainMonitorInfo;//主显示器;
	};

	GaScreenHelp::GaScreenHelp()
		:m_pDisplayMonitor(new DispalyMonitor)
	{
		Update();
	}
	GaScreenHelp::~GaScreenHelp()
	{
		delete m_pDisplayMonitor;
		m_pDisplayMonitor = nullptr;
		instance = nullptr;
	}

	void GaScreenHelp::Update()
	{
		m_pDisplayMonitor->Update();
	}

	GaScreenHelp::MonitorInfo* GaScreenHelp::Find(HMONITOR hMonitor)
	{
		auto iter = m_pDisplayMonitor->m_listMonitorInfo.find(hMonitor);
		if(iter != m_pDisplayMonitor->m_listMonitorInfo.end())
			return iter->second.get();
		ATLASSERT(FALSE);
		return nullptr;
	}

	GaScreenHelp::MonitorInfo* GaScreenHelp::MainMonitor()
	{
		return m_pDisplayMonitor->m_pMainMonitorInfo;
	}

}

