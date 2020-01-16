#include "../include/parser.hpp"
#include "../include/expr.hpp"
#include "../include/symbols.hpp"
namespace hcc {


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

	LocalVarDecl::LocalVarDecl(std::vector<VarDeclUnit*>& vec, type::Type* t) :Node(NodeType::LOCAL_VAR_DECL),units(vec)
	{
		set_type(t);
		for (const auto& a : vec) {
			_symbol_table.push(new VarRecorder(a->get_name_part(), t));
		}
	}

	void LocalVarDecl::emit_code()
	{
		std::string type_name = get_type()->to_string();
		std::string ret="(";
		for (auto& a : units) {
			std::string var_name = a->get_name_part();
			a->expr->emit_code();
			ret += type_name + " %" + var_name;
			if (a->expr->get_node_type() != NodeType::NON_OP) {
				// if the expr is bin , try to assign a var type to it. we don't assign type to value_node, cause the different mechanism to 
				// binop and value_node
				if (a->expr->get_node_type() == NodeType::BIN_OP)
					a->expr->set_type(get_type());
				std::string tmp = a->expr->to_string();
				if (a->expr->get_type() != get_type() && _is_value_node(a->expr->get_node_type()))
					tmp = type_convert(a->expr->get_type(), get_type(), a->expr);
				ret += " "+tmp+")";
			}
			instructions.push_back(ret);
		}
	}

	extern std::vector<std::pair<std::string, std::string>> nearest_loop_tag;
	namespace Parser {
		void build_if();
		void build_block();
		void build_while();
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
	}
}


