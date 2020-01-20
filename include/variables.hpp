#pragma once
#include <iostream>
#include "node.hpp"
namespace hcc {
	class Symbol;
	class Variable :public Node {
	public:
		Variable(const std::string& n,type::Type * t);
		std::string to_string() {
			return "%" + name;
		}
	private:
		std::string name;
	};
	Node* parse_id();
	Node* parse_var(Symbol* );
	Node* parse_function_call(Symbol* );
}