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
		EQ, NE, GT, GE, LE, LT,
		AND, OR, W8, W16, W32, W64, WR128,
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
	extern std::map<std::string, void(*)()> parsing_table;
	extern std::string cur_instruction; // cur instruction name

	//======================================================
	class Error {
	public:
		Error(const std::string &str) :err_msg(str), line(line_no) {}
		std::string what() { return "<line:" + std::to_string(line) + ">" + err_msg; }
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

		void push(InsData);
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
	void parse_bin();


}