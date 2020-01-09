#include "..\include\literal.hpp"
namespace hcc
{
	hcc::LiteralValue::LiteralValue(std::string v, int s) :Node(NodeType::LITERAL), value(v), state(s){}
	std::string LiteralValue::to_string()
	{
		std::string suffix[] = { "i32","u32","i64","u64","u8","i8","float","double","ldouble" };
		if (state >= 8 || state < 0) {
			throw Error("internal error: in <literal.cpp: (line)" + std::to_string(__LINE__) + "> invalid integer suffix");
		}
		return "(" + suffix[state] + ":" + value+")";
	}
}
