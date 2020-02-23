#include "../include/word_table.hpp"
#include "../include/translator.hpp";
namespace vm
{
	std::deque<std::map<std::string, VarInfo>> var_symbol_table;
	std::map<std::string, int> function_address_table;
	int find_func_address(const std::string & name)
	{
		auto result = function_address_table.find(name);
		if (result == function_address_table.end())
			throw Error("intern-error E6 function " + name + " no found");
		return result->second;
	}
	int find_type(const std::string & var_name)
	{
		for (int i = var_symbol_table.size() - 1; i >= 0; i--)
		{
			auto result = var_symbol_table[i].find(var_name);
			if (result != var_symbol_table[i].end())
				return result->second.type;
		}
		return -1;
	}

	index_type find_pos(const std::string & var_name)
	{
		for (int i = var_symbol_table.size() - 1; i >= 0; i--)
		{
			auto result = var_symbol_table[i].find(var_name);
			if (result != var_symbol_table[i].end())
				return result->second.pos;
		}
		return -1;
	}

	void push_new_symbol(std::string name, int type, int pos)
	{
		var_symbol_table.back().insert({ name,VarInfo(type, pos) });
	}

	void push_new_func_address(const std::string & n, int pos)
	{
		auto result = function_address_table.find(n);
		if (result != function_address_table.end())
			throw Error("intern-error E7 function " + n + " redefined");
		function_address_table.insert({ n,pos });
	}

}