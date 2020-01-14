#include "../include/branch_loop.hpp"
#include "../include/info.hpp"
#include "../include/parser.hpp"
namespace hcc {
	void IfFalseToA::emit_code()
	{
		condition->emit_code();
		instructions.push_back("(iffalse " + condition->to_string() + " " + false_tag+")");
	}

	std::string _gen_false_tag() {
		static int index = 0;
		//  The tag which has a dot in front is auto generated jmp tag in an effort to distinct the user defined from compiler auto generated.
		return ".ft" + std::to_string(index++);
	}
	/*
		end_tag: 
		when processing if-else we need to imply end_tag for instance;
		if(a<b)
			min= a;
		else
			min = b;
		=======to=============
		(bool %t1 (< a b))
		(iffalse t1 .ft0)
		(= min a)
		(jmp .et)
		(tag .ft)
		(= min b)
		(tag .et)
		..residual instructions...

	*/
	std::string _gen_end_tag() {
		static int index = 0;
		return ".et" + std::to_string(index++);
	}

	namespace Parser
	{
		void build_block()
		{
			token_stream.match(BEGIN);
			abstruct_instruction_table.push_back(new FixedInstruction(NodeType::BEGIN_BLOCK, "begin"));
			while (token_stream.this_tag() != END) {
				auto cur_statement = statement();
				if(cur_statement!=nullptr)
					abstruct_instruction_table.push_back(cur_statement);
			}
			abstruct_instruction_table.push_back(new FixedInstruction(NodeType::END_BLOCK, "end"));
			token_stream.match(END);
		}
		/*
		if(a<b)
		min= a;
		else
		min = b;
		=======to=============
		(bool %t1 (< a b))
		(iffalse t1 .ft0)
		(= min a)
		(jmp .et0)
		(tag .ft0)
		(= min b)
		(tag .et)
		..residual instructions...
		*/
		void build_if()
		{
			// to store the tmp abstruct instructions and when the parsing finshed, add abstruct_inst to abstruct_instruction_table
			token_stream.match(IF);
			token_stream.match(LPAREN);
			auto condition = analyse_expr::create_expr();
			token_stream.match(RPAREN);
			std::string false_tag = _gen_false_tag();
			abstruct_instruction_table.push_back(new IfFalseToA(false_tag, condition));
			if (token_stream.this_tag() == BEGIN)
				build_block();
			else
			{
				auto cur_statement = statement();
				if(cur_statement!=nullptr)
					abstruct_instruction_table.push_back(cur_statement);
			}
			// attach end tag into abstruct_instruction_table
			if (token_stream.this_tag() == ELSE) {
				std::string end_tag = _gen_end_tag();
				abstruct_instruction_table.push_back(new Jmp(end_tag));
				abstruct_instruction_table.push_back(new JmpTag(false_tag));
				token_stream.match(ELSE);
				if (token_stream.this_tag() == BEGIN)
					build_block();
				else
				{
					auto cur_statement = statement();
					if (cur_statement != nullptr)
						abstruct_instruction_table.push_back(cur_statement);
				}
				abstruct_instruction_table.push_back(new JmpTag(end_tag));
				return;
			}
			abstruct_instruction_table.push_back(new JmpTag(false_tag));
		}
	}



	void JmpTag::emit_code()
	{
		instructions.push_back("(tag " + tag_name + ")");
	}

	void Jmp::emit_code()
	{
		instructions.push_back("(jmp " + tag_name + ")");
	}

}


