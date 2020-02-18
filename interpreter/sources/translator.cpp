#include "../include/translator.hpp"
#include "../include/instructions.hpp"
#include "../include/word_table.hpp"
#include <string>
#include <cstring>
namespace hcc
{
	char _convert_escape(char);
}
namespace vm
{
	std::string to_string(std::string &str, int & pos) {
		std::string value;
		// jump over '
		pos++;
		for (; pos < str.size(); pos++)
		{
			if (str[pos] == '\"')
				break;
			if (str[pos] == '\\')
			{
				pos++;
				if (pos >= str.size())
					throw Error("bad string");
				char tmp = hcc::_convert_escape(str[pos]);
				value += tmp;
			}
			else
				value += str[pos];
		}
		pos++;
		return value;
	}

	//===============================externs=============================

	namespace print_ins {
		void print_str(char *ins);
		void print_int_var(char *ins);
	}
	namespace write_ins {
		void write_8(char *ins);
		void write_16(char * ins);
		void write_32(char *ins);
		void write_64(char *ins);
		void write_t_8(char *ins);
		void write_t_16(char * ins);
		void write_t_32(char *ins);
		void write_t_64(char *ins);
	}
	namespace  control_ins {
		void jmp(char *ins);
		void iffalse(char *ins);
	}
	int find_type(const std::string &var_name);
	instruction_type gen_covert_op(char t1, char t2);
	index_type find_pos(const std::string &var_name);
	//=============================== vars===============================
	std::string ir_content;
	int cur_pos = 0;
	int ir_index = 0;
	int line_no = 1;
	std::map<std::string, void(*)()> parsing_table{
		{"+=",parse_bin },{"-=",parse_bin},{ "*=",parse_bin },{ "/=",parse_bin },{"=",parse_bin},
		{"int",parse_decl},{"char",parse_decl},{"long",parse_decl },{"float",parse_decl },{"double",parse_decl },
		{"jmp",parse_jmp},{"tag",parse_tag},{"print",parse_print_str},{"print_var",parse_print_var},{"iffalse",parse_iffalse}
	};
	std::map<std::string, int> _tag_table;
	std::map<std::string, std::vector<char *>>_indefinate_tag_table;
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

			if (ir_content[ir_index] != '(')
			{
				ir_index++;
				continue;
			}
			match('(');
			std::string word = extract_word();
			cur_instruction = word;
			auto result = parsing_table.find(word);
			if (result == parsing_table.end())
				throw Error("invaild instruction: " + word);
			result->second();
			match(')');
			line_no++;
		}
	}
	void parse_bin()
	{
		const std::map<std::string, InsTag> si_table{
			{ "+=",SADD },{ "-=",SSUB },{ "*=",SMUL },{"=",ASSIGN}, { "/=",SDIV },{"+",ADD},{"-",SUB},{"*",MUL},{"/",DIV},
			{"<",LT},{"<=",LE},{">=",GE},{">",GT},{"==",EQ},{"!=",NE}
		};

		auto tag_result = si_table.find(cur_instruction);
		if (tag_result == si_table.end())
			throw Error(cur_instruction + " invalid binary operation");

		// ins name
		// need to obtain type and mod(the type of the operators, imm or var)
		auto op1 = process_unit();

		int op1_is_var = (op1.first >> 4);
		auto op2 = process_unit();
		char dd = op2.first | (op1_is_var << 5) | ((op2.first >> 4) << 4);
		op1.second.push(op2.second);
		auto ins = gen_bin_op(dd, tag_result->second);
		// load instruction.
		glo_instructions.push_back({ ins, op1.second.release() });
	}

	void parse_decl()
	{
		auto type_result = type_name_info_table.find(cur_instruction);
		if (type_result == type_name_info_table.end())
			throw Error("void vm::parse_decl() unknown type!");
		// the first char of var_name is % so it needs to skip it
		std::string var_name = extract_word().substr(1);
		int pos = cur_pos;
		cur_pos += type_result->second.second / 8;
		var_type_table.insert({ var_name, VarInfo(type_result->second.first, pos) });

		int byte_count = type_result->second.second / 8;

		// bin_op factor
		if (ir_content[ir_index] == '(')
		{
			match('(');
			cur_instruction = extract_word();
			parse_bin();
			match(')');
			char *ins = new char[sizeof(index_type)];
			*(index_type*)ins = pos;
			switch (byte_count)
			{
			case 1:
				glo_instructions.push_back({ write_ins::write_t_8,ins });
				return;
			case 2:
				glo_instructions.push_back({ write_ins::write_t_16,ins });
				return;
			case 4:
				glo_instructions.push_back({ write_ins::write_t_32,ins });
				return;
			case 8:
				glo_instructions.push_back({ write_ins::write_t_64,ins });
				return;
			default:
				throw Error("intern_error E3");
				break;
			}
			return;
		}
		else if (ir_content[ir_index] == '%')
		{
			std::string rhs_var_name = extract_word().substr(1);
			char * ins = new char[sizeof(index_type)];
			memset(ins, find_pos(rhs_var_name), sizeof(index_type));
			// convert to ache
			glo_instructions.push_back({ gen_covert_op(find_type(rhs_var_name),type_result->second.first),ins });
			// write var from ache
			switch (byte_count)
			{
			case 1:
				glo_instructions.push_back({ write_ins::write_t_8,nullptr });
				return;
			case 2:
				glo_instructions.push_back({ write_ins::write_t_16,nullptr });
				return;
			case 4:
				glo_instructions.push_back({ write_ins::write_t_32,nullptr });
				return;
			case 8:
				glo_instructions.push_back({ write_ins::write_t_64,nullptr });
				return;
			default:
				throw Error("intern_error E3");
				break;
			}
			return;
		}
		std::string right_value_info = extract_word();
		InsData ins = convert_imm_type(right_value_info, type_result->second.first);
		ins.push(new int(pos), sizeof(pos));
		switch (byte_count)
		{
		case 1:
			glo_instructions.push_back({ write_ins::write_8,ins.release() });
			return;
		case 2:
			glo_instructions.push_back({ write_ins::write_16,ins.release() });
			return;
		case 4:
			glo_instructions.push_back({ write_ins::write_32,ins.release() });
			return;
		case 8:
			glo_instructions.push_back({ write_ins::write_64,ins.release() });
			return;
		default:
			throw Error("intern_error E3");
			break;
		}
	}

	void parse_jmp()
	{
		std::string tag_name = extract_word();
		int pos = get_tag_pos(tag_name);
		char * ptr = new char[4];
		if (pos == -1)
			_indefinate_tag_table[tag_name].push_back(ptr);
		*(index_type*)ptr = pos;
		glo_instructions.push_back({ control_ins::jmp,ptr });
	}

	void parse_tag() {
		set_tag(extract_word());
	}
	void parse_iffalse()
	{
		std::string condition = extract_word();
		index_type con_pos = find_pos(condition.substr(1));
		char * ins = new char[sizeof(index_type) + 4];
		*(index_type*)ins = con_pos;
		// parsing tag
		std::string tag_name = extract_word();
		int jmp_pos = get_tag_pos(tag_name);
		if (jmp_pos == -1)
		{
			_indefinate_tag_table[tag_name].push_back(ins + sizeof(index_type));
		}
		*(index_type*)(ins + sizeof(index_type)) = jmp_pos;
		glo_instructions.push_back({ control_ins::iffalse,ins });
	}
	void parse_print_str()
	{
		while (ir_content[ir_index] == ' ') ir_index++;
		std::string result = vm::to_string(ir_content, ir_index);
		char *tmp = new char[result.size() + 1];
		strcpy_s(tmp, result.size() + 1, result.c_str());
		glo_instructions.push_back({ print_ins::print_str,tmp });
	}

	void parse_print_var()
	{
		std::string var_name = extract_word();
		char *tmp = new char[sizeof(index_type)];
		int pos = find_pos(var_name);
		if (pos < 0)
			throw Error("undefined var " + var_name);
		*(index_type*)tmp = pos;
		glo_instructions.push_back({ print_ins::print_int_var,tmp });
	}

	void set_tag(const std::string & tag_name)
	{
		if (_indefinate_tag_table.count(tag_name))
		{
			index_type pos = glo_instructions.size();
			auto result = _indefinate_tag_table.find(tag_name);
			for (int i = 0; i < result->second.size(); i++)
			{
				// the ptr points to a instruction which should store position infomation
				char * ptr = result->second[i];
				*(int*)ptr = pos-1;
			}
		}
		_tag_table.insert({ tag_name,glo_instructions.size()-1 });

	}

	int get_tag_pos(const std::string & tag_name)
	{
		auto result = _tag_table.find(tag_name);
		if (result == _tag_table.end())
			return -1;
		return result->second;
	}

	//======================instruction proccessor========================
	std::string extract_word()
	{
		std::string ret;
		char cur_ch = ir_content[ir_index];
		while (cur_ch == ' ')
			cur_ch = ir_content[++ir_index];
		while (cur_ch != ' '&&cur_ch != ')'&&cur_ch != ':')
		{
			ret += cur_ch;
			cur_ch = ir_content[++ir_index];
		}
		while (cur_ch == ' ')
			cur_ch = ir_content[++ir_index];
		return ret;
	}


	int64_t to_int(std::string str) {
		int64_t ret = 0;
		for (int pos = 0; pos < str.size(); pos++)
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
			return { type | (1 << 4),InsData(find_pos(var_name)) };
		}

		auto type_info = stype_table.find(unit);
		if (type_info == stype_table.end())
			throw Error("unknown type " + unit + "!");
		type = type_info->second;
		// store the unit info( var or imm) in 5ed bit.
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
			throw vm::Error("type error or the version is too slow to support the new type.");
		}

	}

	InsData convert_imm_type(const std::string &type_name, int target_type)
	{
		auto type_result = stype_table.find(type_name);
		if (type_result == stype_table.end())
			throw Error("invalid type: " + type_name);
		match(':');
		int imm_type_idx = type_result->second;
		// calculate target_type len
		int target_type_len = pow(2, target_type);
		if (target_type >= 4)
			target_type_len /= 8;
		char *ret = new char[target_type_len];
		if (imm_type_idx <= INTEGER_TIDX_MAX)
		{
			switch (target_type)
			{
			case 0:
				*(int8_t*)ret = to_int(extract_word());
				break;
			case 1:
				*(int16_t*)ret = to_int(extract_word());
				break;
			case 2:
				*(int32_t*)ret = to_int(extract_word());
				break;
			case 3:
				*(int64_t*)ret = to_int(extract_word());
				break;
			case 4:
				*(float*)ret = to_int(extract_word());
				break;
			case 5:
				*(double*)ret = to_int(extract_word());
				break;
			case 6:
				*(long double*)ret = to_int(extract_word());
				break;
			default:
				throw Error("intern_error E1");
			}
		}
		else {
			// boring copy - paste
			switch (target_type)
			{
			case 0:
				*(int8_t*)ret = to_real(extract_word());
				break;
			case 1:
				*(int16_t*)ret = to_real(extract_word());
				break;
			case 2:
				*(int32_t*)ret = to_real(extract_word());
				break;
			case 3:
				*(int64_t*)ret = to_real(extract_word());
				break;
			case 4:
				*(float*)ret = to_real(extract_word());
				break;
			case 5:
				*(double*)ret = to_real(extract_word());
				break;
			case 6:
				*(long double*)ret = to_real(extract_word());
				break;
			default:
				throw Error("intern_error E1");
			}
		}
		auto rr= InsData(ret, target_type_len);
		delete ret;
		return rr;
	}

	InsData::InsData(InsData && ins)
	{
		info = ins.info;
		length = ins.length;
		ins.info = nullptr;
	}
	void InsData::push(void * ins, int len)
	{
		char *tmp = new char[length +len];
		memcpy(tmp, info, length);
		memcpy(tmp + length, ins, len);
		delete[] info;
		info = tmp;
		length += len;
	}
	void InsData::push(InsData& rhs)
	{
		char *tmp = new char[length + rhs.length];
		int i = 0;
		memcpy(tmp, info, length);
		memcpy(tmp + length, rhs.info, rhs.length);
		delete[] rhs.info;
		delete[] info;
		rhs.info = nullptr;
		info = tmp;
		length += rhs.length;
	}
}