#include "node.hpp"
#include "info.hpp"
std::string hcc::type_convert(type::Type* s, type::Type* dest, Node* n)
{
	std::string name = get_tmp_var_name();
	std::string ins;
	ins += dest->to_string() + " " + name + "=" + "(" + dest->to_string() + ")" + n->to_string();
	instructions.push_back(ins);
	return name;
}