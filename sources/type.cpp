#include "../include/type.hpp"
namespace hcc
{
	namespace type {
		ty_index type_index=1;
		std::map<ty_index, ty_index> convert_map;
		std::map<ty_index, BasicType*> type_map;
		void build_type_conver_info(ty_index t1, const std::vector<ty_index>& types)
		{
		}
	}
}