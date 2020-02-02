#include "../include/translator.hpp"
#include "../include/instructions.hpp"
#include <string>
namespace vm
{

	//===============================externs=============================
	int find_type(const std::string &var_name);

	index_type find_pos(const std::string &var_name);
	//=============================== vars===============================
	std::string ir_content;
	int ir_index = 0;
	int line_no = 1;
	std::map<std::string, void(*)()> parsing_table{
		{"+",parse_bin },{"-",parse_bin},{ "*",parse_bin },{ "/",parse_bin }
	};
	//=====================================parser========================
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
	void parse_bin()
	{
		const std::map<std::string, InsTag> si_table{
			{ "+",ADD },{ "-",SUB },{ "*",MUL },{ "/",DIV }
		};
		InsTag tag = si_table.find(cur_instruction)->second;
		// ins name
		// need to obtain type and mod(the type of the operators, imm or var)
		auto op1 = process_unit();
		int op1_is_var = (op1.first >> 4);
		auto op2 = process_unit();
		char dd = op2.first | (op1_is_var << 5);
		op1.second.push(op2.second);
		//auto ins = gen_bin_op(dd,tag);
		// load instruction.
		//glo_instructions.push_back({ins, op1.second.release()});
	}

	//======================instruction proccessor========================
	std::string extract_word()
	{
		std::string ret;
		char cur_ch = ir_content[ir_index];
		while (cur_ch != ' '&&cur_ch != ')'||cur_ch==':')
		{
			ret += cur_ch;
			cur_ch = ir_content[++ir_index];
		}
		return ret;
	}

	int64_t to_int(std::string str) {
		int64_t ret = 0;
		for (int pos=0; pos < str.size(); pos++)
		{
			if (isdigit(str[pos]))
			{
				ret = ret * 10 + (str[pos] - 48);
			}
			else
			{
				break;
			}
		}
		return ret;
	}

	long double to_real(std::string str) {
		int64_t int_part = 0;
		int pos = 0;
		for (; pos < str.size(); pos++)
		{
			if (isdigit(str[pos]))
			{
				int_part = int_part * 10 + (str[pos] - 48);
			}
			else
			{
				break;
			}
		}
		pos++;
		long double tmp = 0.0;
		long double tmp2 = 1;
		for (; pos < str.size(); pos++)
		{
			if (isdigit(str[pos]))
			{
				tmp2 /= 10;
				tmp = tmp + tmp2 * (str[pos] - (size_t)48);
			}
		}
		return int_part + tmp;
	}
	// first sub_ins, second unit data.
	std::pair<char, InsData> process_unit() {
		std::string unit = extract_word();
		char type = 0;
		if (unit[0] == '%')
		{
			std::string var_name = unit.substr(1, unit.size() - 1);
			type = find_type(var_name);
			return { type,InsData(find_pos(var_name)) };
		}
		const std::map<std::string, char> type_table{ {"i8",0},{"i16",1},{"i32",2},
		{"i64",3 }, { "r32",4 }, { "r64",5 }, { "r128",6 }};
		auto type_info = type_table.find(unit);
		if (type_info == type_table.end())
			throw Error("unknown type!");
		type = type_info->second;
		// store the unit info( var or imm) in 5ed bit.
		type = type | (1 << 4);
		match(':');
		unit = extract_word();
		

		switch (type) {
		case 0:
			return { type,InsData((int8_t)to_int(unit)) };
		case 1:
			return { type,InsData((int16_t)to_int(unit)) };
		case 2:
			return { type,InsData((int32_t)to_int(unit)) };
		case 3:
			return { type,InsData((int64_t)to_int(unit)) };
		case 4:
			return { type,InsData((float)to_real(unit)) };
		case 5:
			return { type,InsData((double)to_real(unit)) };
		case 6:
			return { type,InsData((long double)to_real(unit)) };
		default:
			throw Error("type error or the version is too slow to support the new type.");
		}

	}
	void InsData::push(InsData rhs)
	{
		char *tmp = new char[length + rhs.length];
		int i = 0;
		for (i = 0; i < length; i++) {
			tmp[i] = info[i];
		}
		i++;
		for (int j = 0; j < rhs.length; j++) {
			tmp[i + j] = rhs.info[j];
		}
		delete[] info;
		info = tmp;
		length += rhs.length;
	}
}