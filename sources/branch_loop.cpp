#include "..\include\branch_loop.hpp"
namespace hcc {
	void IfTrueToAOrB::emit_code()
	{
		expr->emit_code();
		auto ret = expr->to_string();
		
	}
}

