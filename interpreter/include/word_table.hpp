#pragma once
#include <map>
#include <deque>
namespace vm
{
	using index_type = int;
	struct VarInfo {
		VarInfo(int t, int p) :type(t), pos(p) {}
		int type;
		int pos;

	};
	extern std::deque<std::map<std::string, VarInfo>> var_symbol_table;

	extern std::map<std::string, int> function_address_table;



	int find_func_address(const std::string &name);

	int find_type(const std::string &var_name);

	index_type find_pos(const std::string &var_name);

	void push_new_symbol(std::string name,int type, int pos);

	void push_new_func_address(const std::string &n, int pos);
}