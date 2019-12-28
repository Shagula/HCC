#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>
namespace hcc {
	namespace type {
		using ty_index = int;
		enum TypeTag {
			INT=1,LONG=2,UINT,ULONG,USHORT,SHORT,CHAR,BOOL,FLOAT,DOUBLE,LDOUBLE
		};
		enum TypeProperty {
			CONST,POINTER,COMMON
		};
		class Type {
		public:
			Type(int tys = 0) :ty_size(tys) {}
			virtual bool constant()const { return false; }
			int type_size() { return ty_size; }
			virtual std::string to_string()const { return "unknown-type"; }
			virtual ~Type(){}
		private:
			int ty_size;
		};
		// int double long float short char uint ulong ushort ldouble
		class BasicType:public Type {
		public:
			BasicType(std::string _name,int tys) :Type(tys),name(_name) {}
			std::string to_string()const { return name; }
		private:
			std::string name;
		};
		bool converitble(ty_index t1, ty_index t2) {
			return convert_map.find(t1) != convert_map.end() && convert_map[t1] == t2;
		}
		void build_type_conver_info(ty_index t1, const std::vector<ty_index> & types);
		void init_basic_type();
		extern ty_index type_index;
		extern std::map<ty_index, BasicType*> type_map;
		extern std::map<ty_index, ty_index> convert_map;
	}
}