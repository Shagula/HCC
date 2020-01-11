#include "../include/symbols.hpp"
#include "../include/lexer.hpp"
#include "../include/type.hpp"
namespace hcc {

	SymbolTable _symbol_table;

	void SymbolTable::type_check(Token* id, SymbolType e)
	{
		auto result = find(Id::get_value(id));
		if (result == nullptr)
			throw Error("id " + id->to_string() + " no found.");
		if (result->symbol_type != e)
			throw Error("id typ not matched");
	}

	Symbol* SymbolTable::find_front(std::string id)
	{
		auto result = data.front().find(id);
		if (result == data.front().end())
			return nullptr;
		return result->second;
	}

	Symbol* SymbolTable::find(std::string id)
	{
		for (int i = 0; i < data.size(); i++)
		{
			auto result = data[i].find(id);
			if (result != data[i].end())
			{
				return result->second;
			}
		}
		return nullptr;
	}

	void SymbolTable::push(Symbol* wr)
	{
		if (data.front().find(wr->get_name()) != data.front().end())
			throw Error("symbol redefined!");
		data.front().insert({ wr->get_name(),wr });
	}
	void SymbolTable::print()
	{
		for (const auto& a : data)
		{
			for (const auto& b : a)
			{
				std::cout << "ID:" << b.first << " TYPE:" << b.second->get_type()->to_string() << std::endl;;
			}
			std::cout << "=================================\n";
		}
		std::cout << "#########################################\n\n\n";
	}
}