#pragma once
#include <map>
namespace vm
{
	extern std::map<std::string, int> var_type_table;

	int find_type(const std::string &var_name);
}