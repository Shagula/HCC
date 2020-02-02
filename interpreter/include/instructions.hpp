#pragma once
#include <vector>
#include <functional>
#include <iostream>
namespace vm {
	using instruction_type = std::function<void(char*)>;
	extern std::vector<std::pair<instruction_type,char*>> glo_instructions;
	extern int pc;
	void run();
	instruction_type gen_bin_op(char _ty,int op);
}