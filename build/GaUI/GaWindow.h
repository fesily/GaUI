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
			Form m_formWnd;//��װWTL��windows����
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

