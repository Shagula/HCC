#pragma once
#include <iostream>
#include <map>
#include <string>
namespace vm {
	using index_type = int;

	enum InsTag :char {
		// bin_op sub_ins op1,op2 
		/*
			sub_ins First Bit,
					  0-> i8
					  1-> i16
					  2-> i32
					  3-> i64
					  4-> r32
					  5-> r64
					  6-> r128
					  C2 need to support
					  7-> u8
					  8-> u16
					  9-> u32
					  A-> u64
					Second Bit,
					0:00-> imm op imm
					1:01-> imm op add
					2:10-> add op imm
					3:11-> add op add
		*/
		SADD = 0x01, SSUB, SMUL, SDIV,
		ADD,SUB,MUL,DIV,
		EQ, NE, GT, GE, LE, LT,
		AND, OR, W8, W16, W32, W64, WR128,
		// write from cache
		WT8,WT16,WT32,WT64,WT128,
		// sub_ins 
		/*
			0-> common
			1-> Expr
		*/
		JMP, CALL
	};
	
	extern std::string ir_content;
	extern int ir_index;
	extern int line_no;
	extern int cur_pos;
	extern std::map<std::string, void(*)()> parsing_table;
	extern std::string cur_instruction; // cur instruction name
	// the max idx of the integer type in an effort to distinguish if the type is integer
	const int INTEGER_TIDX_MAX = 3;
	const std::map<std::string, char> stype_table{ { "i8",0 },{ "i16",1 },{ "i32",2 },
	{ "i64",3 },{ "r32",4 },{ "r64",5 },{ "r128",6 } };
	// <var_name,<type_index,type_length>>
	const std::map<std::string, std::pair<int, int>> type_name_info_table{ { "char",{ 0,8 } },{ "short",{ 1,16 } },{ "int",{ 2,32 } },
	{ "long",{ 3,64 } },{ "float",{ 4,32 } },{ "double",{ 5,64 } } };
	//======================================================
	class Error {
	public:
		Error(const std::string &str) :err_msg(str), line(line_no) {}
		std::string what()const { return "<line:" + std::to_string(line) + ">" + err_msg; }
	private:
		std::string err_msg;
		int line;
	};
	// to store the bin info of the imm or var add.
	struct InsData {
		InsData(char *i, int len) :info(i), length(len) {}
		template<typename Ty>
		InsData(const Ty & data) {
			length = sizeof(data);
			info = new char[length];
			for (int i = 0; i < length; i++)
				info[i] = ((char*)(&data))[i];
		}
		InsData(const InsData &) = delete;
		InsData(InsData &&ins);
		void push(InsData&);
		char *release() { return info; info = nullptr; }
		int length = 0;
		char *info = nullptr;
		~InsData() {
			if (info != nullptr)
				delete[] info;
		}
	};
	//======================================================
	void match(char ch);
	void parsing();
	std::string extract_word();
	std::pair<char, InsData> process_unit();
	char *convert_imm_type(int target_type);
	void parse_bin();
	void parse_decl();

}