#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>
namespace hcc {
	namespace type {
		class Type;
		extern std::map<std::string, Type*> basic_type_map;
		extern Type* void_type;
		enum TypeTag {
			BASIC=1,PTR,CONST_PTR,CONST,NONE,
		};
		class Type {
		public:
			Type(const std::string& n, size_t sz) :name(n), type_length(sz) {}
			size_t size() { return type_length; }
			virtual bool convertible(Type* ty)=0;
			virtual std::string to_string() { return name; }
			virtual ~Type() {}
			enum TypeTag type_tag=NONE;
		private:
			std::string name;
			size_t type_length;
		};
		class BasicType:public Type {
		public:
			BasicType(const std::string& n, size_t sz) :Type(n, sz) {
				type_tag = BASIC;
			}
			bool convertible(Type* ty)override {
				return ty->type_tag == BASIC;
			}
		private:

		};

	}
	type::Type* process_type();
}