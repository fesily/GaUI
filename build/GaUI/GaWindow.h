#pragma once
namespace Window
{
	namespace Detailed
	{
		template<typename Form = CWindow>
		class GaWindowContainer
		{
			GaWindowContainer(){}
			virtual ~GaWindowContainer() {}
		public:
			Form m_formWnd;//包装WTL的windows对象
		};
	}

	template<typename Form = CWindow>
	class GaWindow
	{
		typedef Detailed::GaWindowContainer<Form> Container;
	public:
		GaWindow() {};
		virtual ~GaWindow() {};

	private:
		Container* m_lpContainer{ nullptr };
	};
}

