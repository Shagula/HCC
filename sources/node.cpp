#include "../include/node.hpp"
#include "../include/info.hpp"
std::string hcc::type_convert(type::Type* s, type::Type* dest, Node* n)
{
	std::string name = dest->to_string()+" "+ get_tmp_var_name(false);
	std::string ins;
	ins += "(" + name + " " + n->to_string()+")";
	instructions.push_back(ins);
	return name;
}