#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "type.hpp"
namespace hcc {
	// the various info of a function
	class Function {
	public:
		Function(const std::string &str, type::Type* ty) :func_name(str), return_type(ty){}
		std::string get_func_name() { return func_name; }
		type::Type* get_type() { return return_type; }
		std::vector<std::pair<std::string, type::Type*>> argument;
	private:
		std::string func_name;
		type::Type *return_type;
	};

	extern std::map<std::string, Function*> function_map;
	namespace Parser
	{
		//build functions or global variable.
		/*
		
		*/
		void function_or_glo_var();
		std::vector<std::pair<std::string, type::Type*>> parse_argument();
	}
}