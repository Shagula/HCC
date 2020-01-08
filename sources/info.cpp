#include "../include/info.hpp"
namespace hcc {
	std::vector<std::string> instructions;
	std::string get_tmp_var_name(bool c)
	{
		static int index = 0;
		if (c)
		{
			index = 0;
			return "";
		}
		return "%" + std::to_string(index++);
	}
}