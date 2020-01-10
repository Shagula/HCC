#pragma once
#include <iostream>
#include <deque>
#include <map>
namespace hcc
{
	class Token;
	namespace type {
		class Type;
	}
	std::string get_tmp_var_name(bool clear);
	enum class SymbolType {
		LOCAL_VAR,
		GLO_VAR,
		FUNCTION_ID,
	};
	class Symbol {
	public:
		Symbol(const std::string& str, type::Type* t, SymbolType st) :name(str), type(t), symbol_type(st) {}
		std::string get_name() { return name; }
		type::Type* get_type() { return type; }
		SymbolType symbol_type;
	private:
		std::string name;
		type::Type* type;
	};
	// stores the information of a local variable
	class VarRecorder :public Symbol {
	public:
		VarRecorder(const std::string& _name, type::Type* t) :Symbol(_name, t, SymbolType::LOCAL_VAR) {}
	private:

	};
	class SymbolTable
	{
	public:
		SymbolTable()
		{
			data.push_front(std::map<std::string, Symbol*>());
		}
		void new_block()
		{
			data.push_front(std::map<std::string, Symbol*>());
		}
		void end_block()
		{
			data.pop_front();
		}
		void type_check(Token* id, SymbolType e);
		Symbol* find_front(std::string id);
		Symbol* find(std::string id);
		void push_glo(std::string id, Symbol* wr)
		{
			data.back().insert({ id,wr });
		}
		void push(Symbol* wr);
		void print();
	private:
		std::deque<std::map<std::string, Symbol*>> data;
	};
	// symbol table for user
	extern SymbolTable _symbol_table;
}