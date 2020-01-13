#include "../include/branch_loop.hpp"
#include "../include/info.hpp"
#include "../include/parser.hpp"
namespace hcc {
	void IfTrueToA::emit_code()
	{
		condition->emit_code();
		instructions.push_back("(if " + condition->to_string() + " " + false_tag+")");
		block->emit_code();
		instructions.push_back("(tag " + false_tag + ")");
	}
	std::string _gen_false_tag() {
		static int index = 0;
		//  The tag which has a dot in front is auto generated jmp tag in an effort to distinct the user defined from compiler auto generated.
		return ".ft" + std::to_string(index++);
	}

	void Block::emit_code()
	{
		/*
		for instance:
		if(a==1)
			a++;
		a-=1;
		it will tanslate into
		IR (Scheme-Style :-) )
		(bool %0 a==1)
		(if %0 :.ft0)
		(inc a)
		(tag .ft0)
		(dec a)
		*/
		if (block_content.size() == 1) {
			block_content.front()->emit_code();
			return;
		}
		instructions.push_back("(begin)");
		for (auto a : block_content)
			a->emit_code();
		instructions.push_back("(end)");
	}

	namespace Parser
	{
		Block* build_block()
		{
			token_stream.match(BEGIN);
			std::vector<Node*> nodes_vec;
			while (token_stream.this_tag() != END) {
				nodes_vec.push_back(statement());
			}
			token_stream.match(END);
			return new Block(nodes_vec);
		}
		Node * build_if()
		{
			token_stream.match(IF);
			token_stream.match(LPAREN);
			auto condition = analyse_expr::create_expr();
			token_stream.match(RPAREN);
			Block* blo;
			if (token_stream.this_tag() == BEGIN)
				blo = build_block();
			else
				blo = new Block({ statement() });
			return new IfTrueToA(_gen_false_tag(),condition,blo);
		}
	}

}


