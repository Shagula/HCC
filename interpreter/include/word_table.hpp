#pragma once
#include <map>
namespace vm
{
	using index_type = int;
	struct VarInfo {
		VarInfo(int t, int p) :type(t), pos(p) {}
		int type;
		int pos;

	};

	extern std::map<std::string, VarInfo> var_type_table;

	int find_type(const std::string &var_name);

	index_type find_pos(const std::string &var_name);
}