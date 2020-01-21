#include "../include/variables.hpp"
#include "../include/symbols.hpp"
#include "../include/function.hpp"
namespace hcc
{
	namespace analyse_expr {
		Node* create_expr();
	}
	Variable::Variable(const std::string& n,type::Type* t):Node(NodeType::VAR),name(n)
	{
		set_type(t);
	}
	Node* parse_id()
	{
		std::string id_content = Id::get_value(token_stream.this_token());
		auto result = _symbol_table.find(id_content);
		if (result == nullptr)
			throw Error("id " + id_content + " undefined");
		token_stream.match(ID);
		switch (result->symbol_type)
		{
		case SymbolType::LOCAL_VAR:
			return parse_var(result);
		case SymbolType::FUNCTION_ID:
			return parse_function_call(result);
		default:
			break;
		}
	}
	Node* parse_var(Symbol* symbol) {
		switch (symbol->symbol_type)
		{
		case SymbolType::LOCAL_VAR:
			return new Variable(symbol->get_name(),symbol->get_type());
		default:
			break;
		}
	}
	Node* parse_function_call(Symbol* symbol) {
		auto func_info = function_map[symbol->get_name()];
		token_stream.match(LPAREN);
		std::vector<Node*> exprs;
		exprs.push_back(analyse_expr::create_expr());
		while (token_stream.this_tag() != RPAREN) {
			token_stream.match(COMMA);
			exprs.push_back(analyse_expr::create_expr());
		}
		token_stream.match(RPAREN);
		return new FunctionCall(func_info, exprs);
	}
}

