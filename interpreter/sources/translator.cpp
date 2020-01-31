#include "../include/translator.hpp"
#include <string>
namespace vm
{
	//=============================== vars===============================
	std::string ir_content;
	int ir_index = 0;
	int line_no = 1;
	std::map<std::string, void(*)()> parsing_table{
		{"+",parse_bin },{"-",parse_bin},{ "*",parse_bin },{ "/",parse_bin }
	};

	std::string cur_instruction; // cur instruction name
	//====================================================================
	void match(char ch)
	{
		if (ch != ir_content[ir_index++])
			throw Error("instruction format error!");
	}
	void parsing()
	{
		while (ir_index < ir_content.size())
		{
			match('(');
			std::string word = extract_word();
			auto result = parsing_table.find(word);
			if (result == parsing_table.end())
				throw Error("invaild instruction: " + word);
			result->second();
			match(')');
		}
	}
	std::string extract_word()
	{
		std::string ret;
		char cur_ch = ir_content[ir_index];
		while (cur_ch != ' '&&cur_ch != ')')
		{
			ret += cur_ch;
			cur_ch = ir_content[++ir_index];
		}
		return ret;
	}
	void parse_bin()
	{
		const std::map<std::string, InsTag> si_table{
			{"+",ADD},{"-",SUB},{"*",MUL},{"/",DIV}
		};
		char *instruction = new char[20];
		InsTag tag=si_table.find(cur_instruction)->second;
		// ins name
		instruction[0] = tag;
		// need to obtain type and mod(the type of the operators, imm or var)


	}

	// first sub_ins, second unit data.
	std::pair<char,InsData> process_unit() {
		std::string unit = extract_word();
		if (unit[0] == '%')
		{
			// TODO
		}
	}
}