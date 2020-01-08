#include "../include/type.hpp"
#include "../include/lexer.hpp"
namespace hcc
{
	namespace type {
		std::map<std::string, Type*> basic_type_map{
			{"int",new BasicType("int",sizeof(int))},{"unsigned int",new BasicType("unsigned int",sizeof(int))},
			{"char",new BasicType("int",sizeof(char))},{"unsigned char",new BasicType("unsigned char",sizeof(char))},
			{"long",new BasicType("long",sizeof(long long))},{"unsigned long",new BasicType("unsigned long",sizeof(long long))},
			{"float",new BasicType("float",sizeof(float))},{"double",new BasicType("double",sizeof(double))},{"long double",new BasicType("long double",sizeof(long double))},
			{"bool",new BasicType("bool",sizeof(bool))},
			{"void",new BasicType("void",0)}
		};
	}
	type::Type* process_basic_type(Token* tok)
	{
		switch (tok->get_tag())
		{
		case hcc::INTEGER_DECL:
			token_stream.next();
			return type::basic_type_map["int"];
		case hcc::FLOAT_DECL:
			token_stream.next();
			return type::basic_type_map["float"];
		case hcc::DOUBLE_DECL:
			token_stream.next();
			return type::basic_type_map["double"];
		case hcc::BOOL_DECL:
			token_stream.next();
			return type::basic_type_map["bool"];
		case hcc::CHAR_DECL:
			token_stream.next();
			return type::basic_type_map["char"];
		case hcc::LONG_DECL:
			token_stream.next();
			return type::basic_type_map["long"];
		default:
			throw Error("unkown type");
		}
	}
	type::Type* process_type() {
		return process_basic_type(token_stream.this_token());
	}
}