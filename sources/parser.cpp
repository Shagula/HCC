#include "../include/parser.hpp"
#include "../include/expr.hpp"
#include "../include/symbols.hpp"
namespace hcc {

	extern bool function_block;
	bool _is_value_node(NodeType t)
	{
		switch (t)
		{
		case hcc::NodeType::VAR:
		case hcc::NodeType::LITERAL:
			return true;
		default:
			return false;
		}
	}

	VarDeclUnit::VarDeclUnit(type::Type* t) :type(t)
	{
		name = Id::get_value(token_stream.this_token());
		token_stream.match(ID);
		if (token_stream.this_tag() == ASSIGN) {
			token_stream.match(ASSIGN);
			expr = analyse_expr::create_expr();
			return;
		}
		else if (token_stream.this_tag() == COMMA)
			return;
		throw Error("invaild init expression!");
	}

	void VarDeclUnit::emit_code()
	{
		std::string type_name = get_type()->to_string();
		std::string ret = "(";

		std::string var_name = get_name_part();
		expr->emit_code();
		ret += type_name + " %" + var_name;
		if (expr->get_node_type() != NodeType::NON_OP) {
			// if the expr is bin , try to assign a var type to it. we don't assign type to value_node, cause the different mechanism to 
			// binop and value_node
			if (expr->get_node_type() == NodeType::BIN_OP)
				expr->set_type(get_type());
			std::string tmp = expr->to_string();
			if (expr->get_type() != get_type() && _is_value_node(expr->get_node_type()))
				tmp = type_convert(expr->get_type(), get_type(), expr);
			ret += " " + tmp + ")";

			instructions.push_back(ret);
		}
	}

	LocalVarDecl::LocalVarDecl(std::vector<VarDeclUnit*>& vec, type::Type* t) :Node(NodeType::LOCAL_VAR_DECL), units(vec)
	{
		set_type(t);
		for (const auto& a : vec) {
			_symbol_table.push(new VarRecorder(a->get_name_part(), t));
		}
	}

	void LocalVarDecl::emit_code()
	{
		for (auto a : units) {
			a->emit_code();
		}
	}

	extern std::vector<std::pair<std::string, std::string>> nearest_loop_tag;
	namespace Parser {
		void build_if();
		void build_block(bool bf=false);
		void build_while();

		void build_program()
		{
			while (token_stream.this_tag() != Tag::ENDOF) {
				function_or_glo_var();
			}
		}

		Node* var_decl()
		{
			type::Type* type = hcc::process_type();
			std::vector<VarDeclUnit*> units;
			units.push_back(new VarDeclUnit(type));
			while (token_stream.this_tag() != SEMI) {
				token_stream.match(COMMA);
				units.push_back(new VarDeclUnit(type));
			}
			token_stream.match(SEMI);
			return new LocalVarDecl(units, type);
		}
		Node* statement()
		{
			switch (token_stream.this_tag())
			{
			case RETURN:
				if (!function_block) { throw Error("return must exist in function defination!"); }
				return return_statement();
			case BREAK:
				token_stream.match(BREAK);
				token_stream.match(SEMI);
				return new Jmp(nearest_loop_tag.back().second);
			case CONTINUE:
				token_stream.match(CONTINUE);
				token_stream.match(SEMI);
				return new Jmp(nearest_loop_tag.back().first);
			case INTEGER_DECL:
			case CHAR_DECL:
			case LONG_DECL:
			case FLOAT_DECL:
			case DOUBLE_DECL:
				return var_decl();
			case BEGIN:
				build_block();
				return nullptr;
			case IF:
				build_if();
				return nullptr;
			case WHILE:
				build_while();
				return nullptr;
			default:
			{
				auto ret = analyse_expr::create_expr();
				token_stream.match(SEMI);
				return ret;
			}
			}
		}
		Node * return_statement()
		{
			token_stream.match(RETURN);

			if (token_stream.this_tag() == SEMI)
			{
				token_stream.match(SEMI);
				return new Return(nullptr, true);
			}
			auto expr = analyse_expr::create_expr();
			token_stream.match(SEMI);
			return new Return(expr, false);
		}
	}
	void Return::emit_code()
	{
		if (empty) {
			instructions.push_back("(eret)");
			return;
		}
		expr->emit_code();
		instructions.push_back("(ret " + expr->to_string() + ")");
	}
}


