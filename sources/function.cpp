#include "../include/function.hpp"
#include "../include/lexer.hpp"
#include "../include/symbols.hpp"
namespace hcc
{
	extern std::vector<std::string> instructions;
	bool function_block = false;
	std::map<std::string, FunctionInfo*> function_map;
	extern std::vector<Node*> abstract_instruction_table;
	namespace Parser
	{
		void build_block();
		void function_or_glo_var()
		{
			type::Type* ty = process_type();
			std::string name = Id::get_value(token_stream.this_token());
			token_stream.match(ID);
			if (token_stream.this_tag() == LPAREN) {
				FunctionInfo *func = new FunctionInfo(name,ty);
				func->argument = parse_argument();
				function_map.insert({ name,func });
				abstract_instruction_table.push_back(new FunctionDef(func));
				function_block = true;
				build_block();
				function_block = false;
				_symbol_table.push(new Symbol(name, ty, SymbolType::FUNCTION_ID));
			}
		}
		std::vector<std::pair<std::string, type::Type*>> parse_argument()
		{
			std::vector<std::pair<std::string, type::Type*>> ret;
			token_stream.match(LPAREN);
			while (token_stream.this_tag() != RPAREN) {
				type::Type *ty = process_type();
				std::string name = Id::get_value(token_stream.this_token());
				token_stream.match(ID);
				ret.push_back({ name,ty });
				if(token_stream.this_tag() != RPAREN){
					token_stream.match(COMMA);
				}
			}
			token_stream.match(RPAREN);
			return ret;
		}
	}
	void FunctionDef::emit_code()
	{
		std::string tmp;
		tmp += "(function " + func_info->get_func_name() + " " + func_info->get_type()->to_string() + " ";
		for (auto a : func_info->argument) {
			// Yip 
			tmp += a.first + "->" + a.second->to_string() + ",)"[a==func_info->argument.back()];
		}
	}
	FunctionCall::FunctionCall(FunctionInfo * _func, const std::vector<Node*> &_exprs):Node(NodeType::FUNC_CALL),func(_func),exprs(_exprs)
	{
		set_type(func->get_type());
		if (exprs.size() != func->argument.size())
			throw Error("argument size error");
		for (int i = 0; i < exprs.size(); i++) {
			if (!exprs[i]->get_type()->convertible(func->argument[i].second))
				throw Error("argument type not matched");
		}
	}
	void FunctionCall::emit_code()
	{
		for (auto a : exprs)
		{
			a->emit_code();
			instructions.push_back("(push " + a->to_string() + ")");
		}
		instructions.push_back("(call " + func->get_func_name()+")");
	}
}


