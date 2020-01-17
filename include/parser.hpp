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
		void emit_code();
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
	namespace Parser {
		Node* var_decl();
		Node* statement();
	}
	namespace analyse_expr
	{
		Node* create_expr();
	}
	class Jmp :public Node {
	public:
		Jmp(std::string _tag_name) :Node(NodeType::JMP), tag_name(_tag_name) {}
		void emit_code()override;
	private:
		std::string tag_name;
	};
}