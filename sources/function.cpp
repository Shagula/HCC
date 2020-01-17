#include "../include/function.hpp"
#include "../include/lexer.hpp"
namespace hcc
{
	std::map<std::string, Function*> function_map;

	namespace Parser
	{
		void function_or_glo_var()
		{
			type::Type* ty = process_type();
			std::string name = Id::get_value(token_stream.this_token());
			token_stream.match(ID);
			if (token_stream.this_tag() == LPAREN) {
				Function *func = new Function(name,ty);
				func->argument = parse_argument();
				function_map.insert({ name,func });
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
}


