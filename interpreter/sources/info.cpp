#include "../include/info.hpp"
namespace vm
{
	std::map<std::string, int> var_type_table;
	int vm::find_type(const std::string & var_name)
	{
		auto result = var_type_table.find(var_name);
		if (result == var_type_table.end())
			return -1;
		return result->second;
	}

}