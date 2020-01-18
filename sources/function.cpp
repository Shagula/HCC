#include "../include/function.hpp"
#include "../include/lexer.hpp"
namespace hcc
{
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
}


