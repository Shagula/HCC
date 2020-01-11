#include "../include/variables.hpp"
#include "../include/symbols.hpp"
namespace hcc
{
	Variable::Variable(const std::string& n,type::Type* t):Node(NodeType::VAR),name(n)
	{
		set_type(t);
	}
	Node* parse_id(type::Type* ty)
	{
		std::string id_content = Id::get_value(token_stream.this_token());
		token_stream.match(ID);
		auto result = _symbol_table.find(id_content);
		if (result == nullptr)
			throw Error("id " + id_content + " undefined");
		switch (result->symbol_type)
		{
		case SymbolType::LOCAL_VAR:
			return new Variable(id_content,ty);
		default:
			break;
		}
	}
}

