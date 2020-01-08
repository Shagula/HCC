#pragma once
#include "node.hpp"
#include "type.hpp"
namespace hcc
{
	class IntV final :public Node
	{
	public:
		IntV(int v,int s);
		IntV();
		std::string to_string()override;
	private:
		int value;
	};
	class RealV final :public Node
	{
	public:
		RealV(double v);
		RealV();
		std::string to_string()override;
	private:
		double value;
	};
	class BoolV final :public Node
	{
	public:
		BoolV(bool v);
		BoolV();
		std::string to_string()override
		{
			if (value)
				return "true";
			return "false";
		}
	private:
		bool value;
	};
	class CharV final :public Node
	{
	public:
		CharV(char v);
		CharV();
		std::string to_string()override
		{
			return "c\'" + std::string(1, value) + "\'";
		}
	private:
		char value;
	};
}