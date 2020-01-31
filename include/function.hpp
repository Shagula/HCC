#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "type.hpp"
#include "node.hpp"
namespace hcc {
	// the various info of a function
	extern bool function_block;
	class FunctionInfo {
	public:
		FunctionInfo(const std::string &str, type::Type* ty) :func_name(str), return_type(ty){}
		std::string get_func_name() { return func_name; }
		type::Type* get_type() { return return_type; }
		std::vector<std::pair<std::string, type::Type*>> argument;
	private:
		std::string func_name;
		type::Type *return_type;
	};
	class FunctionDef:public Node {
	public:
		FunctionDef(FunctionInfo* f) :Node(NodeType::FUNC_DEF),func_info(f) {}
		void emit_code();
	private:
		FunctionInfo* func_info;
	};
	class FunctionCall :public Node {
	public:
		FunctionCall(FunctionInfo *_func, const std::vector<Node*> &_exprs);
		void emit_code()override;
		std::string to_string()override;
	private:
		std::vector<Node*> exprs;
		FunctionInfo *func;
	};
	extern std::map<std::string, FunctionInfo*> function_map;
	namespace Parser
	{
		//build functions or global variable.
		/*
		
		*/
		void function_or_glo_var();
		std::vector<std::pair<std::string, type::Type*>> parse_argument();
	}
}