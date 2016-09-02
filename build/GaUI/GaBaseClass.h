#pragma once
namespace GaUI
{
	class Noncopyable
	{
		Noncopyable(const Noncopyable&) {};
		Noncopyable& operator=(const Noncopyable&) {};
	protected:
		Noncopyable() {};
	};

	/// Prevent a class to be movable
	class Nonmovable
	{
		Nonmovable(Nonmovable&&) {};
		Nonmovable& operator=(Nonmovable&&) {};
	protected:
		Nonmovable() {};
	};
	class Interface
		:public Noncopyable
	{
	public:
		virtual ~Interface() {};
	};
}