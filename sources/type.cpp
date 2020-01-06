#include "../include/type.hpp"
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
}