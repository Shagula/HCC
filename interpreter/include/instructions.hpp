#pragma once
#include <vector>
#include <functional>
#include <iostream>
namespace vm {
	using instruction_type = std::function<void(char*)>;
	extern std::vector<std::pair<instruction_type,char*>> glo_instructions;
	extern int pc;

	// the char-array is to store the tmp result such as 1+1
	extern char intern_result_buf[20];
	
	instruction_type gen_bin_op(char _ty,char op);
}