#include "../include/word_table.hpp"
namespace vm
{
	std::map<std::string, VarInfo> var_type_table;

	int find_type(const std::string & var_name)
	{
		auto result = var_type_table.find(var_name);
		if (result == var_type_table.end())
			return -1;
		return result->second.type;
	}

	index_type find_pos(const std::string & var_name)
	{
		auto result = var_type_table.find(var_name);
		if (result == var_type_table.end())
			return -1;
		return result->second.pos;
	}

}