#include "../include/type.hpp"
#include "../include/lexer.hpp"
namespace hcc
{
	namespace type {
		std::map<std::string, Type*> basic_type_map{
			{"i32",new BasicType("int",sizeof(int))},{"u32",new BasicType("unsigned int",sizeof(int))},
			{"i8",new BasicType("unsigned char",sizeof(char))},{"u8",new BasicType("unsigned char",sizeof(char))},
			{"i64",new BasicType("long",sizeof(long long))},{"u64",new BasicType("unsigned long",sizeof(long long))},
			{"float",new BasicType("float",sizeof(float))},{"double",new BasicType("double",sizeof(double))},{"long double",new BasicType("ldouble",sizeof(long double))},
			{"void",new BasicType("void",0)}
		};
		type::Type* void_type=basic_type_map["void"];
	}

	type::Type* process_basic_type(Token* tok)
	{
		switch (tok->get_tag())
		{
		case hcc::INTEGER_DECL:
			token_stream.next();
			return type::basic_type_map["i32"];
		case hcc::FLOAT_DECL:
			token_stream.next();
			return type::basic_type_map["float"];
		case hcc::DOUBLE_DECL:
			token_stream.next();
			return type::basic_type_map["double"];
		case hcc::CHAR_DECL:
			token_stream.next();
			return type::basic_type_map["i8"];
		case hcc::LONG_DECL:
			token_stream.next();
			return type::basic_type_map["i64"];
		default:
			throw Error("unkown type");
		}
	}
	type::Type* process_type() {
		return process_basic_type(token_stream.this_token());
	}
}