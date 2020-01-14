#pragma once
#include <vector>
#include <string>
namespace hcc {
	class Node;
	extern std::vector<std::string> instructions;
	extern std::vector<Node*> abstruct_instruction_table;
	// if c is true the index will be reset
	std::string get_tmp_var_name(bool c);
}