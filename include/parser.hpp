#pragma once
#include "node.hpp"
#include <iostream>
#include <vector>
namespace hcc {
	// in a var_decl , you may def many var in one sentance for instance
// int a=3,b=4,c=3;
	class VarDeclUnit{
	public:
		VarDeclUnit(type::Type* t);
		type::Type* get_type() { return type; }
		std::string get_name_part() { return name; }
		Node* expr;
	private:
		std::string name;
		type::Type* type;

	};
	class LocalVarDecl :public Node {
	public:
		LocalVarDecl(std::vector<VarDeclUnit*>& vec, type::Type* t);
		void emit_code()override;
	private:
		std::vector<VarDeclUnit*> units;
	};
	namespace parse_statement {
		Node* var_decl();
		Node* statement();
	}
}