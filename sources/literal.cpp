#include "..\include\literal.hpp"
namespace hcc
{
	const std::string type_suffix[] = { "i32","u32","i64","u64","u8","i8","float","double","ldouble" };

	hcc::LiteralValue::LiteralValue(std::string v, int s) :Node(NodeType::LITERAL), value(v), state(s)
	{
		if (state >= 8 || state < 0) {
			throw Error("internal error: in <literal.cpp: (line)" + std::to_string(__LINE__) + "> invalid integer suffix");
		}
		set_type(type::basic_type_map[type_suffix[s]]);
	}
	std::string LiteralValue::to_string()
	{
		return  type_suffix[state] + ":" + value;
	}
}
