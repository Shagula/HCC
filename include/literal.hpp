#pragma once
#include "node.hpp"
#include "type.hpp"
namespace hcc
{
	class LiteralValue final :public Node
	{
	public:
		/*
		s-> 0 : int
		s-> 1: unsigned int
		s-> 2: long
		s-> 3: unsigned long
		s-> 4: unsigned char
		s-> 5: char
		s -> 6: float
		s -> 7: double
		s -> 8: long double
		*/
		LiteralValue(std::string value,int s);
		std::string to_string()override;
	private:
		std::string value;
		int state = 1;
	};

}