#pragma once
#include <vector>
#include <string>
namespace hcc {
	extern std::vector<std::string> instructions;
	// if c is true the index will be reset
	std::string get_tmp_var_name(bool c);
}