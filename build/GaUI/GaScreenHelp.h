#pragma once
#include <list>
namespace GaUI
{
	class GaScreenHelp final
	{
	public:
		class TaskInfo
		{
		public:
			enum eTaskPos
			{
				Left,
				Top,
				Right,
				Bottom,
			};
		public:
			void Update(const MONITORINFOEX& monitorInfo);
		protected:
			static eTaskPos UpdateTaskPos(const CRect& rcTask, const CRect& rcWorkeArea);
		public:
			CRect m_rcTask;
			eTaskPos m_eTaskPos;
		};
		class MonitorInfo
		{
		public:
			MonitorInfo();
			void Update(HMONITOR hMonitor);
			bool IsPrimary();
		public:
			MONITORINFOEX m_monitorInfo;
			TaskInfo m_taskInfo;
		};
		class DispalyMonitor;
	protected:
		//删除单例
		class SafeDelete;
		friend SafeDelete;
		//显示器信息相关
	public:
		GaScreenHelp();
		~GaScreenHelp();

		void Update();
		MonitorInfo* Find(HMONITOR hMonitor);
		MonitorInfo* MainMonitor();
	public:
		static GaScreenHelp* Get() 
		{
			if (instance == nullptr)
				instance = new GaScreenHelp;
			return instance;
		}
	protected:
		DispalyMonitor* m_pDisplayMonitor;//显示器列表
	private:
		static GaScreenHelp* instance;
	};
}
